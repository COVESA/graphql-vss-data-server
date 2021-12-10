// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
//   Author: Gabriel Fernandes (g7fernandes@profusion.mobi),
//   Author: Georgia Garcia (georgia@profusion.mobi),
//   Author: Leandro Ferlin (leandroferlin@profusion.mobi),
//   Author: Leonardo Ramos (leo.ramos@profusion.mobi),
//   Author: Paulo Henrique Carvalho de Morais (paulohc@profusion.mobi),
//   Author: Pedro Soares (hspedro@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.


#include "dispatcher/vehicle/cabin/seat/row1/pos1.hpp"
#include "dispatcher/vehicle/cabin/seat/row1/pos2.hpp"
#include "dispatcher/vehicle/cabin/seat/row2/pos1.hpp"
#include "dispatcher/vehicle/cabin/seat/row2/pos2.hpp"
#include "dispatcher/vehicle/powertrain/transmission.hpp"
#include "franca_idl/vehicle/cabin.hpp"
#include "franca_idl/vehicle/cabin/door/row1/left.hpp"
#include "franca_idl/vehicle/cabin/door/row1/right.hpp"
#include "franca_idl/vehicle/cabin/door/row2/left.hpp"
#include "franca_idl/vehicle/cabin/door/row2/right.hpp"
#include "franca_idl/vehicle/cabin/seat/row1/pos1.hpp"
#include "franca_idl/vehicle/cabin/seat/row1/pos2.hpp"
#include "franca_idl/vehicle/cabin/seat/row2/pos1.hpp"
#include "franca_idl/vehicle/cabin/seat/row2/pos2.hpp"
#include "franca_idl/vehicle/currentlocation.hpp"
#include "franca_idl/vehicle/powertrain/combustionengine/engine.hpp"
#include "franca_idl/vehicle/powertrain/fuelsystem.hpp"
#include "franca_idl/vehicle/powertrain/transmission.hpp"

#include <graphql_vss_server_libs/support/scalars.hpp>
#include <graphql_vss_server_libs/protocol/graphqlrequeststate.hpp>

#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/VehiclePositionEvent.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/ConsumptionAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/CapacityAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/CurrentTankVolumeEvent.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/DoorsOpeningStatusAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/EngineSpeedAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/SeatHeatingLevelAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/VehiclePositionEvent.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/VolumeAttribute.hpp"
#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/DrivePowerTransmissionAttribute.hpp"

#include "Vehicle.hpp"
#include "permissions_symbols.hpp"

namespace graphql::vehicle {

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1_Left>>
Mutation::applySetVehicleCabinDoorRow1Left(service::FieldParams&& params, Vehicle_Cabin_Door_Row1_Left_Input&& input) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);

    if (input.isOpen.has_value())
    {
        state->validate(permissions::Vehicle_Cabin_Door_Row1_Left_IsOpen_WRITE);
        implementation::Vehicle_Cabin_Door_Row1_Left::fromIsOpenToChangeDoorsState(
            state,
            input.isOpen.value()
        );
    }

    return std::make_shared<Vehicle_Cabin_Door_Row1_Left>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1_Right>>
Mutation::applySetVehicleCabinDoorRow1Right(service::FieldParams&& params, Vehicle_Cabin_Door_Row1_Right_Input&& input) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);

    if (input.isOpen.has_value())
    {
        state->validate(permissions::Vehicle_Cabin_Door_Row1_Right_IsOpen_WRITE);
        implementation::Vehicle_Cabin_Door_Row1_Right::fromIsOpenToChangeDoorsState(
            state,
            input.isOpen.value()
        );
    }

    return std::make_shared<Vehicle_Cabin_Door_Row1_Right>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2_Left>>
Mutation::applySetVehicleCabinDoorRow2Left(service::FieldParams&& params, Vehicle_Cabin_Door_Row2_Left_Input&& input) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);

    if (input.isOpen.has_value())
    {
        state->validate(permissions::Vehicle_Cabin_Door_Row2_Left_IsOpen_WRITE);
        implementation::Vehicle_Cabin_Door_Row2_Left::fromIsOpenToChangeDoorsState(
            state,
            input.isOpen.value()
        );
    }

    return std::make_shared<Vehicle_Cabin_Door_Row2_Left>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2_Right>>
