// Copyright (C) 2021, Bayerische Motoren Werke Aktiengesellschaft (BMW AG),
//   Author: Alexander Domin (Alexander.Domin@bmw.de)
// Copyright (C) 2021, ProFUSION Sistemas e Soluções LTDA,
//   Author: Gustavo Sverzut Barbieri (barbieri@profusion.mobi),
//   Author: Georgia Garcia (georgia@profusion.mobi),
//   Author: Pedro Soares (hspedro@profusion.mobi)
//
// SPDX-License-Identifier: MPL-2.0
//
// This Source Code Form is subject to the terms of the
// Mozilla Public License, v. 2.0. If a copy of the MPL was
// not distributed with this file, You can obtain one at
// http://mozilla.org/MPL/2.0/.

import fs from 'fs';
import { ApolloClient } from 'apollo-client';
import { NormalizedCacheObject } from 'apollo-cache-inmemory';
import { SubscriptionClient } from 'subscriptions-transport-ws';
import { DocumentNode } from 'graphql';
import { performance } from 'perf_hooks';

type MeasuredFunction<T> = (what: () => T | Promise<T>) => Promise<T>;

const createMeasure = <T>(measureFile: string): MeasuredFunction<T> => {
  const file = fs.createWriteStream(measureFile, { flags: 'a' });
  return async (what: () => T | Promise<T>, description = ''): Promise<T> => {
    const startTime = performance.now();
    const result = await what();
    const endTime = performance.now();
    file.write(`${(endTime - startTime).toString()} ${description}\n`);
    return result;
  };
};

const measure = !process.env.PERFORMANCE_FILE
  ? // eslint-disable-next-line @typescript-eslint/no-unused-vars
    <T>(what: () => T | Promise<T>, _description = ''): Promise<T> =>
      Promise.resolve(what())
  : createMeasure(process.env.PERFORMANCE_FILE);

export type Operation<T = NormalizedCacheObject> = (
  client: ApolloClient<T>,
  payload: DocumentNode,
  subClient: SubscriptionClient | undefined,
) => void;

export interface GraphqlOperations {
  query: Operation;
  mutation: Operation;
  subscription: Operation;
}

const operations: GraphqlOperations = {
  query: async (
    client: ApolloClient<NormalizedCacheObject>,
    payload: DocumentNode,
    subClient: SubscriptionClient | undefined,
  ) => {
    const result = await measure(
      () =>
        client.query({
          query: payload,
        }),
      'query.csv',
    );
    const resultstring = await measure(
      () => JSON.stringify(result, undefined, 2),
      'query-processing.csv',
    );
    if (!process.env.PERFORMANCE_FILE) {
      // eslint-disable-next-line no-console
      console.log(resultstring);
    }
    if (subClient) {
      subClient.close(true);
    }
  },
  mutation: async (
    client: ApolloClient<NormalizedCacheObject>,
    payload: DocumentNode,
    subClient: SubscriptionClient | undefined,
  ) => {
    const result = await measure(() => {
      const fileflag = '/tmp/apollo_opened_door';
      fs.stat(fileflag, (err, _stat) => {
        if (err == null) {
          client.mutate({
            mutation: payload,
            variables: { input: { isOpen: false } },
          });
          fs.unlinkSync(fileflag);
        } else if (err.code === 'ENOENT') {
          client.mutate({
            mutation: payload,
            variables: { input: { isOpen: true } },
          });
          fs.closeSync(fs.openSync(fileflag, 'w'));
        } else {
          console.log('Could not create open door file flag: ', err.code);
        }
      });
    }, 'mutation.csv');
    const resultstring = await measure(
      () => JSON.stringify(result, undefined, 2),
      'mutation-processing.csv',
    );
    if (!process.env.PERFORMANCE_FILE) {
      // eslint-disable-next-line no-console
      console.log(resultstring);
    }
    if (subClient) {
      subClient.close(true);
    }
  },
  subscription: (
    client: ApolloClient<NormalizedCacheObject>,
    payload: DocumentNode,
    subClient: SubscriptionClient | undefined,
  ) => {
    client
      .subscribe({
        query: payload,
      })
      .subscribe({
        // eslint-disable-next-line no-console
        next: data => console.log(JSON.stringify(data, undefined, 2)),
        // eslint-disable-next-line no-console
        error: error => {
          console.error(`Error on subscription ${error}`);
          if (subClient) {
            subClient.close(true);
          }
        },
        complete: () => {
          if (subClient) {
            subClient.close(true);
          }
        },
      });
  },
};

export default operations;
