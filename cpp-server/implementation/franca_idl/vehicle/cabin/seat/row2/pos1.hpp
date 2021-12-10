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

#include "franca_idl/vehicle/cabin/seat/heating.hpp"
#include "graphql_vss_server_libs/protocol/graphqlrequeststate.hpp"
#include "implementation.hpp"

namespace implementation {

namespace Vehicle_Cabin_Seat_Row2_Pos1 {

template <typename HeatingType>
void fromHeatingToSeatHeatingLevel(
    std::shared_ptr<GraphQLRequestState> state, const HeatingType& input)
{
    return fromHeatingToSeatHeatingLevelImplementation(state, input, 2);
}

template <typename HeatingType>
void fromHeatingToSeatHeatingStatus(
    std::shared_ptr<GraphQLRequestState> state, const HeatingType& input)
{
    return fromHeatingToSeatHeatingStatusImplementation(state, input, 2);
}

// TODO: Implement HeatingLevel
graphql::response::Value fromSeatHeatingLevelToHeating(const std::vector<uint8_t>& value)
{
    return fromSeatHeatingLevelToHeatingImplementation(value, 2);
}

graphql::response::Value fromSeatHeatingStatusToHeating(const std::vector<bool>& value)
{
    return fromSeatHeatingStatusToHeatingImplementation(value, 2);
}

} // namespace Vehicle_Cabin_Seat_Row2_Pos1
} // namespace implementation
