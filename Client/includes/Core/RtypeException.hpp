/*
** EPITECH PROJECT, 2020
** rtype_2020
** File description:
** RtypeException.hpp
*/

#ifndef _RTYPE_EXCEPTION_
#define _RTYPE_EXCEPTION_

#include <exception>
#include <string>

enum class CException {
    LibException,
//      -----> A remplir
};

template <enum CException>
class RtypeException: public std::exception {
public:
    RtypeException(const std::string &mess): _errorMess(mess) {};
    virtual ~RtypeException() = default;
    virtual const char *what() const noexcept override {return _errorMess.c_str();};
private:
    std::string _errorMess;
};

#endif