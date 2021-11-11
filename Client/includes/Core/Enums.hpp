/*
** EPITECH PROJECT, 2020
** rtype_2020
** File description:
** Enums.hpp
*/

#ifndef __ENUMS__HPP__
#define __ENUMS__HPP__

#include "Dot.hpp"

enum TYPE {
    OBJSPRTE,
};

enum ENTITY_TYPE {
    PLAYER,
    WALL,
    PROJECTILE,
    POWERUP,
};

struct Object_t {
    int id;
    std::string _path;
    dot<float> _Position;
    dot<float> _OldPosition;
    float x;
    TYPE _type;
    bool _IsVisible;
};

enum INPUT {
    LEFT,
    DOWN,
    UP,
    RIGHT,
    START,
    ATTACK,
    POWEROFF,
    NO_INPUT,
};

enum KEYS {
Unknown = -1, 
    A = 0,        
    B,   
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Escape, 
    LControl,  
    LShift,    
    LAlt,
    LSystem,
    RControl,  
    RShift, 
    RAlt,
    RSystem,
    Menu,
    LBracket,  
    RBracket,  
    Semicolon, 
    Comma,
    Period, 
    Quote,
    Slash,
    Backslash, 
    Tilde,
    Equal,
    Hyphen, 
    Space,
    Enter,
    Backspace, 
    Tab, 
    PageUp, 
    PageDown,
    End, 
    Home,
    Insert, 
    Delete, 
    Add, 
    Subtract,
    Multiply,
    Divide, 
    Left,
    Right,
    Up,
    Down,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10, 
    F11, 
    F12, 
    F13, 
    F14, 
    F15, 
    Pause, 
    KeyCount,
    Dash= Hyphen, 
    BackSpace = Backspace, 
    BackSlash = Backslash, 
    SemiColon = Semicolon, 
    Return = Enter 
};

#endif
