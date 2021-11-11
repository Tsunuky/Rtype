/*
** EPITECH PROJECT, 2020
** rtype_2020
** File description:
** Parsers.hpp
*/

#ifndef _PARSER_
#define _PARSER_

#include <boost/algorithm/string.hpp>
#include <boost/config.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <map>

typedef unsigned int uint;

struct libPool {
    std::string _title;
    std::map<std::string, std::string> _section;
};

class Parser {
public:
    Parser(std::string str) {parserConfFile(str);};
    virtual ~Parser() = default;
public:
    std::vector<libPool> getAllParser() const { return _libParsing; };
    void parserConfFile(const std::string &);
    libPool getPartParser(int i) const { return _libParsing[i]; };
    libPool getPartParser(std::string str) const {
        for (uint i = 0; i < _libParsing.size(); ++i) {
            if (_libParsing[i]._title == str)
                return _libParsing[i];
            }
        throw std::invalid_argument("Section Name doesn't know");
    };
    int getIndex(const std::string name) const {
        for (uint i = 0; i < _libParsing.size(); ++i) {
            if (_libParsing[i]._title == name)
                return i;
        }
        return -1;
    };
    void dump(void) {
        for (uint i = 0; i  < _libParsing.size(); i++) {
            std::cerr << "vector : " << i << "\n";
            std::cerr << "LIB : " << _libParsing[i]._section["lib"] << '\n';
            std::cerr << "LIB : " << _libParsing[i]._section["game"] << '\n';
            std::cerr << '\n' << "/* --------------- */" << '\n';
        }
    }
private:
    void parseSection(const std::string &);
    std::vector<libPool> _libParsing; 
};


#endif