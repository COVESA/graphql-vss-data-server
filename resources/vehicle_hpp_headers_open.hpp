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
