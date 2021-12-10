// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
//   Author: Gabriel Fernandes (g7fernandes@profusion.mobi),
//   Author: Georgia Garcia (georgia@profusion.mobi),
//   Author: Leandro Ferlin (leandroferlin@profusion.mobi),
//   Author: Pedro Soares (hspedro@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.

const permissions: number[] = [
  0 /* Subscription.Vehicle.DELIVERY_INTERVAL_1_SECOND */,
  1 /* Subscription.Vehicle.REALTIME */,
  15 /* Vehicle.Cabin.Door.Row1.Left.IsOpen_READ */,
  3 /* Vehicle.Cabin.Door.Row1.Left.IsOpen_WRITE */,
  16 /* Vehicle.Cabin.Door.Row1.Right.IsOpen_READ */,
  4 /* Vehicle.Cabin.Door.Row1.Right.IsOpen_WRITE */,
  17 /* Vehicle.Cabin.Door.Row2.Left.IsOpen_READ */,
  5 /* Vehicle.Cabin.Door.Row2.Left.IsOpen_WRITE */,
  18 /* Vehicle.Cabin.Door.Row2.Right.IsOpen_READ */,
  6 /* Vehicle.Cabin.Door.Row2.Right.IsOpen_WRITE */,
  7 /* Vehicle.Cabin.DoorCount_READ */,
  23 /* Vehicle.Cabin.Seat.Row1.Pos1.Heating_READ */,
  19 /* Vehicle.Cabin.Seat.Row1.Pos1.Heating_WRITE */,
  24 /* Vehicle.Cabin.Seat.Row1.Pos2.Heating_READ */,
  20 /* Vehicle.Cabin.Seat.Row1.Pos2.Heating_WRITE */,
  25 /* Vehicle.Cabin.Seat.Row2.Pos1.Heating_READ */,
  21 /* Vehicle.Cabin.Seat.Row2.Pos1.Heating_WRITE */,
  26 /* Vehicle.Cabin.Seat.Row2.Pos2.Heating_READ */,
  22 /* Vehicle.Cabin.Seat.Row2.Pos2.Heating_WRITE */,
  27 /* Vehicle.Chassis.Axle.Row1.Wheel.Left.Tire.Pressure_READ */,
  28 /* Vehicle.Chassis.Axle.Row1.Wheel.Right.Tire.Pressure_READ */,
  29 /* Vehicle.Chassis.Axle.Row2.Wheel.Left.Tire.Pressure_READ */,
  30 /* Vehicle.Chassis.Axle.Row2.Wheel.Right.Tire.Pressure_READ */,
  8 /* Vehicle.CurrentLocation.Altitude_READ */,
  9 /* Vehicle.CurrentLocation.Latitude_READ */,
  10 /* Vehicle.CurrentLocation.Longitude_READ */,
  14 /* Vehicle.Powertrain.CombustionEngine.Engine.Speed_READ */,
  11 /* Vehicle.Powertrain.FuelSystem.InstantConsumption_READ */,
  12 /* Vehicle.Powertrain.FuelSystem.Level_READ */,
  13 /* Vehicle.Powertrain.FuelSystem.TankCapacity_READ */,
  2 /* Vehicle.Powertrain.Transmission.CurrentGear_READ */,
  31 /* Vehicle.Powertrain.Transmission.DriveType_READ */,
];

export default permissions;
