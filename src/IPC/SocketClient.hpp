/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** SocketClient
*/

#ifndef __SOCKET_CLIENT_HPP__
    #define __SOCKET_CLIENT_HPP__

    #include "SocketServer.hpp"
    #include <arpa/inet.h>

class SocketClient {
    public:
        SocketClient();
        ~SocketClient();
        void connectServer();
        void sendSocket(std::string message);
        std::string readSocket();
        void closeClient();

    private:
        int sock = 0;
};

#endif /* !__SOCKET_CLIENT_HPP__ */
