// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
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
#include <graphql_vss_server_libs/support/permissions.hpp>
namespace permissions {
static inline constexpr ClientPermissions::Key Subscription_Vehicle_DELIVERY_INTERVAL_1_SECOND = 0;
static inline constexpr ClientPermissions::Key Subscription_Vehicle_REALTIME = 1;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Door_Row1_Left_IsOpen_READ = 15;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Door_Row1_Left_IsOpen_WRITE = 3;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Door_Row1_Right_IsOpen_READ = 16;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Door_Row1_Right_IsOpen_WRITE = 4;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Door_Row2_Left_IsOpen_READ = 17;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Door_Row2_Left_IsOpen_WRITE = 5;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Door_Row2_Right_IsOpen_READ = 18;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Door_Row2_Right_IsOpen_WRITE = 6;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_DoorCount_READ = 7;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Seat_Row1_Pos1_Heating_READ = 23;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Seat_Row1_Pos1_Heating_WRITE = 19;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Seat_Row1_Pos2_Heating_READ = 24;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Seat_Row1_Pos2_Heating_WRITE = 20;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Seat_Row2_Pos1_Heating_READ = 25;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Seat_Row2_Pos1_Heating_WRITE = 21;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Seat_Row2_Pos2_Heating_READ = 26;
static inline constexpr ClientPermissions::Key Vehicle_Cabin_Seat_Row2_Pos2_Heating_WRITE = 22;
static inline constexpr ClientPermissions::Key Vehicle_Chassis_Axle_Row1_Wheel_Left_Tire_Pressure_READ = 27;
static inline constexpr ClientPermissions::Key Vehicle_Chassis_Axle_Row1_Wheel_Right_Tire_Pressure_READ = 28;
static inline constexpr ClientPermissions::Key Vehicle_Chassis_Axle_Row2_Wheel_Left_Tire_Pressure_READ = 29;
static inline constexpr ClientPermissions::Key Vehicle_Chassis_Axle_Row2_Wheel_Right_Tire_Pressure_READ = 30;
static inline constexpr ClientPermissions::Key Vehicle_CurrentLocation_Altitude_READ = 8;
static inline constexpr ClientPermissions::Key Vehicle_CurrentLocation_Latitude_READ = 9;
static inline constexpr ClientPermissions::Key Vehicle_CurrentLocation_Longitude_READ = 10;
static inline constexpr ClientPermissions::Key Vehicle_Powertrain_CombustionEngine_Engine_Speed_READ = 14;
static inline constexpr ClientPermissions::Key Vehicle_Powertrain_FuelSystem_InstantConsumption_READ = 11;
static inline constexpr ClientPermissions::Key Vehicle_Powertrain_FuelSystem_Level_READ = 12;
static inline constexpr ClientPermissions::Key Vehicle_Powertrain_FuelSystem_TankCapacity_READ = 13;
static inline constexpr ClientPermissions::Key Vehicle_Powertrain_Transmission_CurrentGear_READ = 2;
static inline constexpr ClientPermissions::Key Vehicle_Powertrain_Transmission_DriveType_READ = 31;
static inline std::unordered_map<std::string_view, ClientPermissions::Key> getKnownPermissions()
{
    return std::unordered_map<std::string_view, ClientPermissions::Key> {
        { "Subscription.Vehicle.DELIVERY_INTERVAL_1_SECOND", Subscription_Vehicle_DELIVERY_INTERVAL_1_SECOND },
        { "Subscription.Vehicle.REALTIME", Subscription_Vehicle_REALTIME },
        { "Vehicle.Cabin.Door.Row1.Left.IsOpen_READ", Vehicle_Cabin_Door_Row1_Left_IsOpen_READ },
        { "Vehicle.Cabin.Door.Row1.Left.IsOpen_WRITE", Vehicle_Cabin_Door_Row1_Left_IsOpen_WRITE },
        { "Vehicle.Cabin.Door.Row1.Right.IsOpen_READ", Vehicle_Cabin_Door_Row1_Right_IsOpen_READ },
        { "Vehicle.Cabin.Door.Row1.Right.IsOpen_WRITE", Vehicle_Cabin_Door_Row1_Right_IsOpen_WRITE },
        { "Vehicle.Cabin.Door.Row2.Left.IsOpen_READ", Vehicle_Cabin_Door_Row2_Left_IsOpen_READ },
        { "Vehicle.Cabin.Door.Row2.Left.IsOpen_WRITE", Vehicle_Cabin_Door_Row2_Left_IsOpen_WRITE },
        { "Vehicle.Cabin.Door.Row2.Right.IsOpen_READ", Vehicle_Cabin_Door_Row2_Right_IsOpen_READ },
        { "Vehicle.Cabin.Door.Row2.Right.IsOpen_WRITE", Vehicle_Cabin_Door_Row2_Right_IsOpen_WRITE },
        { "Vehicle.Cabin.DoorCount_READ", Vehicle_Cabin_DoorCount_READ },
        { "Vehicle.Cabin.Seat.Row1.Pos1.Heating_READ", Vehicle_Cabin_Seat_Row1_Pos1_Heating_READ },
        { "Vehicle.Cabin.Seat.Row1.Pos1.Heating_WRITE", Vehicle_Cabin_Seat_Row1_Pos1_Heating_WRITE },
        { "Vehicle.Cabin.Seat.Row1.Pos2.Heating_READ", Vehicle_Cabin_Seat_Row1_Pos2_Heating_READ },
        { "Vehicle.Cabin.Seat.Row1.Pos2.Heating_WRITE", Vehicle_Cabin_Seat_Row1_Pos2_Heating_WRITE },
        { "Vehicle.Cabin.Seat.Row2.Pos1.Heating_READ", Vehicle_Cabin_Seat_Row2_Pos1_Heating_READ },
        { "Vehicle.Cabin.Seat.Row2.Pos1.Heating_WRITE", Vehicle_Cabin_Seat_Row2_Pos1_Heating_WRITE },
        { "Vehicle.Cabin.Seat.Row2.Pos2.Heating_READ", Vehicle_Cabin_Seat_Row2_Pos2_Heating_READ },
        { "Vehicle.Cabin.Seat.Row2.Pos2.Heating_WRITE", Vehicle_Cabin_Seat_Row2_Pos2_Heating_WRITE },
        { "Vehicle.Chassis.Axle.Row1.Wheel.Left.Tire.Pressure_READ", Vehicle_Chassis_Axle_Row1_Wheel_Left_Tire_Pressure_READ },
        { "Vehicle.Chassis.Axle.Row1.Wheel.Right.Tire.Pressure_READ", Vehicle_Chassis_Axle_Row1_Wheel_Right_Tire_Pressure_READ },
        { "Vehicle.Chassis.Axle.Row2.Wheel.Left.Tire.Pressure_READ", Vehicle_Chassis_Axle_Row2_Wheel_Left_Tire_Pressure_READ },
        { "Vehicle.Chassis.Axle.Row2.Wheel.Right.Tire.Pressure_READ", Vehicle_Chassis_Axle_Row2_Wheel_Right_Tire_Pressure_READ },
        { "Vehicle.CurrentLocation.Altitude_READ", Vehicle_CurrentLocation_Altitude_READ },
        { "Vehicle.CurrentLocation.Latitude_READ", Vehicle_CurrentLocation_Latitude_READ },
        { "Vehicle.CurrentLocation.Longitude_READ", Vehicle_CurrentLocation_Longitude_READ },
        { "Vehicle.Powertrain.CombustionEngine.Engine.Speed_READ", Vehicle_Powertrain_CombustionEngine_Engine_Speed_READ },
        { "Vehicle.Powertrain.FuelSystem.InstantConsumption_READ", Vehicle_Powertrain_FuelSystem_InstantConsumption_READ },
        { "Vehicle.Powertrain.FuelSystem.Level_READ", Vehicle_Powertrain_FuelSystem_Level_READ },
        { "Vehicle.Powertrain.FuelSystem.TankCapacity_READ", Vehicle_Powertrain_FuelSystem_TankCapacity_READ },
        { "Vehicle.Powertrain.Transmission.CurrentGear_READ", Vehicle_Powertrain_Transmission_CurrentGear_READ },
        { "Vehicle.Powertrain.Transmission.DriveType_READ", Vehicle_Powertrain_Transmission_DriveType_READ },
    };
}
} // namespace permissions
