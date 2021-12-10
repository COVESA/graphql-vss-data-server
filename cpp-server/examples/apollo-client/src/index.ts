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

import { ApolloClient } from 'apollo-client';
import { InMemoryCache, NormalizedCacheObject } from 'apollo-cache-inmemory';
import { ApolloLink } from 'apollo-link';
import { WebSocketLink } from 'apollo-link-ws';
import { SubscriptionClient } from 'subscriptions-transport-ws';
import { DocumentNode } from 'graphql';
import gql from 'graphql-tag';
import yargs from 'yargs';

import clipboardy from 'clipboardy';
import getIsOpen from './queries';
import setVehicleCabinDoorRow1Left from './mutations';
import operations from './operations';
import {
  TransportOptions,
  createSubscriptionClient,
  getHttpLink,
  generateToken,
} from './link';

const request = 'query';

const runClient = async (): Promise<void> => {
  const { argv } = yargs
    .usage('Available options:')
    .help('help')
    .alias('help', 'h')
    .option('request', {
      alias: 'r',
      description: 'Query, mutation or subscription',
      string: true,
      default: request,
      type: 'string',
    })
    .option('payload', {
      alias: 'p',
      description: 'Payload to be sent to the server',
      string: true,
      default: getIsOpen,
      type: 'string',
    })
    .option('transport', {
      alias: 't',
      description: 'Transport to send request: "http" or "ws" (WebSocket)',
      choices: [TransportOptions.http, TransportOptions.websocket],
      default: TransportOptions.websocket,
      type: 'string',
    })
    .option('get-token', {});

  try {
    if (argv['get-token']) {
      const token = generateToken();
      console.log(token);
      try {
        clipboardy.writeSync(token);
        console.log('\nToken copied to clipboard\n');
      } catch (e) {
        console.log('\nCould not copy to clipboard.\n');
      }
      return;
    }
    let link: ApolloLink | undefined;
    let subClient: SubscriptionClient | undefined;
    if (argv.transport === TransportOptions.websocket) {
      subClient = createSubscriptionClient();
      link = new WebSocketLink(subClient);
    } else if (argv.transport === TransportOptions.http) {
      link = getHttpLink();
    }
    const client: ApolloClient<NormalizedCacheObject> = new ApolloClient({
      link,
      cache: new InMemoryCache(),
    });

    if (!argv.request || !Object.keys(operations).includes(argv.request)) {
      console.error('Request selected is not valid');
      process.exit(1);
    }

    let payload: DocumentNode;
    if (argv.payload) {
      payload = gql`
        ${argv.payload}
      `;
    } else if (argv.request === 'mutation') {
      payload = setVehicleCabinDoorRow1Left;
    } else {
      payload = getIsOpen;
    }
    await operations[argv.request](client, payload, subClient);
    client.stop();
  } catch (e) {
    console.error('Exception: ', e);
    process.exit(1);
  }
};

runClient();
