/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** status
*/

#include "Status.hpp"
#include <iostream>

Status::Status()
{
}

Status::~Status()
{
}

std::string Status::pack()
{
    std::string message = "status ";
    // message = message + std::to_string(this->type) + " " + std::to_string(this->size) + "\n";
    message = message + std::to_string(this->waitingPizza) + " ";

    for (size_t status : this->cookStatus) {
        message = message + std::to_string(status) + " ";
    }
    message = message + std::to_string(this->elements["doe"]) + " ";
    message = message + std::to_string(this->elements["tomato"]) + " ";
    message = message + std::to_string(this->elements["gruyere"]) + " ";
    message = message + std::to_string(this->elements["ham"]) + " ";
    message = message + std::to_string(this->elements["mushrooms"]) + " ";
    message = message + std::to_string(this->elements["steak"]) + " ";
    message = message + std::to_string(this->elements["eggplant"]) + " ";
    message = message + std::to_string(this->elements["goat cheese"]) + " ";
    message = message + std::to_string(this->elements["chief love"]);
    message = message + "\n";
    return (message);
}

void Status::unpack(std::string message, size_t nbCook)
{
    message = message.substr(7);
    std::vector<std::string> str = Utils::String::split(message, ' ');

    this->waitingPizza = stoi(str[0]);
    for (size_t i = 0; i < nbCook; i++) {
        this->cookStatus.push_back(stoi(str[i + 1]));
    }
    this->elements["doe"] = stoi(str[nbCook + 1]);
    this->elements["tomato"] = stoi(str[nbCook + 2]);
    this->elements["gruyere"] = stoi(str[nbCook + 3]);
    this->elements["ham"] = stoi(str[nbCook + 4]);
    this->elements["mushrooms"] = stoi(str[nbCook + 5]);
    this->elements["steak"] = stoi(str[nbCook + 6]);
    this->elements["eggplant"] = stoi(str[nbCook + 7]);
    this->elements["goat cheese"] = stoi(str[nbCook + 8]);
    this->elements["chief love"] = stoi(str[nbCook + 9]);
}

bool Status::operator<(const Status& status) const
{
    return (this->kitchenId < status.kitchenId);
}
