/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-leonard.pooch
** File description:
** Init.hpp
*/

#include "../Core/Parser.hpp"
#include "../Graph/LibSFML.hpp"
#include "../Games/IGame.hpp"
#include "../Core/DLLoader.hpp"

#ifndef __INIT__HPP__
#define __INIT__HPP__

class Initializor {
public:
    Parser _parser;
    //Initializor(1) default ctor
    //~Initializor(1) default dtor
    Initializor () : _parser("./conf.ini") {};
    virtual ~Initializor () = default;
    //Game : Load a game and return a ptr of it
    //Lib : Load a lib and return a ptr of it
    // Igame *Game();
    // Igraph *Lib();
    // LibContainer *container();
    DLLoader<Igame> loaderGame;
    DLLoader<IGraphic> loaderLib;
    DLLoader<LibContainer> loaderContainer;

Igame *Game(void)
{
    loaderGame.load(_parser.getPartParser("Core")._section["game"]);
    return loaderGame.getInstance("getLib");
}

IGraphic *Lib(void)
{
    loaderLib.load(_parser.getPartParser("Core")._section["lib"]);
    return loaderLib.getInstance("getLib");
}

LibContainer *container(void)
{
    loaderContainer.load(_parser.getPartParser("Core")._section["lib"]);
    return loaderContainer.getInstance("getContainer", Lib());
}

};

#endif