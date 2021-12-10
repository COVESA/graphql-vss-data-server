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

#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/CurrentGearAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/IsReverseGearOnAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/DrivePowerTransmissionAttribute.hpp"
#include <string>

#include <org/genivi/vehicle/playgroundtypes/PlaygroundTypes.hpp>

#include "implementation.hpp"

namespace implementation {
namespace Vehicle_Powertrain_Transmission {

typedef org::genivi::vehicle::playgroundtypes::PlaygroundTypes PlaygroundTypes;
typedef PlaygroundTypes::Gear Gear;
typedef Gear::Literal Literal;
typedef PlaygroundTypes::DriveType DriveType;

IMPLEMENTATION_API graphql::response::Value fromCurrentGearToCurrentGear(const Gear& value);

IMPLEMENTATION_API graphql::response::Value fromIsReverseGearOnToCurrentGear(const bool& value);

IMPLEMENTATION_API std::string fromDrivePowerTransmissionToDriveType(const DriveType& value);

} // namespace Vehicle_Powertrain_Transmission
} // namespace implementation
