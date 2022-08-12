/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** Status
*/

#ifndef __STATUS_HPP__
    #define __STATUS_HPP__

    #include <string>
    #include <vector>
    #include <map>
    #include "String.hpp"

class Status {
    public:
        Status();
        ~Status();
        std::string pack();
        void unpack(std::string, size_t nbCook);
        bool operator<(const Status& status) const;
        size_t waitingPizza;
        std::vector<size_t> cookStatus;
        std::map<std::string, size_t> elements;
        size_t kitchenId;
};

#endif /* !__STATUS_HPP__ */
