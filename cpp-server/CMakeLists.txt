# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
#   Author: Gabriel Fernandes (g7fernandes@profusion.mobi),
#   Author: Georgia Garcia (georgia@profusion.mobi),
#   Author: Leandro Ferlin (leandroferlin@profusion.mobi),
#   Author: Leonardo Ramos (leo.ramos@profusion.mobi),
#   Author: Paulo Henrique Carvalho de Morais (paulohc@profusion.mobi),
#   Author: Pedro Soares (hspedro@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.

project(graphql-data-server)
set(GRAPHQL_DATA_SERVER_VERSION 0.1.0)

cmake_minimum_required(VERSION 3.13.0)

find_package(Python3 COMPONENTS Interpreter)

set(CMAKE_CXX_STANDARD 17)
set(VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused -Wunused-function -ffunction-sections -fdata-sections ")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections -Wl,--as-needed ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections -Wl,--as-needed ")

###############################################################################
# create the commandline variables

OPTION(
  BUILD_SHARED_LIBS
  "Speed up compile times by using shared libraries (slower execution!)"
  OFF
)

OPTION(
  UPDATE_STUBS
  "Enable build target to run schemagen and update stubs"
  OFF
)

OPTION(
  DISABLE_INTROSPECTION
  "Disables introspection on the server"
  OFF
)

OPTION(
  DISABLE_PERMISSIONS
  "Disables permissions check. WARNING: this allows every request!"
  OFF
)

OPTION(
  SANITIZE_THREAD
  "Enables Clang thread sanitizer"
  OFF
)

OPTION(
  SANITIZE_ADDRESS
  "Enables Clang address sanitizer"
  OFF
)
###############################################################################
# set up compile flags

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug" OR BUILD_SHARED_LIBS STREQUAL "ON")
  set(BUILD_SHARED_LIBS "ON")
  add_compile_definitions(BMW_CPP_GRAPHQL_BUILD_SHARED_LIBS=1)
endif()

###############################################################################
# add COMMONAPI install path to cmake find root path
find_package(PkgConfig)

find_package(Threads REQUIRED)
find_package(Boost 1.71 COMPONENTS system program_options REQUIRED)

find_package(CommonAPI 3.2.0 REQUIRED)
find_package(CommonAPI-SomeIP 3.2.0 REQUIRED)
pkg_check_modules(DLT REQUIRED automotive-dlt)

find_package(pegtl 3.2.0 REQUIRED)
find_package(cppgraphqlgen 3.6.0 REQUIRED)
find_package(OpenSSL REQUIRED)

find_package(graphql_vss_server_libs REQUIRED)

set(LibDirs "")
if(DEFINED CMAKE_PREFIX_PATH)
    # The includes of cppgraphqlgen can't be found without this if it is
  # installed outside /usr/local
      foreach(ITEM ${CMAKE_PREFIX_PATH})
          message(STATUS "CMAKE_PREFIX_PATH: " ${ITEM})
          include_directories(SYSTEM "${ITEM}/include")
          list(APPEND LibDirs "${ITEM}/lib")
    endforeach()
endif()

if(NOT DISABLE_PERMISSIONS)
  add_custom_target(
    generate-keys
    ALL
    COMMAND
      KEYS_PATH=${CMAKE_CURRENT_BINARY_DIR}/keys/
      ${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate_keys.sh)
  set(PERMISSIONS_FLAGS "DISABLE_PERMISSIONS=false")
else()
  set(PERMISSIONS_FLAGS "DISABLE_PERMISSIONS=true")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message("Activating DEBUG flags")
  if (SANITIZE_ADDRESS AND SANITIZE_THREAD)
    message(FATAL_ERROR "Address sanitizer not allowed with Thread sanitizer.")
  elseif (SANITIZE_ADDRESS)
    message("Activating ADDRESS sanitizer")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG
        " -fsanitize=address -fno-omit-frame-pointer ")
  elseif (SANITIZE_THREAD)
    message("Activating THREAD sanitizer")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG
        " -fsanitize=thread ")
  endif()
endif()

add_library(commonapi_glue INTERFACE)
target_include_directories(
  commonapi_glue
  INTERFACE
  ${COMMONAPI_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/generated
  ${CMAKE_CURRENT_SOURCE_DIR}/../commonapi-wrappers/playground/include
)
list(JOIN LibDirs " " LibDirsString)
target_link_directories(
  commonapi_glue
  INTERFACE
  ${LibDirsString}
)
target_link_libraries(
  commonapi_glue
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/../commonapi-wrappers/playground/lib/liborg.genivi.vehicle.playground.SomeIPCommon.so
  ${CMAKE_CURRENT_SOURCE_DIR}/../commonapi-wrappers/playground/lib/liborg.genivi.vehicle.playground.SomeIPProxy.so
)

add_subdirectory(implementation)
add_subdirectory(generated)

OPTION(BUILD_EXAMPLES "Build examples" OFF)
if(BUILD_EXAMPLES)
  message(STATUS "Including examples/")
  add_subdirectory(examples/commonapi-usage-examples)
  add_subdirectory(examples/someip_performance)
endif()

add_executable(graphql-data-server src/server.cpp)
target_compile_definitions(
  graphql-data-server
  PRIVATE
  GRAPHQL_DATA_SERVER_VERSION="${GRAPHQL_DATA_SERVER_VERSION}"
  ${PERMISSIONS_FLAGS}
)
target_link_libraries(
  graphql-data-server
  vehiclegraphql
  graphql_vss_server_libs::graphql_vss_server_libs-protocol
  Boost::program_options
)
if(NOT BUILD_SHARED_LIBS)
  install(TARGETS graphql-data-server)
endif()

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
  enable_testing()
endif()
