/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-leonard.pooch
** File description:
** IEnnemi
*/

#ifndef IENNEMI_HPP_
#define IENNEMI_HPP_

#include <vector>

#include "System.hpp"

class IEnnemi {
    public:
        virtual ~IEnnemi() = default;
        virtual void setPv(int pv, int id) = 0;
        virtual int getPv(int id) = 0;
        virtual void checkPv(int id) = 0;
        virtual void addEnnemy(std::string file, dot<float> pos, int pv, uint id) = 0;
        virtual void removeEnnemy(uint id) = 0;
        virtual std::shared_ptr<std::vector<Entity>> getEntity(void) = 0;
        virtual Object_t getObject(int id) = 0;
        virtual void getPosition(dot<float> pos, int id) = 0;
};

#endif /* !IENNEMI_HPP_ */
