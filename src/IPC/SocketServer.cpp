/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** SocketServer
*/

#include "SocketServer.hpp"

SocketServer::SocketServer()
{
    int opt = 1;

    if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		std::exit(84);
	if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        std::exit(84);
    this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(PORT);
    if (bind(this->server_fd, (struct sockaddr *) &this->address, sizeof(this->address)) < 0) {
        std::exit(84);
    }
	if (listen(this->server_fd, 10) < 0) {
        std::exit(84);
    }
}

SocketServer::~SocketServer()
{
}

int SocketServer::acceptNewClient()
{
    int new_socket = 0;
    int addrlen = sizeof(address);

    if ((new_socket = accept(this->server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
        std::exit(84);
    return (new_socket);
}

void SocketServer::sendSocket(int fd, std::string message)
{
    send(fd, message.c_str(), message.length(), 0);
}

std::string SocketServer::readSocket(int fd)
{
    int tmp;
    char buffer[1024] = { 0 };

    tmp = recv(fd, buffer, 1024, 0);
    if (tmp < 0)
        return ("");
    std::string str(buffer);
    return str;
}

void SocketServer::closeServer()
{
    shutdown(this->server_fd, SHUT_RDWR);
}

void SocketServer::closeClient(int fd)
{
    close(fd);
}

