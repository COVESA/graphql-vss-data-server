// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Gabriel Fernandes (g7fernandes@profusion.mobi),
//   Author: Leandro Ferlin (leandroferlin@profusion.mobi),
//   Author: Leonardo Ramos (leo.ramos@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.


#pragma once

#include "proxies/v1_org_genivi_vehicle_playground_PlaygroundProxy_1.hpp"
#include "franca_idl/vehicle/currentlocation.hpp"

namespace implementation::Vehicle_CurrentLocation {
    struct VehiclePositionEvent;
}

TYPEDEF_COMMONAPI_EVENT_SUBSCRIPTION_PROXY_ATTRIBUTE(
    implementation::Vehicle_CurrentLocation::VehiclePositionEvent,
    v1_org_genivi_vehicle_playground_PlaygroundProxy_1,
    VehiclePositionEvent
);