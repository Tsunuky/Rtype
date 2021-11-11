/*
** EPITECH PROJECT, 2020
** rtype_2020
** File description:
** ECS.hpp
*/

#ifndef _GRAPH_
#define _GRAPH_

#include <memory>
#include <vector>
#include <map>
//
typedef unsigned int uint;
//
struct Tags {
    uint Position: 1;
    uint PhysicalObj: 1;
    uint Drawable: 1;
    uint Playable: 1;
    uint Rotate: 1;
};

class Entity {
public:
    Entity(uint id, Tags attribute): _id(id), _attribute(attribute) {};
    ~Entity() = default;
public:
    int _id;
    Tags _attribute = {0, 0, 0, 0, 0};
};

template <class Compoment>
class Storage {
public:
    Storage() = default;
    ~Storage() = default;
public:
    void AddComponent(int ID, Compoment args) {
        _storage.emplace(ID, args);
    };
    void DeleteComponent(int ID) {
        auto tmp = _storage.find(ID);
        if (tmp != _storage.end())
            _storage.erase(tmp);
    };
    auto Find(int ID) { return _storage.find(ID);};
public:
    std::map<int, Compoment> _storage;
};

#endif