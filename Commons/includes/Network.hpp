/*
** EPITECH PROJECT, 2020
** rtype
** File description:
** rtype
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <vector>
#include <cstdint>
#include <iostream>
#include <functional>
#include <boost/asio.hpp>

namespace RType {
    namespace Network {
        class UDPEndpoint {
            public :
                using Handler = std::function<void(const std::vector<char> &, boost::asio::ip::udp::endpoint)>;
            private :
                boost::asio::io_context _context;
                boost::asio::ip::udp::socket _socket;
                Handler _handler;
                std::array<char, 1024> _receiveBuffer;
                boost::asio::ip::udp::endpoint _receiveEndpoint;
            public :
                UDPEndpoint(std::uint16_t port) : _context(), _socket(_context,
                    boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {}
                ~UDPEndpoint(void) { _socket.close(); }
                bool init(Handler handler) {
                    _handler = handler;
                    _socket.async_receive_from(boost::asio::buffer(_receiveBuffer), _receiveEndpoint,
                        [this](const boost::system::error_code &ec, const std::size_t len){ this->handler(ec, len); });
                    return true;
                }
                void handler(const boost::system::error_code &ec, const std::size_t len) {
                    //std::cerr << "HANDLER" << std::endl;
                    _handler(std::vector<char>(std::begin(_receiveBuffer), std::begin(_receiveBuffer) + len), _receiveEndpoint);
                    _socket.async_receive_from(boost::asio::buffer(_receiveBuffer), _receiveEndpoint,
                        [this](const boost::system::error_code &ec, const std::size_t len){ this->handler(ec, len); });
                }
                void send(boost::asio::ip::udp::endpoint endpoint, const std::vector<char> &arr) {
                    std::array<char, 1024> sendBuffer;

                    std::copy(arr.begin(), arr.end(), sendBuffer.begin());
                    _socket.async_send_to(boost::asio::buffer(sendBuffer, arr.size()), endpoint,
                    [this](const boost::system::error_code &ec, const std::size_t rlen){
                        return ;
                    });
                }
                boost::asio::io_context &getContext(void) { return _context; }
                static std::unique_ptr<UDPEndpoint> createEndpoint(const std::uint16_t port) {
                    return std::make_unique<UDPEndpoint>(port);
                }
                static std::unique_ptr<UDPEndpoint> createEndpoint(void) {
                    return std::make_unique<UDPEndpoint>(0);
                }
        };
        class NetworkClient {
            private :
                std::unique_ptr<UDPEndpoint> _endpoint;
                boost::asio::ip::udp::endpoint _end;
            public :
                NetworkClient(boost::asio::ip::udp::endpoint endpoint) :
                    _endpoint(UDPEndpoint::createEndpoint()), _end(endpoint) {}
                boost::asio::io_context &getContext(void) {
                    return _endpoint.get()->getContext();
                }
                bool init(UDPEndpoint::Handler &handler) {
                    return _endpoint->init(handler);
                }
                void send(const std::vector<char> &arr) {
                    _endpoint->send(_end, arr);
                }
                static std::unique_ptr<NetworkClient> createClient(const std::string &host, const std::string &port) {
                    boost::asio::io_context context;
                    boost::asio::ip::udp::resolver resolver(context);
                    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
                    boost::asio::ip::udp::resolver::iterator iterator(resolver.resolve(query));

                    return std::make_unique<NetworkClient>(*iterator);
                }
        };
    }
}

#endif