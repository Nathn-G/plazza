/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** SocketClient
*/

#include "SocketClient.hpp"

SocketClient::SocketClient()
{
	struct sockaddr_in serv_addr;
	if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		std::exit(84);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
		std::exit(84);
	int resp = connect(this->sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (resp < 0) {

		std::exit(84);
	}
}

SocketClient::~SocketClient()
{
}

void SocketClient::connectServer()
{
	
}

void SocketClient::sendSocket(std::string message)
{
    send(this->sock, message.c_str(), message.length(), 0);
}

std::string SocketClient::readSocket()
{
    int tmp;
    char buffer[1024] = { 0 };

	tmp = recv(this->sock, buffer, 1024, 0);
    if (tmp < 0)
        return ("");
    std::string str(buffer);
    return (str);
}

void SocketClient::closeClient()
{
	close(this->sock);
}
