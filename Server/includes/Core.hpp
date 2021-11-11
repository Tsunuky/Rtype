/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <cstdint>

namespace RType {
    namespace Server {
        class Core {
            private :
                const int _ac;
                const char *const *const _av;
                std::int32_t _port;
            public :
                Core(const int, const char *const *const);
                ~Core(void) = default;
                bool check_args(void);
                int launch(void);
        };
    }
}

#endif