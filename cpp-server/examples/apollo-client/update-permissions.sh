#!/bin/bash

# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
#   Author: Gabriel Fernandes (g7fernandes@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.


GIT_BASE_DIR=$(git rev-parse --show-toplevel)
PERMISSIONS_TXT="$GIT_BASE_DIR/cpp-server/generated/permissions.yaml"
PERMISSIONS_FILE="$GIT_BASE_DIR/cpp-server/examples/apollo-client/src/permissions.ts"

if [ ! -f "$PERMISSIONS_TXT" ]; then
    echo "ERROR: permissions.txt file does not exist: $PERMISSIONS_TXT"
    exit 1;
fi

echo "const permissions: number[] = [" > "$PERMISSIONS_FILE"
sed 's;^\([^:]*\): *\([0-9]*\) *$;  \2 /* \1 */,;g' "$PERMISSIONS_TXT" >> "$PERMISSIONS_FILE"
cat << EOF >> "$PERMISSIONS_FILE"
];

export default permissions;
EOF
