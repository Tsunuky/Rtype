/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <array>
#include <boost/asio.hpp>
#include "Queue.hpp"
#include "Packet.hpp"
#include "Game.hpp"
#include "Network.hpp"

namespace RType {
    namespace Server {
        class Server {
            public :
                enum class __status__ {
                    Running = 1,
                    Stopped = 2
                };
                Server(std::uint16_t);
                ~Server(void) = default;

                RType::Server::Game &addGame(const std::string &name);
                void removeGame(int);
                bool gameExists(int);

                void handleServerPacket(const RType::Network::ServerPacket &,
                    boost::asio::ip::udp::endpoint);
                void handleActionPacket(const RType::Network::ServerPacket &,
                    boost::asio::ip::udp::endpoint);
                void handleGamePacket(const RType::Network::ServerPacket &,
                    boost::asio::ip::udp::endpoint);
                void dispatch(const RType::Network::ServerPacket &,
                    boost::asio::ip::udp::endpoint);

                void processInput(const std::vector<char> &,
                    boost::asio::ip::udp::endpoint);
                void processOutput(std::int32_t, const std::string &);

                void checkReturnFromGames(void);

                int stop(void);
                int start(void);
            private :
                int nextID = 100;
                const std::uint16_t _port;
                std::unique_ptr<RType::Network::UDPEndpoint> _server;
                RType::Server::Server::__status__ _status;
                std::vector<std::unique_ptr<RType::Server::Game>> _games;
        };
    }
}

#endif