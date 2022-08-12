/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** methods of class pizza
*/

#include "Pizza.hpp"

Pizza::Pizza()
{

}

Pizza::~Pizza()
{
    
}

std::string Pizza::pack()
{
    std::string message = "pizza " + std::to_string(this->order) + " ";
    message = message + std::to_string(this->type) + " " + std::to_string(this->size) + "\n";
    return (message);
}

void Pizza::unpack(std::string message)
{
    message = message.substr(6);
    std::vector<std::string> str = Utils::String::split(message, ' ');

    this->order = stoi(str[0]);
    this->type = static_cast<Plazza::PizzaType>(stoi(str[1]));
    this->size = static_cast<Plazza::PizzaSize>(stoi(str[2]));
}