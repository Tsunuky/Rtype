/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#include "Core.hpp"

int main(const int ac, const char *const *const av)
{
    RType::Server::Core core(ac, av);

    if (!core.check_args())
        return 84;
    return core.launch();
}