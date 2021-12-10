#!/bin/bash

# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gabriel Fernandes (g7fernandes@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.


# THIS FILE IS AN EXAMPLE

########### SPECIFY OTHER RELEASES ############
## If you want to force the script to install
## another combination of releases, uncomment
## the assignments below and specify them here:

# COMMONAPI_SOMEIP_COMMIT=HASH/TAG/BRANCH
# COMMONAPI_CORE_COMMIT=HASH/TAG/BRANCH
# VSOMEIP_COMMIT=HASH/TAG/BRANCH

# To specify a libboost version, uncomment the
# next four lines and assign the version to SPECIFIC_LIBBOOST_RELEASE

# SPECIFIC_LIBBOOST_RELEASE=1.66.0
# LIBBOOST_MIN=$SPECIFIC_LIBBOOST_RELEASE
# LIBBOOST_MAX=$SPECIFIC_LIBBOOST_RELEASE
# BOOST_RELEASE=https://boostorg.jfrog.io/artifactory/main/release/$SPECIFIC_LIBBOOST_RELEASE/source/boost_1_71_0.tar.gz

###############################################

# Erase next lines after implementing this file
echo "CUSTOM SOURCE IMPLEMENTED!"
exit 1
