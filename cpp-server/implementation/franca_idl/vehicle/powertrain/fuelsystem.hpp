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

#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/CurrentTankVolumeEvent.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/ConsumptionAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/CapacityAttribute.hpp"
#include "implementation.hpp"
#include <bits/stdint-uintn.h>
#include <graphqlservice/GraphQLResponse.h>

namespace implementation {

namespace Vehicle_Powertrain_FuelSystem {

const double CAPACITY_MIN_VALUE = 0.0;
const double CAPACITY_MAX_VALUE = 255.0;
const double CAPACITY_MAX_VALUE_IN_LITERS = 80.0;

class Capacity
{
	double value;

public:
	Capacity(uint8_t capacity)
	{
		value =
			CAPACITY_MAX_VALUE_IN_LITERS * (capacity / (CAPACITY_MAX_VALUE - CAPACITY_MIN_VALUE));
	}

	double getValue() const
	{
		return value;
	}
};

struct IMPLEMENTATION_API CurrentTankVolumeEvent
{
	const uint8_t m_Volume;

	typedef v1_org_genivi_vehicle_playground_PlaygroundProxy_1::Proxy::CurrentTankVolumeEvent
		EventEmitter;
	typedef CommonAPIEventTraits<EventEmitter>::Handler::Tuple EventTuple;

	CurrentTankVolumeEvent(const EventTuple&& event)
		: m_Volume(std::get<0>(event))
	{
	}

	response::Value getLevel() const
	{
		return response::Value(m_Volume);
	}
};

IMPLEMENTATION_API response::Value fromCurrentTankVolumeToLevel(const CurrentTankVolumeEvent& currentTankVolumeEvent);

IMPLEMENTATION_API double fromTankCapacityToCapacity(const uint8_t& value);

} // namespace Vehicle_Powertrain_FuelSystem

} // namespace implementation
