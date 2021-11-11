/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** IObject
*/

#ifndef IOBJECT_HPP_
#define IOBJECT_HPP_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
 #include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "../Core/RtypeException.hpp"

using namespace sf;

class IObject {
public:
    virtual ~IObject() = default;
    virtual void setPosition(Vector2f pos) = 0;
    virtual void setRotation(float pos) = 0;
    virtual void setTexture(std::string path) = 0;
    virtual void setVisible(bool active) = 0;
    virtual void setScale(float x, float y) = 0;
    virtual void displaySprite() = 0;
    virtual Texture* createTexture(std::string path) = 0;
    virtual bool getVisible() = 0;
};

class PrimaryObj: public IObject {
public:
    ~PrimaryObj() = default;
    virtual void setPosition(Vector2f pos) = 0;
    virtual void setRotation(float pos) = 0;
    virtual void displaySprite() = 0;
    virtual void setScale(float x, float y) = 0;
    virtual void setTexture(std::string path) {path = "";};
    virtual void setVisible(bool active) = 0;
    virtual bool getVisible() = 0;
    virtual Texture* createTexture(std::string path) {
        if (!(*_Textures).empty() && (*_Textures).find(path) != (*_Textures).end()) { 
            return (*_Textures)[path];
        }
        if (!_Texture.loadFromFile(path))
            throw RtypeException<CException::LibException>("Error createTexture");
        _Texture.loadFromFile(path);
        (*_Textures)[path] = &_Texture;
        return (*_Textures)[path];
    };
protected:
    std::shared_ptr<std::map<std::string, Texture*>> _Textures;
    Texture _Texture;
};

#endif /* !IOBJECT_HPP_ */
