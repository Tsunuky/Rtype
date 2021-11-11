/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** Objects
*/

#ifndef OBJSPRITE_HPP
#define OBJSPRITE_HPP

#include "IObject.hpp"

class ObjSprite: public PrimaryObj {

public:
    ObjSprite(std::shared_ptr<std::map<std::string, Sprite>> Sprites, std::shared_ptr<std::map<std::string, Texture*>> Textures, RenderWindow *Window, std::string path, Vector2f pos, bool visible) {
        _Window = Window;
        _Sprites = Sprites;
        _Textures = Textures;
        _pos = pos;
        _Sprite = createSprite(path);
        if (!_Sprite.getTexture()) {
            _Window->close();
            throw RtypeException<CException::LibException>("Error ObjSprite");
        }
        _Visible = visible;
    };
public:
    Sprite createSprite(std::string path) {
        if (!(*_Sprites).empty() && (*_Sprites).find(path) != (*_Sprites).end()) {
            return (*_Sprites)[path];
        }
        _Sprite.setTexture(*createTexture(path));
        setPosition(_pos);
        (*_Sprites)[path] = _Sprite;
        return (*_Sprites)[path];
    };
    Sprite createSprite(std::string path, IntRect rect) {
        if (!(*_Sprites).empty() && (*_Sprites).find(path) != (*_Sprites).end()) {
            return (*_Sprites)[path];
        }
        _Sprite.setTexture(*createTexture(path));
        setPosition(_pos);
        _Sprite.setTextureRect(rect);
        (*_Sprites)[path] = _Sprite;
        return (*_Sprites)[path];
    };
    bool getVisible() {
        return _Visible;
    };
    void setVisible(bool visible) {
        //std::cout << visible << std::endl;
        _Visible = visible;
    };
    void setPosition(Vector2f pos) {
        _Sprite.setPosition(pos);
    };
    void setRotation(float pos) {
        _Sprite.setRotation(pos);
    };
    void displaySprite() {
        if (_Visible)
            (*_Window).draw(_Sprite);
    }
    void setScale(float x, float y) {
        _Sprite.setScale(x , y);
    }
private:
    RenderWindow *_Window;
    Sprite _Sprite;
    Vector2f _pos;
    std::shared_ptr<std::map<std::string, Sprite>> _Sprites;
    bool _Visible;
};

#endif