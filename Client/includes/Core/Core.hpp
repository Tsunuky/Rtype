/*
** EPITECH PROJECT, 2020
** rtype_2020
** File description:
** DLLoader.hpp
*/

#ifndef _CORE_
#define _CORE_

#include "../Graph/LibSFML.hpp"
#include "../Games/IGame.hpp"
#include "Network.hpp"
#include "Packet.hpp"

class Core {
public:
    Core(const std::string host, const std::string port, LibContainer *a, Igame *b): _GraphContainer(a), _gameLibrary(b) {
        _NetworkClient = RType::Network::NetworkClient::createClient(host, port);
        handler = std::bind(&Core::fnc, this, std::placeholders::_1, std::placeholders::_2);
        _NetworkClient->init(handler);
        _gameLibrary->setNetworkClient(_NetworkClient);
    };
    virtual ~Core() {};
public:
    void launcher(int nbrPlayer);
    int computeGame(void);
    void run(void);
    int graphicalUpdate(void);
private:
    bool ExistGame(int value) {
        std::vector<std::vector<Entity>> Entitylist =_gameLibrary->getEntity();

        for (size_t i = 0; i < Entitylist.size(); i++) {
            for (size_t j = 0; j < Entitylist[i].size(); j++) {
                if (Entitylist[i][j]._id == value) {
                    return true;
                }
            }
        }
        return false;
    };
    void fnc(const std::vector<char> &arr, boost::asio::ip::udp::endpoint end) {
        _gameLibrary->receivePacket(arr, end);
    };
private:
    std::shared_ptr<LibContainer> _GraphContainer;
    std::unique_ptr<Igame> _gameLibrary;
    std::function<void(const std::vector<char> &, boost::asio::ip::udp::endpoint)> handler;
    std::shared_ptr<RType::Network::NetworkClient> _NetworkClient;
};

#endif