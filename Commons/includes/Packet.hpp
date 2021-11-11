/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <vector>
#include <memory>
#include <cstring>

//char _gameId[16];
//char _player1Id[16], _player2Id[16], _player3Id[16], _player4Id[16];
//char _p1pos[32], _p2pos[32], _p3pos[32], _p4pos[32];
//char _map[__mapHeight * __mapWidth];
//enemy pos

//static const int __mapHeight = 20;
//static const int __mapWidth = 200;

namespace RType {
    namespace Network {
        struct ServerPacket {
            std::int32_t _id;
            std::vector<char> _data;
            std::int32_t getId(void) const { return _id; }
            ServerPacket(void) : _id(-1) {}
            ~ServerPacket(void) = default;
            std::vector<char> &getData(void) { return _data; }
            const std::vector<char> &getData(void) const { return _data; }
            bool deserialize(const std::vector<char> &arr) {
                std::memcpy(&_id, arr.data(), sizeof(_id));
                std::int32_t len;
                std::memcpy(&len, arr.data() + sizeof(_id), sizeof(len));
                if (arr.size() != sizeof(_id) + sizeof(len) + len)
                    return false;
                _data.resize(len);
                std::memcpy(_data.data(), arr.data() + sizeof(_id) + sizeof(len), len);
                return true;
            }
            std::vector<char> serialize(void) {
                std::int32_t len = _data.size();
                std::vector<char> res(sizeof(_id) + sizeof(len) + len);
                std::memcpy(res.data(), &_id, sizeof(_id));
                std::memcpy(res.data() + sizeof(_id), &len, sizeof(len));
                std::memcpy(res.data() + sizeof(_id) + sizeof(len), _data.data(), len);
                return res;
            }
        };
    }
}

#endif