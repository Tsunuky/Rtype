/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#include <tuple>
#include <csignal>
#include <iostream>
#include <algorithm>
#include "Packet.hpp"
#include "Server.hpp"

RType::Server::Server::Server(const std::uint16_t port) :
    _port(port), _server(RType::Network::UDPEndpoint::createEndpoint(port)),
    _status(RType::Server::Server::__status__::Running) {}

RType::Server::Game &RType::Server::Server::addGame(const std::string &name)
{
    _games.push_back(std::make_unique<RType::Server::Game>(nextID, name));
    nextID += 1;
    return **_games.rbegin();
}

void RType::Server::Server::removeGame(int gameId)
{
    auto game = std::find_if(_games.begin(), _games.end(), [&](auto &g) {
        return g->getID() == gameId;
    });

    if (game != _games.end()) {
        (*game)->stop();
        _games.erase(game);
    }
}

bool RType::Server::Server::gameExists(int gameId)
{
    auto pos = std::find_if(_games.begin(), _games.end(), [&](auto &g) {
        return g->getID() == gameId;
    });
    return pos != _games.end();
}

void RType::Server::Server::handleServerPacket(const RType::Network::ServerPacket &inp,
boost::asio::ip::udp::endpoint end)
{
    std::string str(inp._data.begin(), inp._data.end());
    std::cout << "server data (" << str << ")" << std::endl;
    //handle server packet
}

void RType::Server::Server::handleActionPacket(const RType::Network::ServerPacket &inp,
boost::asio::ip::udp::endpoint end)
{
    int gameID = inp._id;

    if (gameID == 10) {
        RType::Network::ServerPacket packet;
        auto newGameID = this->nextID;
        std::string response = std::to_string(newGameID);
        auto &game = this->addGame("");
        game.setEndpoint(end);
        std::cout << "game id (" << newGameID << ") : game creation" << std::endl;

        packet._id = 20;
        packet._data = std::vector(response.begin(), response.end());
        _server.get()->send(end, packet.serialize());
    }
    else if (gameID == 11) {
        RType::Network::ServerPacket packet;
        std::string inpstr(inp._data.begin(), inp._data.end());

        auto inpnbr = std::stoi(inpstr);
        auto game = std::find_if(_games.begin(), _games.end(), [&](auto &g){
            return g->getID() == inpnbr;
        });

        if (game != _games.end())
            this->removeGame(inpnbr);

        packet._id = 21;
        packet._data = std::vector<char>();
        _server.get()->send(end, packet.serialize());

        std::cout << "game id (" << inpnbr << ") : game destruction" << std::endl;
    }
    /*
    else if (gameID == 12) {
        auto game = std::find_if(_games.begin(), _games.end(), [&](auto &g){
            return g->getID() == gameID;
        });

        if (game != _games.end())
            (*game)->reset();
    }*/
}

void RType::Server::Server::handleGamePacket(const RType::Network::ServerPacket &inp,
boost::asio::ip::udp::endpoint end)
{
    int gameID = inp._id;

    auto game = std::find_if(_games.begin(), _games.end(), [&](auto &g){
        return g->getID() == gameID;
    });

    if (game != _games.end()) {
        std::cout << "game id (" << gameID << ") : game exists" << std::endl;
        (*game)->getInput().push(std::make_tuple(end, inp._data));
    }
    else {
        RType::Network::ServerPacket packet;
        std::string response;

        packet._id = 90;
        packet._data = std::vector(response.begin(), response.end());

        std::cout << "game id (" << gameID << ") : game does not exist" << std::endl;
        _server.get()->send(end, packet.serialize());
    }
}

void RType::Server::Server::dispatch(const RType::Network::ServerPacket &inp,
boost::asio::ip::udp::endpoint end)
{
    int gameID = inp._id;

    if (gameID == 0)
        this->handleServerPacket(inp, end);
    else if (gameID >= 10 && gameID <= 99)
        this->handleActionPacket(inp, end);
    else if (gameID >= 100 && gameID <= 999)
        this->handleGamePacket(inp, end);
    else {
        RType::Network::ServerPacket packet;
        std::string response;

        packet._id = 90;
        packet._data = std::vector(response.begin(), response.end());

        std::cout << "game id (" << gameID << ") : invalid id" << std::endl;
        _server.get()->send(end, packet.serialize());
    }
}

void RType::Server::Server::processInput(const std::vector<char> &arr,
boost::asio::ip::udp::endpoint end)
{
    RType::Network::ServerPacket inp;
    std::vector<char> vinp(std::begin(arr), std::end(arr));

    if (!inp.deserialize(vinp))
        return ;
    this->dispatch(inp, end);
}

void RType::Server::Server::processOutput(std::int32_t id, const std::string &str)
{
    RType::Network::ServerPacket out;
    out._id = id;
    out._data = std::vector(str.cbegin(), str.cend());
    std::vector<char> vout = out.serialize();
}

int RType::Server::Server::stop(void)
{
    std::for_each(_games.begin(), _games.end(), [&](auto &g){ g->stop(); });
    return 0;
}

void RType::Server::Server::checkReturnFromGames(void)
{
    for (auto &game : _games) {
        auto &output = game.get()->getOutput();
        if (!output.isEmpty()) {
            std::tuple<boost::asio::ip::udp::endpoint, std::vector<char>> element;
            RType::Network::ServerPacket packet;
            output.pop(element);

            auto gameId = game.get()->getID();
            auto endpoint = std::get<0>(element);
            auto data = std::get<1>(element);

            packet._id = gameId;
            packet._data = data;
            _server.get()->send(endpoint, packet.serialize());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int RType::Server::Server::start(void)
{
    std::signal(SIGINT, [](const int) { std::exit(0); });

    _server->init([this](auto data, auto endpoint){ this->processInput(data, endpoint); });
    while (_status == RType::Server::Server::__status__::Running) {
        this->checkReturnFromGames();
        _server->getContext().run_for(std::chrono::milliseconds(10));
    }
    return this->stop();
}