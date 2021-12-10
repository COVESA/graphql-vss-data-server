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

#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/SeatHeatingLevelAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/SeatHeatingStatusAttribute.hpp"
#include "graphql_vss_server_libs/protocol/graphqlrequeststate.hpp"
#include <stdexcept>

using PlaygroundProxy = v1_org_genivi_vehicle_playground_PlaygroundProxy_1;

typedef org::genivi::vehicle::playgroundtypes::PlaygroundTypes PlaygroundTypes;

template <typename HeatingType>
void fromHeatingToSeatHeatingLevelImplementation(
	std::shared_ptr<GraphQLRequestState> state, const HeatingType& input, int index)
{
	const auto& lockedHeatingLevel =
		state
			->getSingleton<
				v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingLevelAttribute>()
			->getValue()
			.value;
	std::vector<uint8_t> seatHeatingLevel;

	for (int i = 0; i < 8; i++)
	{
		seatHeatingLevel[i] = lockedHeatingLevel[i];
	}
	seatHeatingLevel[index] = input;

	state
		->getSingleton<
			v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingLevelAttribute>()
		->mutateValue(seatHeatingLevel);
}

template <typename HeatingType>
void fromHeatingToSeatHeatingStatusImplementation(
	std::shared_ptr<GraphQLRequestState> state, const HeatingType& input, int index)
{
	const auto& lockedHeatingStatus =
		state
			->getSingleton<
				v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingStatusAttribute>()
			->getValue()
			.value;
	std::vector<bool> seatHeatingStatus;
	for (int i = 0; i < 8; i++)
	{
		seatHeatingStatus[i] = lockedHeatingStatus[i];
	}
	seatHeatingStatus[index] = input;

	state
		->getSingleton<
			v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingStatusAttribute>()
		->mutateValue(seatHeatingStatus);
}

graphql::response::Value
fromSeatHeatingLevelToHeatingImplementation(const std::vector<uint8_t>& value, int index)
{
	return graphql::response::Value(value[index]);
}

graphql::response::Value
fromSeatHeatingStatusToHeatingImplementation(const std::vector<bool>& value, int index)
{
	const bool status = value[index];

	if (status)
	{
		throw std::runtime_error(
			"If enabled, heating must be retrieved from its level instead of status.");
	}
	else
	{
		return graphql::response::Value(0);
	}
}
