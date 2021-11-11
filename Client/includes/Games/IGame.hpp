/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Games.hpp
*/

#ifndef _GAME_
#define _GAME_

#include <vector>

#include "System.hpp"
#include "Network.hpp"

class Igame {
public:
    virtual ~Igame() = default;
    virtual void getInput(std::vector<INPUT>) = 0;
    virtual std::vector<INPUT> setInput() = 0;
    virtual void Calcul(void) = 0;
    virtual Object_t getObjectByNumber(int a) = 0;
    virtual std::vector<std::vector<Entity>> getEntity(void) = 0;
    virtual void initGame(uint nbrPlayer) = 0;
    virtual void addEntity(ENTITY_TYPE type, std::string file, dot<float> pos) = 0;
    virtual void removeEntity(uint id) = 0;
    virtual void deleteGame() = 0;
    virtual void dump() = 0;
    virtual void setNetworkClient(std::shared_ptr<RType::Network::NetworkClient> &ptr) = 0;
    virtual void receivePacket(const std::vector<char> &arr, boost::asio::ip::udp::endpoint end) = 0;
};

#endif