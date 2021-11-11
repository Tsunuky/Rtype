/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#include <thread>
#include <cstdlib>
#include <functional>
#include "Server.hpp"
#include "Core.hpp"

RType::Server::Core::Core(const int ac, const char *const *const av) : _ac(ac), _av(av)
{
    return ;
}

bool RType::Server::Core::check_args(void)
{
    if (_ac != 2)
        return false;
    _port = std::strtol(_av[1], NULL, 10);
    if (_port < 0 || _port > 65535)
        return false;
    return true;
}

int RType::Server::Core::launch(void)
{
    RType::Server::Server server(_port);

    server.start();
    return 0;
}