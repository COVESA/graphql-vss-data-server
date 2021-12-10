// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Gabriel Fernandes (g7fernandes@profusion.mobi),
//   Author: Leonardo Ramos (leo.ramos@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.

#pragma once

#include <graphqlservice/GraphQLResponse.h>

#include <graphql_vss_server_libs/protocol/graphqlrequeststate.hpp>

#ifdef IMPLEMENTATION_API
#undef IMPLEMENTATION_API
#endif
#if defined(BMW_CPP_GRAPHQL_BUILD_SHARED_LIBS) && BMW_CPP_GRAPHQL_BUILD_SHARED_LIBS
#define IMPLEMENTATION_API __attribute__ ((visibility ("default")))
#else
#define IMPLEMENTATION_API
#endif

namespace implementation {

class IMPLEMENTATION_API ImplementationException : public std::exception
{
    const std::string message;

public:
    IMPLEMENTATION_API ImplementationException(std::string&& exceptionMessage);
    const char* what() const noexcept override;
};

} // namespace implementation
