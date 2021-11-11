# RType

## Requirements

This project is built using Conan and Cmake.

The libraries that we used are :
    
* The C++ standard library
* Boost
* SFML

You need to have them installed in order to compile. To do so, you must add the following remotes to Conan :

```sh
conan remote add tek https://api.bintray.com/conan/epitech/public-conan
conan remote add bincrafters https://bintray.com/bincrafters/public-conan
conan remote add conancenter https://bintray.com/conan/conan-center
```

## Building

```sh
./build.sh
```

## Server

### Structure

![alt text](https://github.com/EpitechIT2020/B-CPP-501-PAR-5-1-rtype-leonard.pooch/blob/master/.github/server.png)

### Usage

```sh
./build/bin/r-type_server <port>
```

## Client

### Structure

![alt text](https://github.com/EpitechIT2020/B-CPP-501-PAR-5-1-rtype-leonard.pooch/blob/master/.github/client.png)

### Usage

```sh
cd build
./bin/r-type_client <address> <port>
```

### External libraries

There is a possibility to launch a game using a specific graphic library and a specific game library.

To do so, you  have to add the adress of the library you want to use in a specific place of the ``conf.ini`` file, located in ``/build/conf.ini``.

Note : this file is only created when launching ``./build.sh``.

Here is the place where you should add your libraries :
```ini
[Core]
GAME="./lib/libr-type_game.so"
LIB="./lib/libr-type_sfml.so"
```
Replacing the path between double quotes in ``GAME`` will result in changing the game library.

Replacing the path between double quotes in ``LIB`` will result in changing the graphic library.

## Protocol

### Packet Structure

``[[id][length][data]]``

* ``id``
    * Identifies the destination of the packet
    * The ``id`` is interpreted in several distinct ways :
        * The ID ``0`` is the reserved id when you want to send a message to the server.
        * IDs between ``1`` and ``9`` are currently unused, sending packet with those ids will have no effect.
        * IDs between ``10`` and ``99`` are reserved for the general server actions.
        * IDs between ``100`` and ``999`` are used to identify the game that the packet should be routed to.
        * IDs from ``1000`` and after are not used.
* ``length``
    * Length of the data contained inside the packet
* ``data``
    * Informations contained inside the packet

### Exchanges

#### Requests from the client

* IDs between ``1`` and ``9`` are currently unused.
* ID ``10`` : Create a game
    * Request : ``[[10][0][<empty>]]``
    * Response :
        * Success : ``[[20][<length>][<game id>]]``
        * Failure : ``[[30][0][<empty>]]``
* ID ``11`` : Terminate a game
    * Request : ``[[11][<length>][<game id>]]``
    * Response :
        * Success : ``[[21][0][<empty>]]``
        * Failure : ``[[31][0][<empty>]]``
* ID ``12`` : Reset a game
    * Request : ``[[12][<length>][<game id>]]``
    * Response :
        * Success : ``[[22][0][<empty>]]``
        * Failure : ``[[32][0][<empty>]]``

#### Responses from the server

* Invalid game id :
    * ``[[90][0][<empty>]]``

#### Actions related to a specific game

* Make a player spawn
    * Request : ``[[<game id>][<length>][<10>/<player id>/<x>@<y>]]``

#### Actions related to a player

* Move
    * Request : ``[[<game id>][<length>][<100>/<player id>/<x>@<y>]]``
* Shoot
    * Request : ``[[<game id>][<length>][<101>/<player id>]]``

#### Data sent by the server without any request

* Spawn of an enemy :
    * ``[[<game id>][<length>][<200>/<enemy id>/<x>@<y>]]``
* Death of an enemy :
    * ``[[<game id>][<length>][<201>/<enemy id>]]``
* Move of an enemy :
    * ``[[<game id>][<length>][<202>/<enemy id>/<x>@<y>]]``
