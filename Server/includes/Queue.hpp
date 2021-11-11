/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include <queue>
#include <mutex>

namespace RType {
    namespace Server {
        template<typename T>
        class IQueue {
            public :
                virtual ~IQueue(void) = default;
                virtual void push(const T &elem) = 0;
                virtual void pop(T &elem) = 0;
                virtual bool isEmpty(void) = 0;
                virtual int size(void) = 0;
        };
        template<typename T>
        class Queue : public IQueue<T> {
            private :
                std::mutex _mutex;
                std::queue<T> _vals;
            public :
                Queue(void) = default;
                ~Queue(void) = default;
                void push(const T &elem) {
                    std::unique_lock<std::mutex> lock(_mutex);
                    _vals.push(elem);
                }
                void pop(T &elem) {
                    std::unique_lock<std::mutex> lock(_mutex);
                    elem = _vals.front();
                    _vals.pop();
                }
                bool isEmpty(void) {
                    std::unique_lock<std::mutex> lock(_mutex);
                    return _vals.empty();
                }
                int size(void) {
                    std::unique_lock<std::mutex> lock(_mutex);
                    return _vals.size();
                }
        };
    }
}

#endif