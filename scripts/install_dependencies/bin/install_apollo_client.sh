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


set -e

SCRIPT=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT")
SELF_ROOT_DIR=$(dirname "$SCRIPT_DIR")

# shellcheck source=scripts/install_dependencies/lib/nvm.sh
source "$SELF_ROOT_DIR/lib/nvm.sh"

export NVM_DIR="$HOME/.config/nvm"
# shellcheck disable=SC1091
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh"  # This loads nvm
# shellcheck disable=SC1091
[ -s "$NVM_DIR/bash_completion" ] && \. "$NVM_DIR/bash_completion"  # This loads nvm bash_completion

cd "$SELF_ROOT_DIR"
cd "$(git rev-parse --show-toplevel)/cpp-server/examples/apollo-client"

nvm install
nvm use
if [ ! -x "$(command -v yarn)" ]; then
    npm install -g yarn
fi
yarn install
yarn build

printf "%bSUCCESS! %b\n" "$BLUE" "$NC"
