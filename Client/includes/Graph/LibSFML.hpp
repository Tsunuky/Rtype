/*
** EPITECH PROJECT, 2020
** Visual Studio Live Share (Workspace)
** File description:
** LibSFML
*/

#ifndef LIBSFML_HPP_
#define LIBSFML_HPP_

#include "IGraphic.hpp"
#include "Objects.hpp"
#include "../Core/ECS.hpp"


class LibSFML: public IGraphic {
public:
    LibSFML() {
        _Window.create(sf::VideoMode(800, 600, 32), "rtype");
        _sprite = std::make_shared<std::map<std::string, Sprite>>();
        _texture = std::make_shared<std::map<std::string, Texture*>>();
    };
    void draw() {
        for (auto &i: Objs._storage)
            if (i.second->getVisible() == true)
                i.second->displaySprite();
    };
    int eventWindow() {
        while (_Window.pollEvent(_event)) {
            if (_event.type == Event::Closed) {
                _Window.close();
                return -1;
            }
            if (_event.type == Event::KeyPressed)
                getKey();
        }
        return 0;
    };
    void displayWindow() {
        _Window.clear(sf::Color(0, 0, 50));
        draw();
        _Window.display();
    }
    std::vector<INPUT> getInput(std::vector<std::map<KEYS, INPUT>> keys_map) {
        std::vector<INPUT> tmp;

        for (auto &j: keys_map) {
            for (auto &i: _keys) {
                tmp.push_back(j.at(i));
            }
        }
        _keys.clear();
        return tmp;
    };
    void getKey() {
        _keys.emplace_back(static_cast<KEYS>(_event.key.code));
    };
    void setPosition(uint id, dot<float> pos) {
        if (!Objs.Find(id)->second)
            throw RtypeException<CException::LibException>("Error this object don't exist");
        Vector2f vect = {pos.getX(), pos.getY()};
        Objs.Find(id)->second.get()->setPosition(vect);
    };
    void setRotation(uint id, dot<float> rotate) {
        if (!Objs.Find(id)->second)
            throw RtypeException<CException::LibException>("Error this object don't exist");
        Objs.Find(id)->second.get()->setRotation(rotate.getX());
    };
    void setScale (uint id, dot<float> scale) {
        if (!Objs.Find(id)->second)
            throw RtypeException<CException::LibException>("Error this object don't exist");
        Objs.Find(id)->second.get()->setScale(scale.getX(), scale.getY());
    }
    void createObj(Object_t obj) {
        if (obj._type == TYPE::OBJSPRTE)
            createObj(_sprite, _texture, obj._type, obj.id, obj._path, obj._Position, obj._IsVisible);
    };
    void createObj(std::shared_ptr<std::map<std::string, Sprite>> _Sprites,
        std::shared_ptr<std::map<std::string, Texture*>> _Textures, TYPE type, int id, std::string path, 
        dot<float> pos, bool visible) {
            Vector2f vect = {pos.getX(), pos.getY()};
            if (type == TYPE::OBJSPRTE) {
                std::shared_ptr<IObject> tmp(new ObjSprite(_Sprites, _Textures, &_Window, path, vect, visible));
                Objs.AddComponent(id, tmp);
            }
    };
    RenderWindow *getWindow() {
        return &_Window;
    };
    void EraseObj(uint id) {
        if(!Objs.Find(id)->second)
            throw RtypeException<CException::LibException>("Error this object don't exist");
        Objs.DeleteComponent(id);
    };
    bool exist(uint id) {
        if(Objs.Find(id) != Objs._storage.end())
            return true;
        return false;
    };
    bool IsAvailable(uint id) {
        if(!Objs.Find(id)->second || !Objs.Find(id)->second.get())
            return false;
        return true;
    };
    void ObjVisible(uint id, bool visible) {
        if(!Objs.Find(id)->second)
            throw RtypeException<CException::LibException>("Error this object don't exist");
        Objs.Find(id)->second.get()->setVisible(visible);
    };
    std::vector<int> getEntity() {
        std::vector<int> tmp;

        if (!_Window.isOpen()) {
            tmp.push_back(-5);
            return tmp;
        }
        for (auto &i: Objs._storage)
            tmp.push_back(i.first);
        return tmp;
    };

private:
    RenderWindow _Window;
    Event _event;
    std::vector<KEYS> _keys;
public:
    Storage<std::shared_ptr<IObject>> Objs;
    std::shared_ptr<std::map<std::string, Sprite>> _sprite;
    Storage<sf::Vector2f> Pos;
    std::shared_ptr<std::map<std::string, sf::Texture*>> _texture;
};

class LibContainer {
public:
    virtual IGraphic *getLib(void) = 0;
};

class LibContainerSFML: public LibContainer {
public:
    LibContainerSFML(IGraphic *lib) {
        _graphLib = (LibSFML *)lib;
    };
    virtual ~LibContainerSFML() = default;
public:
    virtual IGraphic *getLib(void) {
        return (IGraphic *)_graphLib;
    };
public:
    LibSFML *_graphLib;
};

#endif /* !LIBSFML_HPP_ */
