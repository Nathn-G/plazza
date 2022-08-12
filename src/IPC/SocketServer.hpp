/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** SocketServer
*/

#ifndef __SOCKET_SERVER_HPP__

    #define __SOCKET_SERVER_HPP__
    #define PORT 8066

    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <iostream>
    #include <unistd.h>

class SocketServer {
    public:
        SocketServer();
        ~SocketServer();
        int acceptNewClient();
        void sendSocket(int fd, std::string message);
        std::string readSocket(int fd);
        void closeServer();
        void closeClient(int fd);

    private:
        int server_fd;
        struct sockaddr_in address;
};

#endif /* !__SOCKET_SERVER_HPP__ */
