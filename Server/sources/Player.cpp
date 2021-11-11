/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"

std::vector<std::string> RType::Server::Player::shoot(std::vector<RType::Server::Enemy> &enemies)
{
    std::vector<std::string> res;
    std::cerr << "Player:" << _pos_y << "|" << _pos_x << std::endl; 
    for (int cpt = 0; cpt < enemies.size(); cpt++) {
        auto e = enemies.at(cpt);
        auto posEnemyX = std::get<0>(e.getPos());
        auto posEnemyY = std::get<1>(e.getPos());
        std::cerr << "Enemy:" << posEnemyX << "|" << posEnemyY << std::endl;
        if (_pos_y - 50 <= posEnemyY && posEnemyY <= _pos_y) {
            res.push_back(e.getId());
            std::cerr << "MATCH:" << e.getId() << std::endl;
        }
    }
    return res;
}

void RType::Server::Player::move(void)
{
}