// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Leandro Ferlin (leandroferlin@profusion.mobi),
//   Author: Leonardo Ramos (leo.ramos@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.

#include "transmission.hpp"
#include "implementation.hpp"
#include <graphqlservice/GraphQLResponse.h>

namespace implementation {
namespace Vehicle_Powertrain_Transmission {

graphql::response::Value fromCurrentGearToCurrentGear(const Gear& value)
{
    switch (value)
    {
        case Literal::UNKNOWN_GEAR:
            return graphql::response::Value(0);
        case Literal::NEUTRAL:
            return graphql::response::Value(0);
        case Literal::FIRST_GEAR:
            return graphql::response::Value(1);
        case Literal::SECOND_GEAR:
            return graphql::response::Value(2);
        case Literal::THIRD_GEAR:
            return graphql::response::Value(3);
        case Literal::FOURTH_GEAR:
            return graphql::response::Value(4);
        case Literal::FIFTH_GEAR:
            return graphql::response::Value(5);
        case Literal::SIXTH_GEAR:
            return graphql::response::Value(6);
        case Literal::ERROR:
            return graphql::response::Value(Literal::ERROR);
        default:
            throw ImplementationException("unknown gear selection");
    }
}

graphql::response::Value fromIsReverseGearOnToCurrentGear(const bool& value)
{
    return graphql::response::Value(-1);

}

std::string fromDrivePowerTransmissionToDriveType(const DriveType& value)
{
    return value.toString();
}

} // namespace Vehicle_Powertrain_Transmission
} // namespace implementation
