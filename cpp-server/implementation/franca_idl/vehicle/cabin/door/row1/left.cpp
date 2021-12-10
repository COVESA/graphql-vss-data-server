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

#include "implementation.hpp"
#include "left.hpp"

namespace implementation {

namespace Vehicle_Cabin_Door_Row1_Left {

bool fromDoorsOpeningStatusToIsOpen(const DoorsStatus& doorsStatus)
{
    return doorsStatus.getFrontLeft();
}

} // namespace Vehicle_Cabin_Door_Row1_Left
} // namespace implementation