Mutation::applySetVehicleCabinDoorRow2Right(service::FieldParams&& params, Vehicle_Cabin_Door_Row2_Right_Input&& input) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);

    if (input.isOpen.has_value())
    {
        state->validate(permissions::Vehicle_Cabin_Door_Row2_Right_IsOpen_WRITE);
        implementation::Vehicle_Cabin_Door_Row2_Right::fromIsOpenToChangeDoorsState(
            state,
            input.isOpen.value()
        );
    }

    return std::make_shared<Vehicle_Cabin_Door_Row2_Right>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1_Pos1>>
Mutation::applySetVehicleCabinSeatRow1Pos1(service::FieldParams&& params, Vehicle_Cabin_Seat_Row1_Pos1_Input&& input) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);

    if (input.heating.has_value())
    {
        state->validate(permissions::Vehicle_Cabin_Seat_Row1_Pos1_Heating_WRITE);
        switch (implementation::Vehicle_Cabin_Seat_Row1_Pos1::selectHeatingFromSeatHeatingStatus(state)) {
            case 0:
                implementation::Vehicle_Cabin_Seat_Row1_Pos1::fromHeatingToSeatHeatingLevel(
                    state,
                    validateRange<int8_t>(input.heating.value(), {-100, 100})
                );
                break;

            case 1:
                implementation::Vehicle_Cabin_Seat_Row1_Pos1::fromHeatingToSeatHeatingStatus(
                    state,
                    validateRange<int8_t>(input.heating.value(), {-100, 100})
                );
                break;

            default:
                throw std::invalid_argument("Unsupported deploy type.");
        }
    }

    return std::make_shared<Vehicle_Cabin_Seat_Row1_Pos1>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1_Pos2>>
Mutation::applySetVehicleCabinSeatRow1Pos2(service::FieldParams&& params, Vehicle_Cabin_Seat_Row1_Pos2_Input&& input) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);

    if (input.heating.has_value())
    {
        state->validate(permissions::Vehicle_Cabin_Seat_Row1_Pos2_Heating_WRITE);
        switch (implementation::Vehicle_Cabin_Seat_Row1_Pos2::selectHeatingFromSeatHeatingStatus(state)) {
            case 0:
                implementation::Vehicle_Cabin_Seat_Row1_Pos2::fromHeatingToSeatHeatingLevel(
                    state,
                    validateRange<int8_t>(input.heating.value(), {-100, 100})
                );
                break;

            case 1:
                implementation::Vehicle_Cabin_Seat_Row1_Pos2::fromHeatingToSeatHeatingStatus(
                    state,
                    validateRange<int8_t>(input.heating.value(), {-100, 100})
                );
                break;

            default:
                throw std::invalid_argument("Unsupported deploy type.");
        }
    }

    return std::make_shared<Vehicle_Cabin_Seat_Row1_Pos2>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2_Pos1>>
Mutation::applySetVehicleCabinSeatRow2Pos1(service::FieldParams&& params, Vehicle_Cabin_Seat_Row2_Pos1_Input&& input) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);

    if (input.heating.has_value())
    {
        state->validate(permissions::Vehicle_Cabin_Seat_Row2_Pos1_Heating_WRITE);
        switch (implementation::Vehicle_Cabin_Seat_Row2_Pos1::selectHeatingFromSeatHeatingStatus(state)) {
            case 0:
                implementation::Vehicle_Cabin_Seat_Row2_Pos1::fromHeatingToSeatHeatingLevel(
                    state,
                    validateRange<int8_t>(input.heating.value(), {-100, 100})
                );
                break;

            case 1:
                implementation::Vehicle_Cabin_Seat_Row2_Pos1::fromHeatingToSeatHeatingStatus(
                    state,
                    validateRange<int8_t>(input.heating.value(), {-100, 100})
                );
                break;

            default:
                throw std::invalid_argument("Unsupported deploy type.");
        }
    }

    return std::make_shared<Vehicle_Cabin_Seat_Row2_Pos1>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2_Pos2>>
