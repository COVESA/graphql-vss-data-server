/*
 * This file was generated by the CommonAPI Generators.
 * Used org.genivi.commonapi.someip 3.2.0.v202012010944.
 * Used org.franca.core 0.13.1.201807231814.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at
 * http://mozilla.org/MPL/2.0/.
 */
#include <v1/org/genivi/vehicle/playground/PlaygroundSomeIPStubAdapter.hpp>
#include <v1/org/genivi/vehicle/playground/Playground.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/SomeIP/AddressTranslator.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

namespace v1 {
namespace org {
namespace genivi {
namespace vehicle {
namespace playground {

std::shared_ptr<CommonAPI::SomeIP::StubAdapter> createPlaygroundSomeIPStubAdapter(
                   const CommonAPI::SomeIP::Address &_address,
                   const std::shared_ptr<CommonAPI::SomeIP::ProxyConnection> &_connection,
                   const std::shared_ptr<CommonAPI::StubBase> &_stub) {
    return std::make_shared< PlaygroundSomeIPStubAdapter<::v1::org::genivi::vehicle::playground::PlaygroundStub>>(_address, _connection, _stub);
}

void initializePlaygroundSomeIPStubAdapter() {
    CommonAPI::SomeIP::AddressTranslator::get()->insert(
        "local:org.genivi.vehicle.playground.Playground:v1_0:1",
         0xff40, 0x1, 1, 0);
    CommonAPI::SomeIP::Factory::get()->registerStubAdapterCreateMethod(
        "org.genivi.vehicle.playground.Playground:v1_0",
        &createPlaygroundSomeIPStubAdapter);
}

INITIALIZER(registerPlaygroundSomeIPStubAdapter) {
    CommonAPI::SomeIP::Factory::get()->registerInterface(initializePlaygroundSomeIPStubAdapter);
}

} // namespace playground
} // namespace vehicle
} // namespace genivi
} // namespace org
} // namespace v1
