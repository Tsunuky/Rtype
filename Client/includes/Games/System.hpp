/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** system
*/

#ifndef __SYSTEM_ECS_HPP__
#define __SYSTEM_ECS_HPP__

#include <thread>
#include <chrono>

#include "../Core/ECS.hpp"
#include "../Core/Enums.hpp"


template <class T>
using StorageSPtr = std::shared_ptr<Storage<T>>;
using EntityVecSPtr = std::shared_ptr<std::vector<Entity>>;
using KeyBoard = std::vector<std::map<KEYS, INPUT>>;

class Chrono {
public:
    Chrono(int time = 360): _time(time) {};
    virtual ~Chrono() = default;
public:
    void Run() {
        while (_time > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            _time--;
        }
    };
    int getTime() {return _time;};
private:
    int _time;
};

class Isystem {
public:
    virtual void update(std::vector<INPUT>) = 0;
    virtual ~Isystem() = default;
};

#endif
