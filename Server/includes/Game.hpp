/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>
#include <thread>
#include <memory>
#include <vector>
#include <tuple>
#include <boost/asio.hpp>
#include "Player.hpp"
#include "Queue.hpp"
#include "Enemy.hpp"

namespace RType {
    namespace Server {
        class Game {
            public :
                enum class __status__ {
                    Running = 1,
                    Stopped = 2
                };
                const std::string &getName(void) const { return _name; }
                int getID(void) const { return _id; }

                RType::Server::Queue<std::tuple<boost::asio::ip::udp::endpoint,
                    std::vector<char>>> &getInput(void) { return _input; }
                RType::Server::Queue<std::tuple<boost::asio::ip::udp::endpoint,
                    std::vector<char>>> &getOutput(void) { return _output; }

                void shoot(const std::string &);
                void process(boost::asio::ip::udp::endpoint, std::vector<char> &);

                int reset(void);
                int stop(void);
                int start(void);

                Game(void) = default;
                Game(int id, const std::string &name) : _id(id), _name(name) {
                    _enemId = 500;
                    _status = RType::Server::Game::__status__::Running;
                    this->start();
                }
                ~Game(void) = default;
                void setEndpoint(boost::asio::ip::udp::endpoint endpoint) {
                    _endpoint = endpoint;
                };
                static std::vector<char> contentToOutput(std::vector<std::string> &input) {
                    std::vector<char> res;

                    for (auto &i : input) {
                        for (auto j : i)
                            res.push_back(j);
                        res.push_back('/');
                    }
                    if (res.size() > 0) {
                        res.pop_back();
                    }
                    return res;
                }
                static std::vector<std::string> inputToContent(std::vector<char> &input) {
                    std::vector<std::string> res;

                    auto str = std::string(input.begin(), input.end());
                    std::string delimiter = "/";
                    for (auto index = str.find(delimiter); index != std::string::npos; index = str.find(delimiter)) {
                        res.push_back(str.substr(0, index));
                        str = str.substr(index + delimiter.length());
                    }
                    res.push_back(str);
                    return res;
                }
            private :
                int _id;
                std::string _name;

                int _enemId;

                RType::Server::Queue<std::tuple<boost::asio::ip::udp::endpoint,
                    std::vector<char>>> _input;
                RType::Server::Queue<std::tuple<boost::asio::ip::udp::endpoint,
                    std::vector<char>>> _output;

                RType::Server::Game::__status__ _status;
                std::unique_ptr<std::jthread> _th;

                std::vector<RType::Server::Player> _players;
                std::vector<RType::Server::Enemy> _enemies;
                boost::asio::ip::udp::endpoint _endpoint;
        };
    }
}

#endif