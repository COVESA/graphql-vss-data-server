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

import fetch from 'cross-fetch';
import { ApolloLink } from 'apollo-link';
import { createHttpLink } from 'apollo-link-http';
import { SubscriptionClient } from 'subscriptions-transport-ws';
import WebSocket from 'ws';
import jwt from 'jsonwebtoken';
import fs from 'fs';

import permissions from './permissions';

export enum TransportOptions {
  http = 'http',
  websocket = 'ws',
}

export const generateToken = (): string =>
  jwt.sign(
    {
      uid: process.env.UID,
      permissions: process.env.PERMISSIONS
        ? JSON.parse(process.env.PERMISSIONS)
        : permissions,
    },
    process.env.PRIV_KEY_FILE ? fs.readFileSync(process.env.PRIV_KEY_FILE) : '',
    {
      algorithm: 'RS256',
    },
  );

export const createSubscriptionClient = (): SubscriptionClient => {
  if (!process.env.WEBSOCKET_URL) {
    console.error(
      'You have to specify the server websocket url in the WEBSOCKET_URL env variable',
    );
    process.exit(1);
  }
  const subclient = new SubscriptionClient(
    process.env.WEBSOCKET_URL,
    {
      connectionParams: {
        authorization: generateToken(),
      },
    },
    WebSocket,
  );

  subclient.onError((err: Error) => {
    console.error(`Error on connection: ${err.message}`);
  });

  return subclient;
};

export const getHttpLink = (): ApolloLink => {
  if (!process.env.HTTP_URL) {
    console.error(
      'You have to specify the server http url in the HTTP_URL env variable',
    );
    process.exit(1);
  }

  const httpLink = createHttpLink({ uri: process.env.HTTP_URL, fetch });
  const middlewareLink = new ApolloLink((operation, forward) => {
    operation.setContext({
      headers: {
        authorization: generateToken(),
      },
    });
    return forward(operation);
  });

  return middlewareLink.concat(httpLink);
};
