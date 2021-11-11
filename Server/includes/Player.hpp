/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "Enemy.hpp"

namespace RType{
    namespace Server {
        class Player {
            private :
                std::string _id = "ERROR";
                std::int32_t _pos_x;
                std::int32_t _pos_y;
            public :
                Player(void) = default;
                Player(const std::string &id) : _id(id), _pos_x(-1), _pos_y(-1) {};
                ~Player(void) = default;
                const std::string getId(void) { return _id; };
                void setId(const std::string &id) { _id = id; }
                const std::tuple<int32_t, int32_t> getPos(void) {
                    return std::make_tuple(_pos_x, _pos_y);
                };
                void setPos(std::tuple<int32_t, int32_t> &pos) {
                    _pos_x = std::get<0>(pos);
                    _pos_y = std::get<1>(pos);
                }
                std::vector<std::string> shoot(std::vector<RType::Server::Enemy> &);
                void move(void);
        };
    }
}

#endif