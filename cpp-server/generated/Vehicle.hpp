#pragma once
// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG), Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA, Author: Leonardo Ramos (leo.ramos@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.


#ifdef VEHICLE_API
#undef VEHICLE_API
#endif
#if defined(BMW_CPP_GRAPHQL_BUILD_SHARED_LIBS) && BMW_CPP_GRAPHQL_BUILD_SHARED_LIBS
#define VEHICLE_API __attribute__ ((visibility ("default")))
#else
#define VEHICLE_API
#endif

#include "VehicleSchema.h"


namespace implementation {
} // namespace implementation

namespace graphql::vehicle {

using namespace graphql;
class Mutation;
class Query;
class Subscription;
class Vehicle;
class Vehicle_Cabin;
class Vehicle_Cabin_Door;
class Vehicle_Cabin_Door_Row1;
class Vehicle_Cabin_Door_Row1_Left;
class Vehicle_Cabin_Door_Row1_Right;
class Vehicle_Cabin_Door_Row2;
class Vehicle_Cabin_Door_Row2_Left;
class Vehicle_Cabin_Door_Row2_Right;
class Vehicle_Cabin_Seat;
class Vehicle_Cabin_Seat_Row1;
class Vehicle_Cabin_Seat_Row1_Pos1;
class Vehicle_Cabin_Seat_Row1_Pos2;
class Vehicle_Cabin_Seat_Row2;
class Vehicle_Cabin_Seat_Row2_Pos1;
class Vehicle_Cabin_Seat_Row2_Pos2;
class Vehicle_CurrentLocation;
class Vehicle_Powertrain;
class Vehicle_Powertrain_CombustionEngine;
class Vehicle_Powertrain_CombustionEngine_Engine;
class Vehicle_Powertrain_FuelSystem;
class Vehicle_Powertrain_Transmission;

class VEHICLE_API Mutation : public object::Mutation
{
public:
    VEHICLE_API explicit Mutation() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1_Left>>
    applySetVehicleCabinDoorRow1Left(service::FieldParams&& params, Vehicle_Cabin_Door_Row1_Left_Input&& input) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1_Right>>
    applySetVehicleCabinDoorRow1Right(service::FieldParams&& params, Vehicle_Cabin_Door_Row1_Right_Input&& input) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2_Left>>
    applySetVehicleCabinDoorRow2Left(service::FieldParams&& params, Vehicle_Cabin_Door_Row2_Left_Input&& input) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2_Right>>
    applySetVehicleCabinDoorRow2Right(service::FieldParams&& params, Vehicle_Cabin_Door_Row2_Right_Input&& input) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1_Pos1>>
    applySetVehicleCabinSeatRow1Pos1(service::FieldParams&& params, Vehicle_Cabin_Seat_Row1_Pos1_Input&& input) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1_Pos2>>
    applySetVehicleCabinSeatRow1Pos2(service::FieldParams&& params, Vehicle_Cabin_Seat_Row1_Pos2_Input&& input) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2_Pos1>>
    applySetVehicleCabinSeatRow2Pos1(service::FieldParams&& params, Vehicle_Cabin_Seat_Row2_Pos1_Input&& input) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2_Pos2>>
    applySetVehicleCabinSeatRow2Pos2(service::FieldParams&& params, Vehicle_Cabin_Seat_Row2_Pos2_Input&& input) const final;
};

class VEHICLE_API Query : public object::Query
{
public:
    VEHICLE_API explicit Query() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle>>
    getVehicle(service::FieldParams&& params) const final;
};

class VEHICLE_API Subscription : public object::Subscription
{
public:
    VEHICLE_API explicit Subscription() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle>>
    getVehicle(service::FieldParams&& params, SubscriptionDeliveryInterval&& deliveryInterval) const final;
};

class Vehicle : public object::Vehicle
{
public:
    explicit Vehicle() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin>>
    getCabin(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_CurrentLocation>>
    getCurrentLocation(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain>>
    getPowertrain(service::FieldParams&& params) const final;
};

class Vehicle_Cabin : public object::Vehicle_Cabin
{
public:
    explicit Vehicle_Cabin() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door>>
    getDoor(service::FieldParams&& params) const final;

    service::FieldResult<std::optional<response::Value>>
    getDoorCount(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat>>
    getSeat(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Door : public object::Vehicle_Cabin_Door
{
public:
    explicit Vehicle_Cabin_Door() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1>>
    getRow1(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2>>
    getRow2(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Door_Row1 : public object::Vehicle_Cabin_Door_Row1
{
public:
    explicit Vehicle_Cabin_Door_Row1() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1_Left>>
    getLeft(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1_Right>>
    getRight(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Door_Row1_Left : public object::Vehicle_Cabin_Door_Row1_Left
{
public:
    explicit Vehicle_Cabin_Door_Row1_Left() = default;

    service::FieldResult<std::optional<bool>>
    getIsOpen(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Door_Row1_Right : public object::Vehicle_Cabin_Door_Row1_Right
{
public:
    explicit Vehicle_Cabin_Door_Row1_Right() = default;

    service::FieldResult<std::optional<bool>>
    getIsOpen(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Door_Row2 : public object::Vehicle_Cabin_Door_Row2
{
public:
    explicit Vehicle_Cabin_Door_Row2() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2_Left>>
    getLeft(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2_Right>>
    getRight(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Door_Row2_Left : public object::Vehicle_Cabin_Door_Row2_Left
{
public:
    explicit Vehicle_Cabin_Door_Row2_Left() = default;

    service::FieldResult<std::optional<bool>>
    getIsOpen(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Door_Row2_Right : public object::Vehicle_Cabin_Door_Row2_Right
{
public:
    explicit Vehicle_Cabin_Door_Row2_Right() = default;

    service::FieldResult<std::optional<bool>>
    getIsOpen(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Seat : public object::Vehicle_Cabin_Seat
{
public:
    explicit Vehicle_Cabin_Seat() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1>>
    getRow1(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2>>
    getRow2(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Seat_Row1 : public object::Vehicle_Cabin_Seat_Row1
{
public:
    explicit Vehicle_Cabin_Seat_Row1() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1_Pos1>>
    getPos1(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1_Pos2>>
    getPos2(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Seat_Row1_Pos1 : public object::Vehicle_Cabin_Seat_Row1_Pos1
{
public:
    explicit Vehicle_Cabin_Seat_Row1_Pos1() = default;

    service::FieldResult<std::optional<response::Value>>
    getHeating(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Seat_Row1_Pos2 : public object::Vehicle_Cabin_Seat_Row1_Pos2
{
public:
    explicit Vehicle_Cabin_Seat_Row1_Pos2() = default;

    service::FieldResult<std::optional<response::Value>>
    getHeating(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Seat_Row2 : public object::Vehicle_Cabin_Seat_Row2
{
public:
    explicit Vehicle_Cabin_Seat_Row2() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2_Pos1>>
    getPos1(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2_Pos2>>
    getPos2(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Seat_Row2_Pos1 : public object::Vehicle_Cabin_Seat_Row2_Pos1
{
public:
    explicit Vehicle_Cabin_Seat_Row2_Pos1() = default;

    service::FieldResult<std::optional<response::Value>>
    getHeating(service::FieldParams&& params) const final;
};

class Vehicle_Cabin_Seat_Row2_Pos2 : public object::Vehicle_Cabin_Seat_Row2_Pos2
{
public:
    explicit Vehicle_Cabin_Seat_Row2_Pos2() = default;

    service::FieldResult<std::optional<response::Value>>
    getHeating(service::FieldParams&& params) const final;
};

class Vehicle_CurrentLocation : public object::Vehicle_CurrentLocation
{
public:
    explicit Vehicle_CurrentLocation() = default;

    service::FieldResult<std::optional<double>>
    getAltitude(service::FieldParams&& params) const final;

    service::FieldResult<std::optional<double>>
    getLatitude(service::FieldParams&& params) const final;

    service::FieldResult<std::optional<double>>
    getLongitude(service::FieldParams&& params) const final;
};

class Vehicle_Powertrain : public object::Vehicle_Powertrain
{
public:
    explicit Vehicle_Powertrain() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_CombustionEngine>>
    getCombustionEngine(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_FuelSystem>>
    getFuelSystem(service::FieldParams&& params) const final;

    service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_Transmission>>
    getTransmission(service::FieldParams&& params) const final;
};

class Vehicle_Powertrain_CombustionEngine : public object::Vehicle_Powertrain_CombustionEngine
{
public:
    explicit Vehicle_Powertrain_CombustionEngine() = default;

    service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_CombustionEngine_Engine>>
    getEngine(service::FieldParams&& params) const final;
};

class Vehicle_Powertrain_CombustionEngine_Engine : public object::Vehicle_Powertrain_CombustionEngine_Engine
{
public:
    explicit Vehicle_Powertrain_CombustionEngine_Engine() = default;

    service::FieldResult<std::optional<response::Value>>
    getSpeed(service::FieldParams&& params) const final;
};

class Vehicle_Powertrain_FuelSystem : public object::Vehicle_Powertrain_FuelSystem
{
public:
    explicit Vehicle_Powertrain_FuelSystem() = default;

    service::FieldResult<std::optional<double>>
    getInstantConsumption(service::FieldParams&& params) const final;

    service::FieldResult<std::optional<response::Value>>
    getLevel(service::FieldParams&& params) const final;

    service::FieldResult<std::optional<double>>
    getTankCapacity(service::FieldParams&& params) const final;
};

class Vehicle_Powertrain_Transmission : public object::Vehicle_Powertrain_Transmission
{
public:
    explicit Vehicle_Powertrain_Transmission() = default;

    service::FieldResult<std::optional<response::Value>>
    getCurrentGear(service::FieldParams&& params) const final;

    service::FieldResult<std::optional<std::string>>
    getDriveType(service::FieldParams&& params) const final;
};

} // namespace graphql::vehicle