Mutation::applySetVehicleCabinSeatRow2Pos2(service::FieldParams&& params, Vehicle_Cabin_Seat_Row2_Pos2_Input&& input) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);

    if (input.heating.has_value())
    {
        state->validate(permissions::Vehicle_Cabin_Seat_Row2_Pos2_Heating_WRITE);
        switch (implementation::Vehicle_Cabin_Seat_Row2_Pos2::selectHeatingFromSeatHeatingStatus(state)) {
            case 0:
                implementation::Vehicle_Cabin_Seat_Row2_Pos2::fromHeatingToSeatHeatingLevel(
                    state,
                    validateRange<int8_t>(input.heating.value(), {-100, 100})
                );
                break;

            case 1:
                implementation::Vehicle_Cabin_Seat_Row2_Pos2::fromHeatingToSeatHeatingStatus(
                    state,
                    validateRange<int8_t>(input.heating.value(), {-100, 100})
                );
                break;

            default:
                throw std::invalid_argument("Unsupported deploy type.");
        }
    }

    return std::make_shared<Vehicle_Cabin_Seat_Row2_Pos2>();
}

service::FieldResult<std::shared_ptr<object::Vehicle>>
Query::getVehicle(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle>();
}

service::FieldResult<std::shared_ptr<object::Vehicle>>
Subscription::getVehicle(service::FieldParams&& params, SubscriptionDeliveryInterval&& deliveryInterval) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    switch (deliveryInterval)
    {
        case SubscriptionDeliveryInterval::REALTIME:
            state->validate(permissions::Subscription_Vehicle_REALTIME);
            state->setSubscriptionmIntervalBetweenDeliveries(std::chrono::milliseconds(0));
            break;

        case SubscriptionDeliveryInterval::DELIVERY_INTERVAL_1_SECOND:
            state->validate(permissions::Subscription_Vehicle_DELIVERY_INTERVAL_1_SECOND);
            state->setSubscriptionmIntervalBetweenDeliveries(std::chrono::seconds(1));
            break;

        case SubscriptionDeliveryInterval::DELIVERY_INTERVAL_5_SECONDS:
            state->setSubscriptionmIntervalBetweenDeliveries(std::chrono::seconds(5));
            break;
    }

    return std::make_shared<Vehicle>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin>>
