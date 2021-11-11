/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-leonard.pooch
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include "../Core/Enums.hpp"

#include <vector>
#include <map>
//
typedef unsigned int uint;
//
class IGraphic {
public:
    virtual ~IGraphic() = default;
    virtual void draw() = 0;
    virtual void displayWindow() = 0;
    virtual int eventWindow()= 0;
    virtual std::vector<INPUT> getInput(std::vector<std::map<KEYS, INPUT>> keys_map) = 0;
    virtual void setPosition(uint id, dot<float>) = 0;
    virtual void setRotation(uint id, dot<float>) = 0;
    virtual void setScale(uint id, dot<float>) = 0;
    virtual void createObj(Object_t) = 0;
    virtual void EraseObj(uint id) = 0;
    virtual bool exist(uint id) = 0;
    virtual bool IsAvailable(uint id) = 0;
    virtual void ObjVisible(uint id, bool visible) = 0;
    virtual std::vector<int> getEntity() = 0;
};

#endif /* !IGRAPHIC_HPP_ */