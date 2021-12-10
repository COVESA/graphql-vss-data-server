// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
//   Author: Georgia Garcia (georgia@profusion.mobi),
//   Author: Pedro Soares (hspedro@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.

import gql from 'graphql-tag';

const setVehicleCabinDoorRow1Left = gql`
  mutation DoorRow1LeftMutation($input: Vehicle_Cabin_Door_Row1_Left_Input!) {
    setVehicleCabinDoorRow1Left(input: $input) {
      isDoorOpen
    }
  }
`;

export { setVehicleCabinDoorRow1Left as default };