Vehicle::getCabin(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_CurrentLocation>>
Vehicle::getCurrentLocation(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_CurrentLocation>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain>>
Vehicle::getPowertrain(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Powertrain>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door>>
Vehicle_Cabin::getDoor(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Door>();
}

service::FieldResult<std::optional<response::Value>>
Vehicle_Cabin::getDoorCount(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_DoorCount_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__DoorsOpeningStatusAttribute>()->getValue<response::Value>(
        implementation::Vehicle_Cabin::fromDoorsOpeningStatusToDoorCount
    );
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat>>
Vehicle_Cabin::getSeat(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Seat>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1>>
Vehicle_Cabin_Door::getRow1(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Door_Row1>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2>>
Vehicle_Cabin_Door::getRow2(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Door_Row2>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1_Left>>
Vehicle_Cabin_Door_Row1::getLeft(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Door_Row1_Left>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row1_Right>>
Vehicle_Cabin_Door_Row1::getRight(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Door_Row1_Right>();
}

service::FieldResult<std::optional<bool>>
Vehicle_Cabin_Door_Row1_Left::getIsOpen(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_Door_Row1_Left_IsOpen_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__DoorsOpeningStatusAttribute>()->getValue<bool>(
        implementation::Vehicle_Cabin_Door_Row1_Left::fromDoorsOpeningStatusToIsOpen
    );
}

service::FieldResult<std::optional<bool>>
Vehicle_Cabin_Door_Row1_Right::getIsOpen(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_Door_Row1_Right_IsOpen_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__DoorsOpeningStatusAttribute>()->getValue<bool>(
        implementation::Vehicle_Cabin_Door_Row1_Right::fromDoorsOpeningStatusToIsOpen
    );
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2_Left>>
Vehicle_Cabin_Door_Row2::getLeft(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Door_Row2_Left>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Door_Row2_Right>>
Vehicle_Cabin_Door_Row2::getRight(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Door_Row2_Right>();
}

service::FieldResult<std::optional<bool>>
Vehicle_Cabin_Door_Row2_Left::getIsOpen(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_Door_Row2_Left_IsOpen_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__DoorsOpeningStatusAttribute>()->getValue<bool>(
        implementation::Vehicle_Cabin_Door_Row2_Left::fromDoorsOpeningStatusToIsOpen
    );
}

service::FieldResult<std::optional<bool>>
Vehicle_Cabin_Door_Row2_Right::getIsOpen(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_Door_Row2_Right_IsOpen_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__DoorsOpeningStatusAttribute>()->getValue<bool>(
        implementation::Vehicle_Cabin_Door_Row2_Right::fromDoorsOpeningStatusToIsOpen
    );
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1>>
Vehicle_Cabin_Seat::getRow1(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Seat_Row1>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2>>
Vehicle_Cabin_Seat::getRow2(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Seat_Row2>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1_Pos1>>
Vehicle_Cabin_Seat_Row1::getPos1(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Seat_Row1_Pos1>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row1_Pos2>>
Vehicle_Cabin_Seat_Row1::getPos2(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Seat_Row1_Pos2>();
}

service::FieldResult<std::optional<response::Value>>
Vehicle_Cabin_Seat_Row1_Pos1::getHeating(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_Seat_Row1_Pos1_Heating_READ);
    switch (implementation::Vehicle_Cabin_Seat_Row1_Pos1::selectHeatingFromSeatHeatingStatus(state)) {
        case 0:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingLevelAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Cabin_Seat_Row1_Pos1::fromSeatHeatingLevelToHeating
            );
        case 1:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingStatusAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Cabin_Seat_Row1_Pos1::fromSeatHeatingStatusToHeating
            );
        default:
            throw std::invalid_argument("Unsupported deploy type.");
    }
}

service::FieldResult<std::optional<response::Value>>
Vehicle_Cabin_Seat_Row1_Pos2::getHeating(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_Seat_Row1_Pos2_Heating_READ);
    switch (implementation::Vehicle_Cabin_Seat_Row1_Pos2::selectHeatingFromSeatHeatingStatus(state)) {
        case 0:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingLevelAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Cabin_Seat_Row1_Pos2::fromSeatHeatingLevelToHeating
            );
        case 1:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingStatusAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Cabin_Seat_Row1_Pos2::fromSeatHeatingStatusToHeating
            );
        default:
            throw std::invalid_argument("Unsupported deploy type.");
    }
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2_Pos1>>
Vehicle_Cabin_Seat_Row2::getPos1(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Seat_Row2_Pos1>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Cabin_Seat_Row2_Pos2>>
Vehicle_Cabin_Seat_Row2::getPos2(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Cabin_Seat_Row2_Pos2>();
}

service::FieldResult<std::optional<response::Value>>
Vehicle_Cabin_Seat_Row2_Pos1::getHeating(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_Seat_Row2_Pos1_Heating_READ);
    switch (implementation::Vehicle_Cabin_Seat_Row2_Pos1::selectHeatingFromSeatHeatingStatus(state)) {
        case 0:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingLevelAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Cabin_Seat_Row2_Pos1::fromSeatHeatingLevelToHeating
            );
        case 1:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingStatusAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Cabin_Seat_Row2_Pos1::fromSeatHeatingStatusToHeating
            );
        default:
            throw std::invalid_argument("Unsupported deploy type.");
    }
}

service::FieldResult<std::optional<response::Value>>
Vehicle_Cabin_Seat_Row2_Pos2::getHeating(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Cabin_Seat_Row2_Pos2_Heating_READ);
    switch (implementation::Vehicle_Cabin_Seat_Row2_Pos2::selectHeatingFromSeatHeatingStatus(state)) {
        case 0:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingLevelAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Cabin_Seat_Row2_Pos2::fromSeatHeatingLevelToHeating
            );
        case 1:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__SeatHeatingStatusAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Cabin_Seat_Row2_Pos2::fromSeatHeatingStatusToHeating
            );
        default:
            throw std::invalid_argument("Unsupported deploy type.");
    }
}

service::FieldResult<std::optional<double>>
Vehicle_CurrentLocation::getAltitude(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_CurrentLocation_Altitude_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__VehiclePositionEvent>()->getValue<double>(
        implementation::Vehicle_CurrentLocation::fromVehiclePositionToAltitude
    );
}

service::FieldResult<std::optional<double>>
Vehicle_CurrentLocation::getLatitude(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_CurrentLocation_Latitude_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__VehiclePositionEvent>()->getValue<double>(
        implementation::Vehicle_CurrentLocation::fromVehiclePositionToLatitude
    );
}

service::FieldResult<std::optional<double>>
Vehicle_CurrentLocation::getLongitude(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_CurrentLocation_Longitude_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__VehiclePositionEvent>()->getValue<double>(
        implementation::Vehicle_CurrentLocation::fromVehiclePositionToLongitude
    );
}

service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_CombustionEngine>>
Vehicle_Powertrain::getCombustionEngine(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Powertrain_CombustionEngine>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_FuelSystem>>
Vehicle_Powertrain::getFuelSystem(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Powertrain_FuelSystem>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_Transmission>>
Vehicle_Powertrain::getTransmission(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Powertrain_Transmission>();
}

service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_CombustionEngine_Engine>>
Vehicle_Powertrain_CombustionEngine::getEngine(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Powertrain_CombustionEngine_Engine>();
}

service::FieldResult<std::optional<response::Value>>
Vehicle_Powertrain_CombustionEngine_Engine::getSpeed(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_CombustionEngine_Engine_Speed_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__EngineSpeedAttribute>()->getValue<response::Value>();
}

service::FieldResult<std::optional<double>>
Vehicle_Powertrain_FuelSystem::getInstantConsumption(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_FuelSystem_InstantConsumption_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__ConsumptionAttribute>()->getValue<double>();
}

service::FieldResult<std::optional<response::Value>>
Vehicle_Powertrain_FuelSystem::getLevel(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_FuelSystem_Level_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__CurrentTankVolumeEvent>()->getValue<response::Value>(
        implementation::Vehicle_Powertrain_FuelSystem::fromCurrentTankVolumeToLevel
    );
}

service::FieldResult<std::optional<double>>
Vehicle_Powertrain_FuelSystem::getTankCapacity(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_FuelSystem_TankCapacity_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__CapacityAttribute>()->getValue<double>(
        implementation::Vehicle_Powertrain_FuelSystem::fromTankCapacityToCapacity
    );
}

service::FieldResult<std::optional<response::Value>>
Vehicle_Powertrain_Transmission::getCurrentGear(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_Transmission_CurrentGear_READ);
    switch (implementation::Vehicle_Powertrain_Transmission::selectCurrentGearFromIsReverseGearOnCurrentGear(state)) {
        case 0:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__CurrentGearAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Powertrain_Transmission::fromCurrentGearToCurrentGear
            );
        case 1:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__IsReverseGearOnAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Powertrain_Transmission::fromIsReverseGearOnToCurrentGear
            );
        default:
            throw std::invalid_argument("Unsupported deploy type.");
    }
}

service::FieldResult<std::optional<std::string>>
Vehicle_Powertrain_Transmission::getDriveType(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_Transmission_DriveType_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__DrivePowerTransmissionAttribute>()->getValue<std::string>(
        implementation::Vehicle_Powertrain_Transmission::fromDrivePowerTransmissionToDriveType
    );
}

} // namespace graphql::vehicle
