#!/bin/bash

# Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
#   Author: Alexander Domin (Alexander.Domin@bmw.de)
# Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
#   Author: Pedro Soares (hspedro@profusion.mobi)
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the
# Mozilla Public License, v. 2.0. If a copy of the MPL was
# not distributed with this file, You can obtain one at
# http://mozilla.org/MPL/2.0/.

STATISTICS='query.csv query-processing.csv mutation.csv mutation-processing.csv'
PERFORMANCE_FILE=${1:-"measurements"}

echo "Reading statistis from ${PERFORMANCE_FILE}"
for stat in ${STATISTICS}
do
  echo "Grouping statistis for ${stat}"
  awk -v pattern="${stat}" '$0 ~ pattern {if(length($1) > 0){print $1 > pattern}}' $PERFORMANCE_FILE
done
