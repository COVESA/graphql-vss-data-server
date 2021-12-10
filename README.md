# C++ GraphQL VSS Data Server

This GraphQL C++ Server project is an example of the implementation of [GraphQL VSS Server Libraries](https://github.com/COVESA/graphql-vss-server-libs). This server aims to deliver a GraphQL Server abstracting data from a vehicle to client applications. Albeit this example covers vehicle data, it should cover any service that uses SOME/IP as inter process communication.

This server and the *GraphQL VSS Server Libraries* gets vehicle data from SOME/IP using CommonAPI. Therefore, the server discharges the developers of client applications from the tedious tasks of implementing CommonAPI proxies and attributes for each data that it needs. Instead, the client applications can get vehicle data by sending a simple HTTP or WebSocket message with the [GraphQL Query](https://graphql.org/learn/queries/) to this server. This server also supports subscriptions and mutations.

Although this example fetches data from SOME/IP services, it is easy to expand it to get data from other sources.

The implementation on C++ will use
[cppgraphqlgen](https://github.com/microsoft/cppgraphqlgen) library to implement
GraphQL services, with the internal GraphQL pipeline. Also, we are going to use
[websocketpp](https://github.com/zaphoyd/websocketpp) library to deploy the
services via WebSocket, so that GraphQL clients make operations through the network.

Much of this code was generated with the help of [VSS to GraphQL Schema](https://github.com/COVESA/vss2graphql_schema) and [GraphQL Schema to C++ Code Generator](https://github.com/COVESA/graphql_schema2cpp_codegen).

## Install all dependencies automatically

To install all dependencies automatically, simply run the script at `scripts` folder. This script was tested in Ubuntu 20.04 and 18.04. Enter the terminal, and execute the **install_dependencies.sh**. The option `-h` shows help.

```bash
# cd into this repository
./scripts/install_dependencies/bin/install_dependencies.sh [OPTIONS]
```

Example and **recommended** way to install the dependencies:

```bash
# cd into this repository
./scripts/install_dependencies/bin/install_dependencies.sh --download-in-advance --download-dir $HOME/git/GQL_Dependencies --install-prefix $HOME/usr -r 3.2
```

The command above will install all dependencies compiled from source to your `$HOME/usr`. The repositories will be cloned to `$HOME/git/GQL_Dependencies`. It is recommended to install things that you compiled from source into some directory under your `/home` directory of your user, then testing or developing. This avoids conflicts with your system's libraries and you can uninstall everything by deleting the `/home/YOUR_USER/usr` directory later.

All CommonAPI and VSS related software is compiled from [COVESA's github](https://github.com/COVESA/) by default.

The installation script is extensible if you want to use different repositories other than COVESA's. For that, create a new directory under `scripts/install_dependencies/sources` with a name of your choice, and add a shell script with a name to specify the release. Then, specify the branches, tags and commits for the revision that you want to pick up. You can use the ones that we supply as an example, see `scripts/install_dependencies/sources/custom/custom.sh`.

The script clones the repositories of the dependencies and downloads their the source code by default to the folder `/home/YOUR_USER/git`. Use the option `--download-dir` to specify other directory.

If you don't want to install the dependencies to your system, pass an install location with `--install-prefix`.

The `--download-in-advance` flag will clone all dependencies at once before stating to build in order to save time.

For other options, run the script with

```bash
# cd this repository
./scripts/install_dependencies/bin/install_dependencies.sh -h
```

---
**Note:** If you ever installed CommonAPI to your system, I recommend to run the *install_dependencies.sh* script with the `--clean` option, **if** you get some compilation problem when building the GraphQL server or the Franca interfaces. The `--clean` will make the script ignore all current CommonAPI and SOME/IP installations on your system.

---

You will also have to build the Franca C++ interfaces for CommonAPI and SOME/IP. You will find the instruction at the _“Franca C++ Interfaces”_ subsection.

### The dependencies of this project

The [install_dependencies.sh](scripts/install_dependencies/bin/install_dependencies.sh) script installs all the dependencies for this project and for the *GraphQL VSS Server Libs*. This project requires:

* [GraphQL VSS Server Libs](https://github.com/COVESA/graphql-vss-server-libs);
* [CommonAPI-SomeIP Runtime](https://github.com/COVESA/capicxx-someip-runtime) 3.2.x;
* [VSomeIP](https://github.com/COVESA/vsomeip) [3.1.x, 3.2.x]
* [CommonAPI Core Runtime](https://github.com/COVESA/capicxx-core-runtime) 3.2.x
* [cppgraphqlgen](https://github.com/microsoft/cppgraphqlgen) 3.6.x;
* PEGTL 3.2.0 (is built automatically along with *cppgraphqlgen* if you do `git submodule update --init --recursive` at *cppgraphqlgen*'s repository);
* OpenSSL;
* Python 3;
* libpthread;
* Boost [1.66, 1.74] (The max version limit is a CommonAPI constrain);
* ninja (optionally).

To generate the C++ Franca interfaces on the *commonapi-wrappers* directory, you will need the [CommonAPI Core Tools](https://github.com/COVESA/capicxx-core-tools) and [CommonAPI SomeIP Tools](https://github.com/COVESA/capicxx-someip-tools). The provided script [gen_wrappers.sh](commonapi-wrappers/gen_wrappers.sh) downloads and generates the C++ Franca interfaces for you automatically. You may use the `gen_wrappers.sh` as shown below.

### Franca C++ Interfaces

The server needs the Franca C++ interfaces to be able to do SOME/IP calls with CommonAPI. The source code is provided in the _commonapi-wrappers_ directory.

The `CommonAPI wrappers` are generated by the [CommonAPI generator](https://github.com/COVESA/capicxx-core-tools) and [CommonAPI-SomeIP generator](https://github.com/COVESA/capicxx-someip-tools).

We provide already-generated headers and sources of the CommonAPI Franca C++ interfaces under the directory `commonapi-wrappers`. You must compile it.

The `PREFIX_PATH` must be set if some dependency is installed outside the default directories (`/usr` and `/usr/local`). If you used the installation script provided on GraphQL VSS Server repository, this will be the path that you specified in the `--install-prefix` option. If you specified, for example, `~/usr`:

```bash
PREFIX_PATH=$HOME/usr
cd commonapi-wrappers
CMAKE_PREFIX_PATH=$PREFIX_PATH ./gen_wrappers.sh
cd .. # go back to the root of this project
```

## Building

Prior to build the GraphQL Server, ensure that all the libraries previously generated are configured in system path, if you didn't used the install_dependencies script:

```bash
sudo ldconfig
```

### Automatic build

The script *build_release_server.sh* compiles a **release build** of the server and the Franca C++ interfaces automatically. Run it passing the `CMAKE_PREFIX_PATH` variable containing the path where you installed the dependencies. For example, if you chose `--install-prefix $HOME/usr` on the *install_dependencies.sh*, run:

```bash
CMAKE_PREFIX_PATH=$HOME/usr ./scripts/build_release_server.sh
```

### Manual build


To build the GraphQL Server, go to [cpp-server](cpp-server/) and build with
`cmake`:

```bash
cd cpp-server
mkdir build && cd build
```

Set `PREFIX_PATH` to the path where you installed the dependencies, ex:

```bash
PREFIX_PATH=$HOME/usr
```

If you didn't specify the `--install-prefix` on the install_dependencies.sh script, the prefix should be `/usr/local`.

To compile with clang (or other compiler), use the flag:

```bash
-DCMAKE_CXX_COMPILER=your_compiler
```

Note that the parameter `-DCMAKE_BUILD_TYPE` must match the built type that you used on the build of the [GraphQL VSS Server Libraries](https://github.com/COVESA/graphql-vss-server-libs). The `install_dependencies.sh` script, builds everything with `-DCMAKE_BUILD_TYPE=Release` by default.


If you want to update VehicleSchema.cpp and VehicleSchema.hpp specify the library path of cppgraphqlgen if you installed it somewhere other than `/usr/lib` before running CMake:

```bash
export LD_LIBRARY_PATH=$PREFIX_PATH/lib
```

And run CMake with the `UPDATE_STUBS` option set to `ON`:

```bash
-DUPDATE_STUBS=ON
```

If you don't want to verify the permissions on the request, set the `DISABLE_PERMISSIONS` to `ON`.

```bash
-DDISABLE_PERMISSIONS=ON
```

Below, the commands show how to compile with clang++.

#### Release build

```bash
cmake -G Ninja -DCMAKE_PREFIX_PATH="$PREFIX_PATH" \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER=$(which clang++) \
  -DCMAKE_STATIC_LINKER_FLAGS="" \
  -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib -L$PREFIX_PATH/lib" \
  -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib" \
  -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON ..
```

#### Debug build

```bash
cmake -G Ninja -DCMAKE_PREFIX_PATH="$PREFIX_PATH \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER=$(which clang++) \
  -DCMAKE_STATIC_LINKER_FLAGS="" \
  -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib -L/$PREFIX_PATH/lib" \
  -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld -L/usr/local/lib" \
  -DPKG_CONFIG_USE_CMAKE_PREFIX_PATH=ON  ..
```

Then start the build with

```bash
ninja
# or
cmake --build . -j $(nproc)
```

---
**NOTE** If CMake complains about not finding `jwt-cpp` **and you installed to the system**, specify with a flag
```
cmake -DCMAKE_PREFIX_PATH=/usr/local/cmake ..
```
or export the variable:
```
export CMAKE_PREFIX_PATH=/usr/local/cmake
```

**NOTE**: During the build process, a public key is going to be created in
order to be used for the JWT authentication. When the time comes, one can just
press enter and generate a key without a passphrase (only for development).

**NOTE**: The addition of `../commonapi-wrappers/playground` is to specify where the pre-compiled franca interface libraries are. If you compiled your own and installed somewhere else, specify where they are instead.

**NOTE**: The pre-compiled commonapi-wrappers were built and tested on Ubuntu 20.04 and 21.10.

---


## Running the SOME/IP Playground Service

This server requests a few attributes using CommonAPI SOME/IP. In a real car, the computer unit that monitors the sensors and operates the actuators will have CommonAPI services set up and available to receive requests.

We supply on the SOME/IP Playground Server repository that implements SOME/IP services to simulate the car, delivering mocked data.

The SOME/IP Playground Service and the instructions to run it can be found at [Test SOME/IP Service](https://github.com/COVESA/test-someip-service) repository.

## Running the GraphQL VSS Data Server

The targets will be available inside `build` folder. By default, the target will
build an executable for the `graphql_data_server` containing the GraphQL implementation.

First, export the `LD_LIBRARY_PATH` environment variable pointing to where you installed the libraries of the dependencies, if you didn't installed them on your systems default locations. For exemple, if you installed the dependencies under `$HOME/usr`

```
PREFIX_PATH="$HOME/usr"
export LD_LIBRARY_PATH="$PREFIX_PATH/lib"
VSOMEIP_CONFIGURATION=vsomeip.json VSOMEIP_APPLICATION_NAME=graphql ./build/graphql-data-server -R 1
```

The `export LD_LIBRARY_PATH="$PREFIX_PATH/lib"` is necessary for the system to find the libraries that the binary is using, if installed outside a “default” location like `/usr/lib`.

The `VSOMEIP_CONFIGURATION` and `VSOMEIP_APPLICATION_NAME` are used to set up the SOME/IP connections specifying the addresses.

The `-R 1` tells the server to reuse the same WebSocket address if it is closed and relaunched.

If you want to use DLT to monitor the logs of your server, start the DLT daemon.

```
dlt-daemon -d
```

To start the server, go back to the `cpp-server` directory and run

```bash
VSOMEIP_CONFIGURATION=vsomeip.json VSOMEIP_APPLICATION_NAME=graphql ./build/graphql-data-server
```

Then in another terminal where you want to receive the requests, run

```bash
dlt-control localhost -d 6 -l 6  # otherwise you will only receive info messages
dlt-receive -a localhost # start receiving the dlt messages
```

The application id of this GraphQL Server is `GDAS`. You can pipe an grep to filter the dlt messages of the server:

```bash
dlt-receive -a localhost | grep GDAS
```

-------
**Note:** If the DLT binaries are not found, the installation script probably installed to your `$PREFIX_PATH/bin`. If the binaries can be found there, export that location to your path.

```bash
# check if PREFIX_PATH is correct.
ls "$PREFIX_PATH/bin" # It shall show the dlt binaries
```

```bash
# add to your path
export PATH="$PATH:$PREFIX_PATH"
```

-------

### Apollo Client

We provide a typescript implementation of the Apollo Client can be used to make queries, mutations and subscriptions to the GraphQL Server.

The Apollo Client is supplied at `cpp-server/examples/apollo-client` under this repository. Use `nvm` to create an environment and install the dependencies.

If nvm is not installed, follow the instructions [at nvm's repository](https://github.com/nvm-sh/nvm).

You can install the Apollo Client automatically with the script `scripts/install_dependencies/bin/install_apollo_client.sh`, or following the steps on a subsection below.

#### Requesting data with the Apollo Client

Go to the apollo client directory and enter in the NVM environment.

```bash
cd cpp-server/examples/apollo-client
nvm use
```

To start the client it's necessary to provide all environment variables, this can
be done using a `.env` file. For a quick start just create a symbolic link to
`.env.example`

```bash
ln -s .env.example .env
```

To execute the binary, you can run:

```bash
yarn start
```

When no command line arguments are specified, by default the selected are:
* Request: `query`
* Payload:

```graphql
query IsDoorOpen {
  vehicle {
    cabin {
      door {
        row1 {
          left {
            isOpen
          }
        }
      }
    }
  }
}
```

To run a different payload, run the binary with the following command. Make sure to surround the payload with single quotes so the shell do not expand the characters.

```bash
yarn start --request query --payload 'query tankCapacityQuery { vehicle { powertrain { fuelSystem { tankCapacity } } } }'
```

If you want to perform a subscription, replace `query` by subscription. You can also do mutations. When doing subscriptions, you must pass a variable indicating the interval that you want to receive updates. This is important to not overload the network with data that is not important to have real time. See the *GraphQL Playground Client* section for more details.

For more details, you can run:

```bash
yarn start --help
```

#### Install the dependencies of Apollo Client

The Apollo Client script can be used to make queries, mutations and subscriptions to the GraphQL Server.

A Apollo client is supplied at `cpp-server/examples/apollo-client` under this repository. Use `nvm` to create an environment and install the dependencies.

If nvm is not installed, follow the instructions [at nvm's repository](https://github.com/nvm-sh/nvm).

Set the environment at `examples/apollo-client`:

```bash
# Go back one level to graphql-vss-data-server/cpp-server
cd ..
cd cpp-server/examples/apollo-client
nvm use
```

Install yarn globally:

```
npm install -g yarn
```

Install the dependencies:
```
yarn install
```

Build the client
```
yarn build
```


#### Running with HTTP Transport

One can also test sending Queries and Mutations via HTTP link, instead of the
default WebSocket. To do that, one must run the apollo client example with the
`-t` option, short for `--transport`:

```bash
yarn start -t http
```

---

**NOTE**: To check all the transport options available, run with `--help`.

---

### Requesting data with GraphQL Playground Client

To use the GraphQL Playground to play with your queries, download the Graphql Playground app at [electronjs](https://www.electronjs.org/apps/graphql-playground).

Copy the token with the permissions:


```bash
cd cpp-server/examples/apollo-client
nvm use
yarn get-token
```

Run the GraphQL playground.

```bash
/opt/GraphQL\ Playground/graphql-playground-electron
# Or open in the applications menu of your distro
```

The path to `graphql-playground-electron` above is the path when you install the deb package. If you don't want to install the .deb, an AppImage is also available.

Select *URL ENDPOINT* and use `http://localhost:4000`, and in the *HTTP HEADERS* tab, paste the token inside `Authorization`.

```json
{
  "authorization": "PASTE THE TOKEN HERE"
}
```

On the left side of the GraphQL Playground, you can write the query, mutation or subscription. For example:

```graphql
query IsDoorOpen {
  vehicle {
    cabin {
      door {
        row1 {
          left {
            isOpen
          }
        }
      }
    }
  }
}
```

![Query on the GraphQL Playground](resources/graphql_playground_screenshot.png "Query being performed on the GraphQL Playground.")
Query being performed on the GraphQL Playground.

To do a **mutation** or if your query requires arguments, write them under *Query Variables*

```json
{
  "input": { "isOpen": true }
}
```

And use the input on the mutation query:

```graphql
mutation OpenCloseDoor($input: Vehicle_Cabin_Door_Row1_Left_Input!) {
  setVehicleCabinDoorRow1Left(input: $input) {
    isOpen
  }
}
```

![Mutation on the GraphQL Playground](resources/graphql_playground_mutation_screenshot.png "Mutation being performed on the GraphQL Playground.")
Mutation being performed on the GraphQL Playground.

**Subscriptions** require a parameter that you can pass directly. The parameter indicates the interval that you want to get updates from the value. The available values are `DELIVERY_INTERVAL_1_SECOND`, `DELIVERY_INTERVAL_5_SECOND` and `REALTIME` (that always notifies the change immediately).

```graphql
subscription IsDoorOpen {
  vehicle(deliveryInterval: DELIVERY_INTERVAL_1_SECOND) {
  	powertrain {
      fuelSystem {
        level
      }
    }
  }
}
```

The data will scroll on the right side as it changes. Can test it by subscribing to the `isOpen` of some door in one tab, write the mutation in the other tab, and see the value changing on the subscription query when you do a mutation with it.

### Requesting data with cURL

You can send HTTP messages to the server using cURL. Since it is HTTP, you can do mutations and queries but not subscriptions.

#### Query

The query request must be in the body (`--data-binary`) of the of the HTTP and the authorization in a header.

```bash
curl 'http://SERVER_ADDRESS:PORT' -H 'Accept-Encoding: gzip, deflate, br' -H 'Content-Type: application/json' -H 'Accept: application/json' -H 'Connection: keep-alive' -H 'DNT: 1' -H 'Origin: file://' -H 'authorization: PASTE_THE_TOKEN_HERE' --data-binary '{"REQUEST_NAME":"PASTE THE QUERY HERE"}' --compressed
```

Example:

```graphql
query {
  vehicle {
    powertrain {
      transmission {
        driveType
      }
    }
  }
}
```

Becomes:

```bash
curl 'http://127.0.0.1:4000' -H 'Accept-Encoding: gzip, deflate, br' -H 'Content-Type: application/json' -H 'Accept: application/json' -H 'Connection: keep-alive' -H 'DNT: 1' -H 'Origin: file://' -H 'authorization: eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJwZXJtaXNzaW9ucyI6WzAsMSwxNSwzLDE2LDQsMTcsNSwxOCw2LDcsMjMsMTksMjQsMjAsMjUsMjEsMjYsMjIsMjcsMjgsMjksMzAsOCw5LDEwLDE0LDExLDEyLDEzLDIsMzFdLCJpYXQiOjE2Mzk1MjY5MDZ9.Hqop-8ZeYzOVqhIrG0ygDrkAEKo9jmmaVeI_kLlD5LlSgXcQex3LDhUHaf1Z-vY9XkIzx-CugARSV1AhS-rH1zUrpaES1kUfiezfTguBY3XG5f3y8KHYCT_DVxbflVjkJNQGu7YCdFUKLf9xvBKg0A_f1XW9PXMSiadhgmPiN0Z3CdYql0R3GKKae-cRuYyt9DWE0VPGRfY1jBv9BvmXk7NOucD-mBzBEW22-MRnvMwt9-3Tw1MMIZWYFcOW6Q-pn1OE9_CoWS2hB-RmC-Wv5mrAxNXtSW2vl5ZVoYt5Woy3gXRXz2l-ZoYrAx0EV30vbzRmXk23CalA6tp_A_h6JYV0iCVgcMu6bNM4avc0JB17As90Q5kyCLblbg1VpjOeslyEPAfROTACRyAdkL8wK-LqOUw3PNhEWA1Lzv0RJ2lAOII9YeREi51PxAhDRnBGZyaz1YVC9DmAxY5uh8Z6BDBZo_BhGso1kl_ZUbGh2o-J2Jk-a3O11SWU4kEHzItuz5KOWxFDn6yqFweTxd0RWLXr0c1tG7CGD_twMqPGXBH5dVrjLAmKocKLrR-g3bLQKSIXd1_5rdpz1onUbO8ScgraI_mwxPv7L1be2KbVD9P_Yrg4niXZSPKktCSBjudxQHAIW5sYIQHqqx5qMH9EuCEWg9C5orvhZq_rs6V_Oqo' --data-binary '{"query":"query {\n  vehicle {\n    powertrain {\n      transmission {\n        driveType\n      }\n    }\n  }\n}"}' --compressed
```

---
**Note**: Don't reuse this token. You must generate it yourself every time the public key changes, which happens when you do a clean build.  This is here just to show how the `curl` command will look like.

---

#### Mutations

Variables that you want to pass to the query must be also in the payload, after the query, preceded by a comma:

```json
"variables":{"input":{"isOpen":true}}
```

```bash
curl 'http://127.0.0.1:4000' -H 'Accept-Encoding: gzip, deflate, br' -H 'Content-Type: application/json' -H 'Accept: application/json' -H 'Connection: keep-alive' -H 'DNT: 1' -H 'Origin: file://' -H 'authorization: eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJwZXJtaXNzaW9ucyI6WzAsMSwxNSwzLDE2LDQsMTcsNSwxOCw2LDcsMjMsMTksMjQsMjAsMjUsMjEsMjYsMjIsMjcsMjgsMjksMzAsOCw5LDEwLDE0LDExLDEyLDEzLDIsMzFdLCJpYXQiOjE2Mzk1MjY5MDZ9.Hqop-8ZeYzOVqhIrG0ygDrkAEKo9jmmaVeI_kLlD5LlSgXcQex3LDhUHaf1Z-vY9XkIzx-CugARSV1AhS-rH1zUrpaES1kUfiezfTguBY3XG5f3y8KHYCT_DVxbflVjkJNQGu7YCdFUKLf9xvBKg0A_f1XW9PXMSiadhgmPiN0Z3CdYql0R3GKKae-cRuYyt9DWE0VPGRfY1jBv9BvmXk7NOucD-mBzBEW22-MRnvMwt9-3Tw1MMIZWYFcOW6Q-pn1OE9_CoWS2hB-RmC-Wv5mrAxNXtSW2vl5ZVoYt5Woy3gXRXz2l-ZoYrAx0EV30vbzRmXk23CalA6tp_A_h6JYV0iCVgcMu6bNM4avc0JB17As90Q5kyCLblbg1VpjOeslyEPAfROTACRyAdkL8wK-LqOUw3PNhEWA1Lzv0RJ2lAOII9YeREi51PxAhDRnBGZyaz1YVC9DmAxY5uh8Z6BDBZo_BhGso1kl_ZUbGh2o-J2Jk-a3O11SWU4kEHzItuz5KOWxFDn6yqFweTxd0RWLXr0c1tG7CGD_twMqPGXBH5dVrjLAmKocKLrR-g3bLQKSIXd1_5rdpz1onUbO8ScgraI_mwxPv7L1be2KbVD9P_Yrg4niXZSPKktCSBjudxQHAIW5sYIQHqqx5qMH9EuCEWg9C5orvhZq_rs6V_Oqo' --data-binary '{"query":"mutation OpenCloseDoor($input: Vehicle_Cabin_Door_Row1_Left_Input!) {\n  setVehicleCabinDoorRow1Left(input: $input) {\n    isOpen\n  }\n}\n","variables":{"input":{"isOpen":true}}}' --compressed
```

You can easily generate cURL commands with the “**Get CURL**” button of the GraphQL PlayGround Client.

## Valgrind

Valgrind is a memory error detector for Linux that helps to find memory leaks and uninitialized variables.

To install on Ubuntu 18.04 LTS or later:

```bash
sudo apt install valgrind
```

To run and check the server executable:

```bash
valgrind --leak-check=full --show-reachable=yes --error-limit=no ./build/graphql_data_server
```

## Schema and Code Generation

### Python Tools

The schema being used is located under [cpp-server](cpp-server/schema.graphql),
it is generated from the [vss2graphql](https://github.com/COVESA/vss2graphql_schema). The tooling reads the
[VSS](cpp-server/schema.graphql) data structure from the Vehicle, filters against the deployed data and then builds the GraphQL Schema representing it.

The files [Vehicle.cpp](cpp-server/generated/Vehicle.cpp),
[Vehicle.hpp](cpp-server/generated/Vehicle.hpp) and
[permissions_symbols.hpp](cpp-server/generated/permissions_symbols.hpp)
are also generated using the [GraphQL Schema to C++ Code Generator](https://github.com/COVESA/graphql_schema2cpp_codegen).

#### VSS2GraphQL Schema and CodeGen setup

Make sure you have python version 3.8.5 and pipenv installed.

```sh
cd cpp-server
pyenv install 3.8.5
pyenv local 3.8.5
python3.8 -m pip install --user pipenv
```

And then you can install the tools on your environment inside the [cpp-server](cpp-server) folder:
```shell
export PIPENV_VENV_IN_PROJECT=1
python3.8 -m pipenv sync
```

Or to install with dev dependencies:
```shell

python3.8 -m pipenv sync -d
```

#### Using the schema and code generators

To generate the files separately using this tool you need to run:
```bash
pipenv run gen_vss_gql_schema
pipenv run gen_vss_gql_code
```
And the files will be generated under the [cpp-server/resources](cpp-server/resources) folder.

The VSS files from COVESA are cloned from the [Vehicle Signal Specification](https://github.com/COVESA/vehicle_signal_specification) to the `resources/spec` directory if you run `git submodule update --init --recursive` in this repository.

---

**NOTE**: Be aware that this will get and overwrite permissions from
[resources/permissions.yaml](resources/permissions.yaml), and if there is none when you run,
the permissions will be created from scratch and it will not match the permissions on the server.

---

You can also run these tools and automatically replace the files where they are using the following commands:
```bash
pipenv run update_vss_gql_schema
pipenv run update_vss_gql_code
```

## Overview of the GraphQL VSS Data Server implementation

This server is an example of the implementation of [GraphQL VSS Server Libs](https://github.com/COVESA/graphql-vss-server-libs). The **GraphQL VSS Server Libs** provides two libraries, _protocol_ and _support_, that handle the server's connections, both to the client (HTTP/WebSocket) and to the SOME/IP service. Checkout **GraphQL VSS Server Libs** repository for more information.

The code on this repository shows how to:

* Use the generated code;
* Declare SOME/IP proxies and CommonAPI attributes;
* Use the _implementation library_ for writing functions that will process the data obtained from CommonAPI;
* Register the DLT loggers.

### The code generated by _cppgraphqlgen_


 The GraphQL schema contains the information about all the data available, the operations, and the shape of the [graph](https://en.wikipedia.org/wiki/Graph_(abstract_data_type)) that organized the data. More information about GraphQL schema is available [at the apollo server documentation](https://www.apollographql.com/docs/apollo-server/schema/schema/).

The _schemagen_ of Microsoft's project _cppgraphqlgen_ is a program that generates the [VehicleSchema.h](cpp-server/generated/introspection/VehicleSchema.h) [VehicleSchema.cpp](cpp-server/generated/introspection/VehicleSchema.cpp) files using the [provided GraphQL schema file](cpp-server/schema.graphql). These files contain the implementation of classes, one for each node of the graph. The member functions (of the classes of the nodes) that retrieve the data are the so-called _resolver functions_.

The _resolver functions_ generated by the _schemagen_ have to be overridden by other _resolver function_ that will deliver the real data. If one doesn't override them, they will throw an error warning that the implementation is missing.

Note that we have two directories, one called _introspection_ and the other called *no_introspection*. The difference between them is that the first one allows introspection queries. When building for production, it is recommended to use the _no_introspection_ C++ schemas, for performance and [security reasons](https://www.apollographql.com/blog/graphql/security/why-you-should-disable-graphql-introspection-in-production/).

### The Resolver Functions

A code generator (to be open-sourced...) generates the files [Vehicle.hpp](cpp-server/generated/Vehicle.hpp) and [Vehicle.hpp](cpp-server/generated/Vehicle.hpp). The generated header file declares the inherited classes from `VehicleSchema.h` and the source file [Vehicle.cpp](cpp-server/generated/Vehicle.cpp) implements the resolver functions.

The resolver functions are generated based on the information obtained from the GraphQL schema (types, enumerations, parameters and shape of the graph), and from the _layer files_, that contain the information about the source of the data and what could be done with it (mutate, subscribe and read).

All resolver functions can receive parameters; this is usually the case for mutations. Resolver functions that return branch objects typically just return a shared pointer to the next node in the graph, but there are exceptions. The executable schema resolves the resolver functions until a “leaf node” returns the data.

### “Leaf” resolver function

The resolver of a “leaf” node is normally composed by:

* A function that retrieves a `GraphQLRequestState` instance;
* The validation of the permission for that node against the permissions stored in the `GraphQLRequestState` object;
* A request for a singleton object;

A `getValue` member function of the singleton that returns the desired data. A few examples are given below.

#### Leaf node that performs a CommonAPI call

The `GraphQLRequestState::fromRequestState` function returns the _request state_. The validation is done by the `validate` function. The parameter of the validate function is a `uint_16` number that corresponds to a permission. These permission symbols are declared in the generated file [permissions_symbols.hpp](cpp-server/generated/permissions_symbols.hpp).

```c++
service::FieldResult<std::optional<response::Value>>
Vehicle_Powertrain_FuelSystem::getLevel(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_FuelSystem_Level_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__CurrentTankVolumeEvent>()->getValue<response::Value>(
        implementation::Vehicle_Powertrain_FuelSystem::fromCurrentTankVolumeToLevel
    );
}
```

The template parameter of the `GraphQLRequestState::getSingleton` function is what indicates which singleton we are using. The name `v1_org_COVESA_vehicle_playground_PlaygroundProxy_1__CurrentTankVolumeEvent` is declared in the implementation library using macros. In this case, it is in the [CurrentTankVolumeEvent.hpp](cpp-server/implementation/attributes/v1_org_COVESA_vehicle_playground_PlaygroundProxy_1/CurrentTankVolumeEvent.hpp). Note that the template parameter used is composed by two parts separated by double underscores: the name of the proxy and the name of the attribute that is returned through that proxy.

```cpp
TYPEDEF_COMMONAPI_EVENT_SUBSCRIPTION_PROXY_ATTRIBUTE(
    implementation::Vehicle_Powertrain_FuelSystem::CurrentTankVolumeEvent,
    v1_org_genivi_vehicle_playground_PlaygroundProxy_1,
    CurrentTankVolumeEvent
);
```

The template parameter of `getValue` is the type of the response. In this case, the function returns a `response::Value` type because it uses a [custom scalar](https://www.apollographql.com/docs/apollo-server/schema/custom-scalars/) since its type (`uint8`) is not a default scalar type. In the case of the resolver function for `tankCapacity`, the return type is a double; since its type in the schema is `float` that is a default type. This server uses `double` for `float` types in the schema.

```cpp
service::FieldResult<std::optional<double>>
Vehicle_Powertrain_FuelSystem::getTankCapacity(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_FuelSystem_TankCapacity_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__CapacityAttribute>()->getValue<double>(
        implementation::Vehicle_Powertrain_FuelSystem::fromTankCapacityToCapacity
    );
}
```

The parameter of the `getValue` functions is a function that converts the data returned by the CommonAPI call to that is expected by the client. These “conversion functions” are implemented in the _implementation_ library.

If the value returned by CommonAPI call is exactly what the client expects, no “conversion function” is required and the `getValue` is called with no parameters.

##### Leaf node with dispatcher

Sometimes the source or “conversion function” of the value of a node depends on some other value. This is the case, for example, of the `getCurrentGear` resolver function.

```cpp
service::FieldResult<std::optional<response::Value>>
Vehicle_Powertrain_Transmission::getCurrentGear(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_Transmission_CurrentGear_READ);
    switch (implementation::Vehicle_Powertrain_Transmission::selectCurrentGearFromIsReverseGearOnCurrentGear(state)) {
        case 0:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__CurrentGearAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Powertrain_Transmission::fromCurrentGearToCurrentGear
            );
        case 1:
            return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__IsReverseGearOnAttribute>()->getValue<response::Value>(
                implementation::Vehicle_Powertrain_Transmission::fromIsReverseGearOnToCurrentGear
            );
        default:
            throw std::invalid_argument("Unsupported deploy type.");
    }
}
```

The snippet above shows the mentioned case. There is a switch-case to call the correct singleton depending on the value returned by `selectCurrentGearFromIsReverseGearOnCurrentGear`. The implementation of the selector function has a CommonAPI call to check the value of `isReverseGearOn`:

```cpp
int selectCurrentGearFromIsReverseGearOnCurrentGear(std::shared_ptr<GraphQLRequestState> state)
{
	const bool isReverseGearOn =
		state
			->getSingleton<
				v1_org_genivi_vehicle_playground_PlaygroundProxy_1__IsReverseGearOnAttribute>()
			->getValue<bool>();

	if (isReverseGearOn)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
```

#### Branch resolver functions

All nodes have resolver functions. The ones that returns instances of other nodes are called _branch resolvers_.

```cpp
service::FieldResult<std::shared_ptr<object::Vehicle_Powertrain_FuelSystem>>
Vehicle_Powertrain::getFuelSystem(service::FieldParams&& params) const
{
    return std::make_shared<Vehicle_Powertrain_FuelSystem>();
}
```

##### List branch resolvers

GraphQL support [list fields](https://www.apollographql.com/docs/apollo-server/schema/schema/#list-fields), which are nodes that retuns multiple values of the same type. The items of these lists contains _modifier_ objects, that are objects that have some attribute or function to differentiate each item of the list.

The return type of list branch resolver is a `std::vector` of `std::shared_ptr` of the object with the type of the node. The _modifier_ must be manually implemented in the implementation library.

```cpp
// on Vehicle.cpp
service::FieldResult<std::optional<std::vector<std::shared_ptr<object::Vehicle_Chassis_Axle>>>>
Vehicle_SomeBranch::getSomeListNode(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    return implementation::Vehicle_Chassis::getSomeListNode<TypeOf_SomeListNode, object::TypeOf_SomeListNode>(state);
}
```

```cpp
// On Vehicle.hpp
class Vehicle_SomeBranch_SomeListNode : public object::Vehicle_SomeBranch_SomeListNode
{
    const std::shared_ptr<implementation::Vehicle_SomeBranch_SomeListNode::Modifiers> m_Modifiers;

public:
    explicit Vehicle_SomeBranch_SomeListNode(std::shared_ptr<implementation::Vehicle_SomeBranch_SomeListNode::Modifiers> modifiers)
        : m_Modifiers(modifiers)
    {
    }
    ...
```

The `m_Modifiers` that hold the _modifier_ instance must have all the `get<NameOfTheNode>` member functions used to obtain the value to be returned by the resolver functions of the nodes children of list nodes.

For example, if the list node `SomeListNode` contains another list field, named `SomeOtherListNode`, the resolver function will be like the one shown below.


```cpp
service::FieldResult<std::optional<std::vector<std::shared_ptr<object::Vehicle_Chassis_Axle_Wheel>>>>
Vehicle_SomeBranch_SomeListNode::getSomeOtherListNode(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    return m_Modifiers->getSomeOtherListNode<TypeOf_SomeOtherListNode, object::TypeOf_SomeOtherListNode>();
}
```

##### Leaf nodes resolved at its branch parent

Another case that worth mentioning is when the value of a “leaf node” is determined at a branch node. When this happens, the type specified at the template of the `getValue` of the singleton is the GraphQL C++ type of the branch. For example:

```cpp
// at Vehicle.cpp
service::FieldResult<std::shared_ptr<object::Vehicle_Branch_BranchWithAllData>>
Vehicle_Branch::getBranchWithAllData(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    return state->getSingleton<v1_someProxy_1__SomeAttributeAttribute>()->getValue<std::shared_ptr<object::Vehicle_Branch_BranchWithAllData>>(
        implementation::Vehicle_Branch::fromSomeAttributeToBranchWithAllData<Vehicle_Branch_BranchWithAllData, object::Vehicle_Branch_BranchWithAllData>
    );
}

service::FieldResult<std::optional<std::string>>
Vehicle_Branch_BranchWithAllData::getSomeLeaf(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Branch_BranchWithAllData_SomeLeaf_READ);
    return m_SomeLeaf;
}

```

The implemented function `fromSomeAttributeToBranchWithAllData` creates a shared pointer of `Vehicle_Branch_BranchWithAllData`.


```cpp
// At Vehicle.hpp
class Vehicle_Branch_BranchWithAllData : public object::Vehicle_Branch_BranchWithAllData
{
    const std::optional<std::string> m_SomeLeaf;

public:
    explicit Vehicle_Branch_BranchWithAllData(std::optional<std::string>&& colorHSV, std::optional<std::string>&& name)
        : m_SomeLeaf(std::move(colorHSV))
    {
    }

    service::FieldResult<std::optional<std::string>>
    getSomeLeaf(service::FieldParams&& params) const final;
};
```

### The Implementation library

The implementation library contains all the code that was not or could not be generated. The **proxies** and **attributes** directories contain the declaration of the `proxy` and `attribute` singletons. The files in these repositories, although not yet generated, could be generated from using the _layer_ files without much difficulty.

In addition to **proxies** and **attributes**, some other directories might be expected by the `Vehicle.cpp` file:

* **constants**: Contains files containing values of nodes that are predefined or constants;
* **dispatcher**: Contains functions that return the selector value of the `swich` statement for the resolver functions that require them;
* **franca_idl**: Functions that manipulates the value returned by CommonAPI to get the value expected by the client;
* **list**: The classes or structures of modifiers and functions that return `std::vectors` of shared pointers of list fields.

The functions implemented on **franca_idl** may be, for example, functions like convert speed value from `km/h` to `mph`, if `mph` is the unit described on the VSS of the `speed` field and CommonAPI returns a value `km/h`.

To keep the files organized, **the directory structure of the directories listed above should mimic the schema's tree**. A function or object used to resolve a node, must be inside a directory with the name of its parent, in a file with its name. For example, the “conversion” function of the `getDriverType` resolver, which belongs to the class of the branch `Vehicle_Powertrain_Transmission`, must be defined at `cpp-server/implementation/franca_idl/vehicle/powertrain/transmission.hpp`.

The namespace where the function or object belongs, must be the name of the branch node that it belongs inside the `implementation::` namespace. For example, in the case of `fromDrivePowerTransmissionToDriveType`:

```cpp
service::FieldResult<std::optional<std::string>>
Vehicle_Powertrain_Transmission::getDriveType(service::FieldParams&& params) const
{
    auto state = GraphQLRequestState::fromRequestState(params.state);
    state->validate(permissions::Vehicle_Powertrain_Transmission_DriveType_READ);
    return state->getSingleton<v1_org_genivi_vehicle_playground_PlaygroundProxy_1__DrivePowerTransmissionAttribute>()->getValue<std::string>(
        implementation::Vehicle_Powertrain_Transmission::fromDrivePowerTransmissionToDriveType
    );
}
```

The developer that is writing resolver functions shall pay attention to the header that the generator included in the beginning of the _Vehicle.cpp_ file. All them must be created and they might need to contain some extra implementation.

The _modifier_ headers are also included in the beginning of the _Vehicle.hpp_ file.

#### Proxies and Attributes

Should be declared always with the provided macros on [GraphQL VSS Server Libs](https://github.com/COVESA/graphql-vss-server-libs) package at the _commonapi-singletons.hpp_ file.

##### Proxy declaration

```cpp
TYPEDEF_COMMONAPI_PROXY(_proxy, _instanceId, _name)
```

##### Broadcasted CommonAPI Attribute

```cpp
TYPEDEF_COMMONAPI_EVENT_SUBSCRIPTION_PROXY_ATTRIBUTE(_event, _proxy, _name)
```

The `_event` must be an object that will process the tuples returned by the CommonAPI Event. See [CurrentTankVolumeEvent.hpp](cpp-server/implementation/attributes/v1_org_genivi_vehicle_playground_PlaygroundProxy_1/CurrentTankVolumeEvent.hpp) for example.

##### Attributes that create lists via subscription

There could be cases where a `list` field must be created using the values obtained from a subscription. Attributes that return values in a sequence withe the values of one single event must be declared as:

```cpp
TYPEDEF_COMMONAPI_ACCUMULATIVE_UNIQUE_EVENT_SUBSCRIPTION_PROXY_ATTRIBUTE(_event,           \
    _proxy,                                                                                        \
    _name)                                                                                         \
```

##### Subscribe-only attribute

This is the case when an attribute can be just subscribed to. When doing simple queries to these attributes, it will wait for the first value to arrive and than return it.


```cpp
TYPEDEF_COMMONAPI_SUBSCRIPTION_ONLY_PROXY_ATTRIBUTE(_proxy, _name)
```

##### Attributes that we can subscribe and fetch a single value

This is the common case of an attribute that we can subscribe or use the `getValue` method to obtain the desired data.

```cpp
TYPEDEF_COMMONAPI_SUBSCRIPTION_PROXY_ATTRIBUTE(_proxy, _name)
```


##### Attributes that does not support subscription

```cpp
TYPEDEF_COMMONAPI_ALWAYS_GET_VALUE_PROXY_ATTRIBUTE(_proxy, _name)
```

## The Source File

The main file [server.cpp](cpp-server/src/server.cpp) creates the instance of the `GraphQLServer` object, sets it, passes the authorizer to it and register the DLT loggers. Do get the DLT messages that were used on the code of GraphQL VSS Server Libs, you must register the application and context in your main file:

```cpp
    // src/server.cpp
    DLT_REGISTER_APP("GDAS", "GraphQL Data Abstraction Server");
    DLT_REGISTER_CONTEXT(dltServer, "SERV", "GraphQL Server");
    DLT_REGISTER_CONTEXT(dltConnection, "CONN", "GraphQL Connection");
    DLT_REGISTER_CONTEXT(dltOperation, "OP", "GraphQL Connection Operation");
    DLT_REGISTER_CONTEXT(dltWebSocket, "WS", "WebSocket Transport");
    DLT_REGISTER_CONTEXT(dltCommonAPI, "CAPI", "CommonAPI Calls");
```

Before returning the `main` function, the DLT contexts and app must be unregisted, otherwise you might get memory leak warnings when running with some sanitizer:

```cpp
    DLT_UNREGISTER_CONTEXT(dltServer);
    DLT_UNREGISTER_CONTEXT(dltConnection);
    DLT_UNREGISTER_CONTEXT(dltOperation);
    DLT_UNREGISTER_CONTEXT(dltWebSocket);
    DLT_UNREGISTER_CONTEXT(dltCommonAPI);
    DLT_UNREGISTER_APP();
```

## Contributing

To avoid the commitment of problematic code, we provide git-hooks that should be installed prior any commiting. In order to install them, run:

```bash
./scripts/git/install_git_hooks.sh
```

You must have the [shellcheck](https://www.shellcheck.net/) installed, clang and [clang-tidy](https://clang.llvm.org/extra/clang-tidy/) installed. They are all available on Ubuntu repositories. The latest shellcheck is available as a snap package also.

## References

[CommonAPI User Guide](https://usermanual.wiki/Document/CommonAPICppUserGuide.1126244679/html)

[CommonAPI C++ Tutorial](https://at.projects.genivi.org/wiki/pages/viewpage.action?pageId=5472311)

[VSomeIP User Guide](https://github.com/COVESA/vsomeip/blob/master/documentation/vsomeipUserGuide)

[CppGraphQLGen Documentation](https://github.com/microsoft/cppgraphqlgen/tree/main/doc)

[Introduction to GraphQL](https://graphql.org/learn/)
