/*
** EPITECH PROJECT, 2020
** rtype_2020
** File description:
** Dot.hpp
*/

//class qui permet de hold des points de différents type

#ifndef _DOT_
#define _DOT_

#include <stdlib.h>
#include <iostream>
#include <math.h>

template <typename T>
class dot {
public:
    dot() = default;
    dot(T x, T y): x_pos(x), y_pos(y) {};
    dot(const dot &copy): x_pos(copy.x_pos), y_pos(copy.y_pos) {};
    virtual ~dot() = default;
public:
    void dump() {
        std::cout << "POSX: " << x_pos << std::endl;
        std::cout << "POSX: " << x_pos << std::endl << std::endl;
    };
public:
    dot &operator=(const dot& equal) {
        x_pos = equal.x_pos;
        y_pos = equal.y_pos;
        return *this;
    };
    bool operator==(dot &equal) {return x_pos == equal.getX() && y_pos == equal.gety();};
    bool operator!=(dot &equal) {return x_pos != equal.getX() || y_pos != equal.getY();};
    void setX(T x) {x_pos = x;};
    void setY(T y) {y_pos = y;};
    T getX() {return x_pos;};
    T getY() {return y_pos;};
    void IncX(T x) {x_pos += x;};
    void IncY(T y) {y_pos += y;};
private:
    T x_pos;
    T y_pos;
};

#endif