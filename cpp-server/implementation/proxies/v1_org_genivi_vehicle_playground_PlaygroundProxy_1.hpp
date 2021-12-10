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

#include <v1/org/genivi/vehicle/playground/PlaygroundProxy.hpp>

#include <graphql_vss_server_libs/support/commonapi-singletons.hpp>

TYPEDEF_COMMONAPI_PROXY(
    v1::org::genivi::vehicle::playground::PlaygroundProxy,
    "1",
    v1_org_genivi_vehicle_playground_PlaygroundProxy_1
);
