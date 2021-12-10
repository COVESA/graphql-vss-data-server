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

#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/DoorsOpeningStatusAttribute.hpp"
#include "proxies/v1_org_genivi_vehicle_playground_PlaygroundProxy_1.hpp"
#include "graphql_vss_server_libs/protocol/graphqlrequeststate.hpp"
#include <vector>
#include "implementation.hpp"

namespace implementation {

namespace Vehicle_Cabin_Door_Row2_Left {

using PlaygroundProxy = v1_org_genivi_vehicle_playground_PlaygroundProxy_1;

typedef org::genivi::vehicle::playgroundtypes::PlaygroundTypes PlaygroundTypes;
typedef PlaygroundTypes::DoorsStatus DoorsStatus;
typedef PlaygroundTypes::DoorCommand DoorCommand;
typedef DoorCommand::Literal Literal;
typedef PlaygroundTypes::CarDoorsCommand CarDoorsCommand;

template <typename IsOpenInputType>
void fromIsOpenToChangeDoorsState(
    std::shared_ptr<GraphQLRequestState> state, const IsOpenInputType& input)
{
    CommonAPI::CallStatus status;
    const CommonAPI::CallInfo* info;

    auto proxy = state->getSingleton<PlaygroundProxy>()->proxy;

    DoorCommand rearLeft;
    if (input) {
        rearLeft = DoorCommand(Literal::OPEN_DOOR);
    } else {
        rearLeft = DoorCommand(Literal::CLOSE_DOOR);
    }
    DoorCommand frontLeft = DoorCommand(Literal::NOTHING);
    DoorCommand frontRight = DoorCommand(Literal::NOTHING);
    DoorCommand rearRight = DoorCommand(Literal::NOTHING);

    CarDoorsCommand carDoorsCommand = CarDoorsCommand(frontLeft, frontRight, rearLeft, rearRight);
    proxy->changeDoorsState(carDoorsCommand, status, info);
    if (status != CommonAPI::CallStatus::SUCCESS)
    {
        throw std::runtime_error("Error while fetching for Vehicle_Cabin_Door_Row1_Left"
                                 "value");
    }
}

IMPLEMENTATION_API bool fromDoorsOpeningStatusToIsOpen(const DoorsStatus& doorsStatus);

} // namespace Vehicle_Cabin_Door_Row2_Left
} // namespace implementation
