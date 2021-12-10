// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// WARNING! Do not edit this file manually, your changes will be overwritten.

#pragma once

#ifndef VEHICLESCHEMA_H
#define VEHICLESCHEMA_H

#include "graphqlservice/internal/Schema.h"

// Check if the library version is compatible with schemagen 3.6.0
static_assert(graphql::internal::MajorVersion == 3, "regenerate with schemagen: major version mismatch");
static_assert(graphql::internal::MinorVersion == 6, "regenerate with schemagen: minor version mismatch");

#include <memory>
#include <string>
#include <vector>

namespace graphql {
namespace vehicle {

enum class HasPermissionsDirectivePolicy
{
	RESOLVER,
	THROW
};

enum class SubscriptionDeliveryInterval
{
	DELIVERY_INTERVAL_5_SECONDS,
	DELIVERY_INTERVAL_1_SECOND,
	REALTIME
};

struct Vehicle_Cabin_Door_Row1_Left_Input
{
	std::optional<response::BooleanType> isOpen;
};

struct Vehicle_Cabin_Door_Row1_Right_Input
{
	std::optional<response::BooleanType> isOpen;
};

struct Vehicle_Cabin_Door_Row2_Left_Input
{
	std::optional<response::BooleanType> isOpen;
};

struct Vehicle_Cabin_Door_Row2_Right_Input
{
	std::optional<response::BooleanType> isOpen;
};

struct Vehicle_Cabin_Seat_Row1_Pos1_Input
{
	std::optional<response::Value> heating;
};

struct Vehicle_Cabin_Seat_Row1_Pos2_Input
{
	std::optional<response::Value> heating;
};

struct Vehicle_Cabin_Seat_Row2_Pos1_Input
{
	std::optional<response::Value> heating;
};

struct Vehicle_Cabin_Seat_Row2_Pos2_Input
{
	std::optional<response::Value> heating;
};

namespace object {

class Query;
class Subscription;
class Mutation;
class Vehicle;
class Vehicle_Cabin;
class Vehicle_CurrentLocation;
class Vehicle_Powertrain;
class Vehicle_Cabin_Door;
class Vehicle_Cabin_Seat;
class Vehicle_Powertrain_CombustionEngine;
class Vehicle_Powertrain_FuelSystem;
class Vehicle_Powertrain_Transmission;
class Vehicle_Cabin_Door_Row1;
class Vehicle_Cabin_Door_Row2;
class Vehicle_Cabin_Seat_Row1;
class Vehicle_Cabin_Seat_Row2;
class Vehicle_Powertrain_CombustionEngine_Engine;
class Vehicle_Cabin_Door_Row1_Left;
class Vehicle_Cabin_Door_Row1_Right;
class Vehicle_Cabin_Door_Row2_Left;
class Vehicle_Cabin_Door_Row2_Right;
class Vehicle_Cabin_Seat_Row1_Pos1;
class Vehicle_Cabin_Seat_Row1_Pos2;
class Vehicle_Cabin_Seat_Row2_Pos1;
class Vehicle_Cabin_Seat_Row2_Pos2;

class Query
	: public service::Object
{
protected:
	explicit Query();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle>> getVehicle(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveVehicle(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolve_schema(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolve_type(service::ResolverParams&& params);

	std::shared_ptr<schema::Schema> _schema;
};

class Subscription
	: public service::Object
{
protected:
	explicit Subscription();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle>> getVehicle(service::FieldParams&& params, SubscriptionDeliveryInterval&& deliveryIntervalArg) const;

private:
	std::future<service::ResolverResult> resolveVehicle(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Mutation
	: public service::Object
{
protected:
	explicit Mutation();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row1_Left>> applySetVehicleCabinDoorRow1Left(service::FieldParams&& params, Vehicle_Cabin_Door_Row1_Left_Input&& inputArg) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row1_Right>> applySetVehicleCabinDoorRow1Right(service::FieldParams&& params, Vehicle_Cabin_Door_Row1_Right_Input&& inputArg) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row2_Left>> applySetVehicleCabinDoorRow2Left(service::FieldParams&& params, Vehicle_Cabin_Door_Row2_Left_Input&& inputArg) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row2_Right>> applySetVehicleCabinDoorRow2Right(service::FieldParams&& params, Vehicle_Cabin_Door_Row2_Right_Input&& inputArg) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row1_Pos1>> applySetVehicleCabinSeatRow1Pos1(service::FieldParams&& params, Vehicle_Cabin_Seat_Row1_Pos1_Input&& inputArg) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row1_Pos2>> applySetVehicleCabinSeatRow1Pos2(service::FieldParams&& params, Vehicle_Cabin_Seat_Row1_Pos2_Input&& inputArg) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row2_Pos1>> applySetVehicleCabinSeatRow2Pos1(service::FieldParams&& params, Vehicle_Cabin_Seat_Row2_Pos1_Input&& inputArg) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row2_Pos2>> applySetVehicleCabinSeatRow2Pos2(service::FieldParams&& params, Vehicle_Cabin_Seat_Row2_Pos2_Input&& inputArg) const;

private:
	std::future<service::ResolverResult> resolveSetVehicleCabinDoorRow1Left(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSetVehicleCabinDoorRow1Right(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSetVehicleCabinDoorRow2Left(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSetVehicleCabinDoorRow2Right(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSetVehicleCabinSeatRow1Pos1(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSetVehicleCabinSeatRow1Pos2(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSetVehicleCabinSeatRow2Pos1(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSetVehicleCabinSeatRow2Pos2(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle
	: public service::Object
{
protected:
	explicit Vehicle();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin>> getCabin(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_CurrentLocation>> getCurrentLocation(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Powertrain>> getPowertrain(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveCabin(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveCurrentLocation(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolvePowertrain(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin
	: public service::Object
{
protected:
	explicit Vehicle_Cabin();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door>> getDoor(service::FieldParams&& params) const;
	virtual service::FieldResult<std::optional<response::Value>> getDoorCount(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat>> getSeat(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveDoor(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveDoorCount(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveSeat(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_CurrentLocation
	: public service::Object
{
protected:
	explicit Vehicle_CurrentLocation();

public:
	virtual service::FieldResult<std::optional<response::FloatType>> getAltitude(service::FieldParams&& params) const;
	virtual service::FieldResult<std::optional<response::FloatType>> getLatitude(service::FieldParams&& params) const;
	virtual service::FieldResult<std::optional<response::FloatType>> getLongitude(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveAltitude(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveLatitude(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveLongitude(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Powertrain
	: public service::Object
{
protected:
	explicit Vehicle_Powertrain();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Powertrain_CombustionEngine>> getCombustionEngine(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Powertrain_FuelSystem>> getFuelSystem(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Powertrain_Transmission>> getTransmission(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveCombustionEngine(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveFuelSystem(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveTransmission(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Door
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Door();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row1>> getRow1(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row2>> getRow2(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveRow1(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveRow2(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Seat
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Seat();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row1>> getRow1(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row2>> getRow2(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveRow1(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveRow2(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Powertrain_CombustionEngine
	: public service::Object
{
protected:
	explicit Vehicle_Powertrain_CombustionEngine();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Powertrain_CombustionEngine_Engine>> getEngine(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveEngine(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Powertrain_FuelSystem
	: public service::Object
{
protected:
	explicit Vehicle_Powertrain_FuelSystem();

public:
	virtual service::FieldResult<std::optional<response::FloatType>> getInstantConsumption(service::FieldParams&& params) const;
	virtual service::FieldResult<std::optional<response::Value>> getLevel(service::FieldParams&& params) const;
	virtual service::FieldResult<std::optional<response::FloatType>> getTankCapacity(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveInstantConsumption(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveLevel(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveTankCapacity(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Powertrain_Transmission
	: public service::Object
{
protected:
	explicit Vehicle_Powertrain_Transmission();

public:
	virtual service::FieldResult<std::optional<response::Value>> getCurrentGear(service::FieldParams&& params) const;
	virtual service::FieldResult<std::optional<response::StringType>> getDriveType(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveCurrentGear(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveDriveType(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Door_Row1
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Door_Row1();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row1_Left>> getLeft(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row1_Right>> getRight(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveLeft(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveRight(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Door_Row2
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Door_Row2();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row2_Left>> getLeft(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Door_Row2_Right>> getRight(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveLeft(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolveRight(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Seat_Row1
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Seat_Row1();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row1_Pos1>> getPos1(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row1_Pos2>> getPos2(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolvePos1(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolvePos2(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Seat_Row2
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Seat_Row2();

public:
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row2_Pos1>> getPos1(service::FieldParams&& params) const;
	virtual service::FieldResult<std::shared_ptr<Vehicle_Cabin_Seat_Row2_Pos2>> getPos2(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolvePos1(service::ResolverParams&& params);
	std::future<service::ResolverResult> resolvePos2(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Powertrain_CombustionEngine_Engine
	: public service::Object
{
protected:
	explicit Vehicle_Powertrain_CombustionEngine_Engine();

public:
	virtual service::FieldResult<std::optional<response::Value>> getSpeed(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveSpeed(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Door_Row1_Left
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Door_Row1_Left();

public:
	virtual service::FieldResult<std::optional<response::BooleanType>> getIsOpen(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveIsOpen(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Door_Row1_Right
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Door_Row1_Right();

public:
	virtual service::FieldResult<std::optional<response::BooleanType>> getIsOpen(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveIsOpen(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Door_Row2_Left
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Door_Row2_Left();

public:
	virtual service::FieldResult<std::optional<response::BooleanType>> getIsOpen(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveIsOpen(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Door_Row2_Right
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Door_Row2_Right();

public:
	virtual service::FieldResult<std::optional<response::BooleanType>> getIsOpen(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveIsOpen(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Seat_Row1_Pos1
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Seat_Row1_Pos1();

public:
	virtual service::FieldResult<std::optional<response::Value>> getHeating(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveHeating(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Seat_Row1_Pos2
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Seat_Row1_Pos2();

public:
	virtual service::FieldResult<std::optional<response::Value>> getHeating(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveHeating(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Seat_Row2_Pos1
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Seat_Row2_Pos1();

public:
	virtual service::FieldResult<std::optional<response::Value>> getHeating(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveHeating(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

class Vehicle_Cabin_Seat_Row2_Pos2
	: public service::Object
{
protected:
	explicit Vehicle_Cabin_Seat_Row2_Pos2();

public:
	virtual service::FieldResult<std::optional<response::Value>> getHeating(service::FieldParams&& params) const;

private:
	std::future<service::ResolverResult> resolveHeating(service::ResolverParams&& params);

	std::future<service::ResolverResult> resolve_typename(service::ResolverParams&& params);
};

} // namespace object

class Operations
	: public service::Request
{
public:
	explicit Operations(std::shared_ptr<object::Query> query, std::shared_ptr<object::Mutation> mutation, std::shared_ptr<object::Subscription> subscription);

private:
	std::shared_ptr<object::Query> _query;
	std::shared_ptr<object::Mutation> _mutation;
	std::shared_ptr<object::Subscription> _subscription;
};

std::shared_ptr<schema::Schema> GetSchema();

} // namespace vehicle
} // namespace graphql

#endif // VEHICLESCHEMA_H
