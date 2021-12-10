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

#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/IsReverseGearOnAttribute.hpp"
#include "graphql_vss_server_libs/protocol/graphqlrequeststate.hpp"
#include "VehicleSchema.h"

namespace implementation {

namespace Vehicle_Powertrain_Transmission {

int selectCurrentGearFromIsReverseGearOnCurrentGear(std::shared_ptr<GraphQLRequestState> state)
{
	const bool isReverseGearOn =
		state
			->getSingleton<
				v1_org_genivi_vehicle_playground_PlaygroundProxy_1__IsReverseGearOnAttribute>()
			->getValue<bool>();

	if (isReverseGearOn)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

} // namespace Vehicle_Powertrain_Transmission
} // namespace implementation
