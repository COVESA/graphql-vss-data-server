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

#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/SeatHeatingStatusAttribute.hpp"
#include "graphql_vss_server_libs/protocol/graphqlrequeststate.hpp"

namespace implementation {

enum SeatsID : uint8_t
{
	FRONT_LEFT,
	FRONT_RIGHT,
	REAR_LEFT,
	REAR_RIGHT
};

int selectorHeatingFromSeatHeatingStatus(std::shared_ptr<GraphQLRequestState> state, SeatsID seatId)
{
	const std::vector<bool>& seatHeatingStatus =
		state
			->getSingleton<
				v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingStatusAttribute>()
			->getValue<std::vector<bool>>();

	const bool isHeatingOn = seatHeatingStatus[seatId];
	if (isHeatingOn)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

} // namespace implementation
