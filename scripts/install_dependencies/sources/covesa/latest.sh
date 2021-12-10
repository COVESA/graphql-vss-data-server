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


########## Load helper functions and variables ##############
cd "$(dirname "$(realpath "$0")")"
GIT_ROOT=$(git rev-parse --show-toplevel)
cd -
# shellcheck source-path=scripts/install_dependencies/bin
source "$GIT_ROOT"/scripts/install_dependencies/bin/load_helpers_and_variables.sh
###############################################################

DEFAULT_BRANCH=master

printf "%b The latest releases of CommonAPI Core, -SomeIp and vSomeIp available will be installed. %b\n" "$BOLD" "$NC"
printf "%b If you want to use another release or specific commits, specify %b\n" "$BOLD" "$NC"
printf "%b them by editing the end of file 'scripts/custom-source/custom-source.sh'%b\n" "$BOLD" "$NC"
printf "%b under SPECIFY OTHER RELEASES %b\n\n" "$BOLD" "$NC"

echo "CommonAPI Core Runtime release"
get_remote_tag_hash github.com/COVESA/capicxx-core-runtime
export COMMONAPI_SOMEIP_COMMIT=$DEFAULT_BRANCH
echo "CommonAPI SomeIP release"
get_remote_tag_hash github.com/COVESA/capicxx-someip-runtime
export COMMONAPI_CORE_COMMIT=$DEFAULT_BRANCH
echo "vSomeIP release:"
get_remote_tag_hash github.com/COVESA/vsomeip
export VSOMEIP_COMMIT=$DEFAULT_BRANCH
