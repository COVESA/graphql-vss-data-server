#!/bin/bash

# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
#   Author: Georgia Garcia (georgia@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.


mkdir -p "${KEYS_PATH}"
cd "${KEYS_PATH}" || exit

if [[ -e jwtRS256.key && -e jwtRS256.key.pub ]]; then
  exit
fi
echo "" | ssh-keygen -t rsa -b 4096 -m PEM -f jwtRS256.key -N ""
openssl rsa -in jwtRS256.key -pubout -outform PEM -out jwtRS256.key.pub
