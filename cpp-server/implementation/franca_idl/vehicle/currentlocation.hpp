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

#include "attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/VehiclePositionEvent.hpp"
#include "implementation.hpp"

namespace implementation {

namespace Vehicle_CurrentLocation {

typedef org::genivi::vehicle::playgroundtypes::PlaygroundTypes PlaygroundTypes;
typedef PlaygroundTypes::StatusGPS StatusGPS;

struct IMPLEMENTATION_API VehiclePositionEvent
{
    const StatusGPS m_StatusGPS;

    typedef v1_org_genivi_vehicle_playground_PlaygroundProxy_1::Proxy::VehiclePositionEvent
        EventEmitter;
    typedef CommonAPIEventTraits<EventEmitter>::Handler::Tuple EventTuple;

    VehiclePositionEvent(const EventTuple&& event)
        : m_StatusGPS(std::get<0>(event))
    {
    }

    double getAltitude() const
    {
        const auto& position = m_StatusGPS.getStatusfGPSPosition();
        return position.getCurrentAltitude();
    }

    double getLatitude() const
    {
        const auto& position = m_StatusGPS.getStatusfGPSPosition();
        return position.getCurrentLatitude();
    }

    double getLongitude() const
    {
        const auto& position = m_StatusGPS.getStatusfGPSPosition();
        return position.getCurrentLongitude();
    }
};

double fromVehiclePositionToAltitude(const VehiclePositionEvent& vehiclePositionEvent)
{
    return vehiclePositionEvent.getAltitude();
}

double fromVehiclePositionToLatitude(const VehiclePositionEvent& vehiclePositionEvent)
{
    return vehiclePositionEvent.getLatitude();
}

double fromVehiclePositionToLongitude(const VehiclePositionEvent& vehiclePositionEvent)
{
    return vehiclePositionEvent.getLongitude();
}

} // namespace Vehicle_CurrentLocation

} // namespace implementation
