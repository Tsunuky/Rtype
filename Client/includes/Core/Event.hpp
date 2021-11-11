/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-leonard.pooch
** File description:
** Event.hpp
*/

#ifndef _EVENT_
#define _EVENT_

#include "../Graph/LibSFML.hpp"
#include "Enums.hpp"

class MyEventReceiver: public sf::Event {
public:
    MyEventReceiver() {
        for (std::uint32_t i = 0; i < KEYS::KeyCount ; ++i)
            KeyIsDown[i] = false;
    };
    virtual bool OnEvent(const sf::Event event) {
        if (event.type == sf::Event::KeyPressed)
            KeyIsDown[event.key.code] = true;
        return false;
    };
    virtual bool IsKeyDown(KEYS keyCode) const {
        return KeyIsDown[keyCode];
    };
private:
    bool KeyIsDown[KEYS::KeyCount];
};

#endif
