/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include <tuple>
#include <string>
#include <utility>

namespace RType{
    namespace Server {
        class Enemy {
            private :
                std::string _id;
                std::int32_t _pos_x;
                std::int32_t _pos_y;
            public :
                Enemy(const std::string &id) : _id(id), _pos_x(-1), _pos_y(-1) {};
                ~Enemy(void) = default;
                const std::string getId(void) { return _id; };
                const std::tuple<int32_t, int32_t> getPos(void) {
                    return std::make_tuple(_pos_x, _pos_y);
                };
                void setPos(std::tuple<int32_t, int32_t> &pos) {
                    _pos_x = std::get<0>(pos);
                    _pos_y = std::get<1>(pos);
                }
        };
    }
}

#endif