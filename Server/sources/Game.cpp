/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/


#include <iostream>
#include <tuple>
#include <random>
#include <algorithm>
#include "Game.hpp"

void RType::Server::Game::shoot(const std::string &playerId)
{
    std::cerr << "Shoot with player " << playerId << std::endl;
    auto player = std::find_if(_players.begin(), _players.end(), [&](auto &p) {
        std::cerr << "Find player" << p.getId() << std::endl;

        return p.getId() == playerId;
    });
    if (player == _players.end()) {
        std::cerr << "Cannot find player" << std::endl;
        return ;
    }

    auto dead = player->shoot(_enemies);
    for (auto deadID : dead) {
        auto it = std::find_if(_enemies.begin(), _enemies.end(), [&](auto &e) {
            return e.getId().compare(deadID) == 0;
        });
        if (it != _enemies.end()) {
            std::string res = "201/";
            auto id = it->getId();
            _enemies.erase(it);
            res.append(id);
            std::vector<char> v(res.begin(), res.end());
            _output.push(std::make_tuple(_endpoint, v));
        }
    }
}

void RType::Server::Game::process(boost::asio::ip::udp::endpoint end,
std::vector<char> &str)
{
    auto v  = inputToContent(str);
    auto act = std::stoi(v.at(0));

    if (act == 10) {
        auto playerId = std::stoi(v.at(1));
        auto pos = v.at(2);

        auto pos_x = pos.substr(0, pos.find_first_of('@'));
        auto pos_y = pos.substr(pos.find_first_of('@') + 1, pos.size());

        auto p = std::make_tuple<std::int32_t, std::int32_t>(std::stoi(pos_x), std::stoi(pos_y));

        _players.push_back(RType::Server::Player());
        _players.rbegin()->setId(v.at(1));
        _players.rbegin()->setPos(p);

        std::cout << "player id : (" << playerId << ") spawn player" << std::endl;
    }
    else if (act == 100) {
        auto playerId = v.at(1);
        auto pos = v.at(2);
        auto pos_x = pos.substr(0, pos.find_first_of('@'));
        auto pos_y = pos.substr(pos.find_first_of('@') + 1, pos.size());
        auto p = std::make_tuple<std::int32_t, std::int32_t>(std::stoi(pos_x), std::stoi(pos_y));
        auto player = std::find_if(_players.begin(), _players.end(), [&](auto &pl) {
            return pl.getId() == playerId;
        });
        if (player != _players.end())
            player->setPos(p);
        std::cout << "player id : (" << std::stoi(v.at(1)) << ") moving" << std::endl;
    }
    else if (act == 101) {
        this->shoot(v.at(1));
        std::cout << "player id : (" << std::stoi(v.at(1)) << ") shooting" << std::endl;
    }
    //auto ret = contentToOutput(v);
    //_output.push(std::make_tuple(end, ret));
}

int RType::Server::Game::reset(void)
{
    return 0;
}

int RType::Server::Game::stop(void)
{
    _status = RType::Server::Game::__status__::Stopped;
    return 0;
}

int RType::Server::Game::start(void)
{
    if (!_th) {
        _th = std::make_unique<std::jthread>([&](){
            std::vector<char> str;

            std::random_device rd;
            std::mt19937 gen(rd());
            auto sp = std::bernoulli_distribution(0.05);

            while (true) {
                if (_status == RType::Server::Game::__status__::Stopped)
                    break ;
                if (!_input.isEmpty()) {
                    std::tuple<boost::asio::ip::udp::endpoint, std::vector<char>> element;
                    _input.pop(element);

                    auto endpoint = std::get<0>(element);
                    auto data = std::get<1>(element);

                    this->process(endpoint, data);
                }
                if (sp(gen)) {
                    std::uniform_int_distribution<> distX(400, 800);
                    std::uniform_int_distribution<> distY(0, 600);

                    auto eid = _enemId;
                    RType::Server::Enemy en(std::to_string(eid));

                    auto x = distX(gen);
                    auto y = distY(gen);

                    auto p = std::make_tuple(x, y);

                    en.setPos(p);
                    _enemies.push_back(en);

                    std::string res = "200";
                    res.append("/").append(std::to_string(eid)).append("/").
                        append(std::to_string(x)).append("@").append(std::to_string(y));
                    std::vector<char> v(res.begin(), res.end());
                    auto resp = std::make_tuple(_endpoint, v);
                    _output.push(resp);
                    std::cout << "game id (" << _id << ") : spawn enemy" << std::endl;
                    _enemId ++;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
    }
    return 0;
}