# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gabriel Fernandes Silva (g7fernandes@profusion.mobi),
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.

project(commonapi-wrappers)

cmake_minimum_required(VERSION 3.13.0)
find_program(CLANG_CXX_PATH clang++)

set(CMAKE_CXX_COMPILER ${CLANG_CXX_PATH})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(CommonAPI 3.2.0 REQUIRED)
find_package(CommonAPI-SomeIP 3.2.0 REQUIRED)
find_package (vsomeip3 3.1.0 REQUIRED)

set(PRJ_GEN_PATH "generated")
set(PRJ_INCLUDE_PATH "include")

message("COMMONAPI_INCLUDE_DIRS: ${COMMONAPI_INCLUDE_DIRS}")
message("COMMONAPI_SOMEIP_INCLUDE_DIRS: ${COMMONAPI_SOMEIP_INCLUDE_DIRS}")

include_directories(
    ${PRJ_GEN_PATH}
    ${PRJ_INCLUDE_PATH}
    ${COMMONAPI_INCLUDE_DIRS}
    ${COMMONAPI_SOMEIP_INCLUDE_DIRS}
    ${VSOMEIP3_INCLUDE_DIRS}
)

function(add_commonapi_internal TYPE SUBTYPE NAME)
  string(TOLOWER ${TYPE} TYPE_LOWERCASE)
  string(TOLOWER ${SUBTYPE} SUBTYPE_LOWERCASE)
  file(GLOB_RECURSE FILES ${PRJ_GEN_PATH}/${NAME}/${TYPE_LOWERCASE}/${SUBTYPE_LOWERCASE}/*.cpp)
  list(LENGTH FILES LEN)
  list(SUBLIST ARGV 3 -1 DEPS)
  message(STATUS "${NAME}.${TYPE}${SUBTYPE} has ${LEN} cpp files")
  if(LEN GREATER 0)
    set(LIBNAME ${NAME}.${TYPE}${SUBTYPE})
    add_library(${LIBNAME} SHARED ${FILES})
    target_link_libraries(${LIBNAME} ${DEPS})
  endif()
  install(TARGETS ${LIBNAME})
endfunction()

function(add_commonapi_wrapper NAME)
  add_commonapi_internal(SomeIP Common ${NAME} CommonAPI-SomeIP)
  add_commonapi_internal(SomeIP Proxy ${NAME} ${NAME}.SomeIPCommon CommonAPI-SomeIP)
  add_commonapi_internal(SomeIP Stub ${NAME} ${NAME}.SomeIPCommon CommonAPI-SomeIP)
endfunction()

file(GLOB WRAPPERS LIST_DIRECTORIES true RELATIVE ${CMAKE_SOURCE_DIR}/${PRJ_GEN_PATH}/ ${CMAKE_SOURCE_DIR}/${PRJ_GEN_PATH}/*)
foreach(NAME IN LISTS WRAPPERS)
  add_commonapi_wrapper(${NAME})
endforeach()

file(GLOB HEADER_DIRS LIST_DIRECTORIES true ${CMAKE_SOURCE_DIR}/${PRJ_INCLUDE_PATH}/*)
install(DIRECTORY ${HEADER_DIRS} TYPE INCLUDE FILES_MATCHING PATTERN "*.hpp")
