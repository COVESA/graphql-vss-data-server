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

#include <bits/stdint-uintn.h>
#include "fuelsystem.hpp"
namespace implementation {

namespace Vehicle_Powertrain_FuelSystem {

double fromTankCapacityToCapacity(const uint8_t& value)
{
	Capacity capacity = Capacity(value);
	return capacity.getValue();
}

response::Value fromCurrentTankVolumeToLevel(const CurrentTankVolumeEvent& currentTankVolumeEvent)
{
	return currentTankVolumeEvent.getLevel();
}

} // namespace Vehicle_Powertrain_FuelSystem
} // namespace implementation
