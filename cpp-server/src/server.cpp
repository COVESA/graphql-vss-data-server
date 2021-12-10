// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
//   Author: Gabriel Fernandes (g7fernandes@profusion.mobi),
//   Author: Georgia Garcia (georgia@profusion.mobi),
//   Author: Leonardo Ramos (leo.ramos@profusion.mobi),
//   Author: Pedro Soares (hspedro@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.

#include <iterator>
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <boost/asio/signal_set.hpp>
#include <boost/program_options.hpp>

#include <graphql_vss_server_libs/protocol/exceptions.hpp>
#include <graphql_vss_server_libs/protocol/jwtauthorizer.hpp>
#include <graphql_vss_server_libs/protocol/dummyauthorizer.hpp>
#if ANDROID
#include "android/androidKeystoreAuthorizer.hpp"
#endif
#include <graphql_vss_server_libs/protocol/graphqlserver.hpp>

#include <graphql_vss_server_libs/support/log.hpp>

#include "generated/Vehicle.hpp"
#include "generated/permissions_symbols.hpp"

using namespace graphql;
namespace po = boost::program_options;

constexpr int DEFAULT_PORT = 4000;

template<typename, typename = void>
constexpr bool is_type_complete_v = false;

template <typename T>
constexpr bool is_type_complete_v<T, std::void_t<decltype(sizeof(T))>> = true;

namespace graphql::vehicle {
class Mutation;
}

template <bool condition, typename... Params>
static vehicle::Operations getOperationRequest(Params... params)
{
    return vehicle::Operations(params...);
}

template<bool condition = is_type_complete_v<graphql::vehicle::Mutation>>
static vehicle::Operations getOperationRequest() {
    auto query = std::make_shared<graphql::vehicle::Query>();
    auto subscription = std::make_shared<graphql::vehicle::Subscription>();

    if constexpr(condition) {
        auto mutation = std::make_shared<graphql::vehicle::Mutation>();
        return getOperationRequest<condition>(query, mutation, subscription);
    } else {
        return getOperationRequest<condition>(query, subscription);
    }

}

void handleSignal(GraphQLServer* server, boost::asio::signal_set* signals,
    const boost::system::error_code& error, int sign)
{
    if (error)
    {
        std::cout << "Signal listener error: " << error.message() << std::endl;
        return;
    }
    switch (sign)
    {
        case SIGUSR2:
            server->garbageCollect();
            signals->async_wait(std::bind(handleSignal,
                server,
                signals,
                std::placeholders::_1,
                std::placeholders::_2));
            return;
        default:
            server->stopListening();
            return;
    }
}

int main(int argc, char** argv)
{
    uint16_t port;
    bool reuseAddress;
    std::string pubKeyFile;
    po::options_description config("Configuration");
    auto addConfigOption = config.add_options();
    addConfigOption("port,p",
        po::value<uint16_t>(&port)->default_value(DEFAULT_PORT),
        "HTTP port to listen (also $GDAS_PORT)");
    addConfigOption("reuse_address,R",
        po::value<bool>(&reuseAddress)->default_value(false),
        "Allow reuse address (also $GDAS_REUSE_ADDRESS)");
    addConfigOption("pub_key_file,k",
        po::value<std::string>(&pubKeyFile),
        "Path to PEM file with the RSA 256 Public Key (also $GDAS_PUB_KEY_FILE)");

    po::options_description desc("GraphQL Data Abstraction Server");
    desc.add(config);
    auto addDescOption = desc.add_options();
    addDescOption("version,V", "print build version");
    addDescOption("help,h", "this help message");

    po::variables_map vars;
    po::store(po::parse_environment(config, "GDAS_"), vars);
    po::store(po::parse_command_line(argc, argv, desc), vars);
    po::notify(vars);

    if (vars.count("help"))
    {
        std::cout << desc << std::endl;
        return 0;
    }
    if (vars.count("version"))
    {
        std::cout << GRAPHQL_DATA_SERVER_VERSION << std::endl;
        return 0;
    }

    DLT_REGISTER_APP("GDAS", "GraphQL Data Abstraction Server");
    DLT_REGISTER_CONTEXT(dltServer, "SERV", "GraphQL Server");
    DLT_REGISTER_CONTEXT(dltConnection, "CONN", "GraphQL Connection");
    DLT_REGISTER_CONTEXT(dltOperation, "OP", "GraphQL Connection Operation");
    DLT_REGISTER_CONTEXT(dltWebSocket, "WS", "WebSocket Transport");
    DLT_REGISTER_CONTEXT(dltCommonAPI, "CAPI", "CommonAPI Calls");

    websocketpp::lib::asio::io_service io_service;
#if DISABLE_PERMISSIONS
    DummyAuthorizer authorizer(permissions::getKnownPermissions());
#elif ANDROID
    AndroidKeystoreAuthorizer authorizer(AndroidKeystoreAuthorizer::createDefaultVerifier(),
        permissions::getKnownPermissions());
#else
    JwtAuthorizer authorizer(pubKeyFile.empty()
            ? JwtAuthorizer::createDefaultVerifier()
            : JwtAuthorizer::createDefaultVerifier(std::filesystem::path(pubKeyFile)),
        permissions::getKnownPermissions());
#endif
    auto executableSchema = getOperationRequest();
    auto server = GraphQLServer(&io_service, authorizer, executableSchema);
    server.startAccept(port, reuseAddress, [&port] {
        std::cout << "Server ready at port=" << port << std::endl;
    });

    boost::asio::signal_set signals(io_service, SIGINT, SIGQUIT, SIGTERM);
    signals.add(SIGUSR2);
    signals.async_wait(
        std::bind(handleSignal, &server, &signals, std::placeholders::_1, std::placeholders::_2));

    io_service.run();

    DLT_UNREGISTER_CONTEXT(dltServer);
    DLT_UNREGISTER_CONTEXT(dltConnection);
    DLT_UNREGISTER_CONTEXT(dltOperation);
    DLT_UNREGISTER_CONTEXT(dltWebSocket);
    DLT_UNREGISTER_CONTEXT(dltCommonAPI);
    DLT_UNREGISTER_APP();

    return 0;
}
