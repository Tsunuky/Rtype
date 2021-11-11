/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#include <iostream>
#include <boost/exception/diagnostic_information.hpp>
#include "includes/Core/Core.hpp"
#include "includes/Core/Init.hpp"

int main(const int ac, const char *const *const av)
{
    try {
        Initializor init;

        Core instance(av[1], av[2], init.container(), init.Game());
        instance.launcher(1);
    } catch (const std::exception &err) {
        std::clog << boost::current_exception_diagnostic_information() << std::endl;
        return 84;
    } catch (...) {
        std::clog << boost::current_exception_diagnostic_information() << std::endl;
        return 84;
    }
    return 0;
}
