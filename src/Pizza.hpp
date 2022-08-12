/*
** EPITECH PROJECT, 2022
** Plazza
** File description:
** class Pizza
*/

#ifndef __PIZZA_HPP__
    #define __PIZZA_HPP__

    #include "Plazza.hpp"
    #include <iostream>
    #include <vector>
    #include "String.hpp"

class Pizza {
    public:
        Pizza();
        ~Pizza();
        std::string pack();
        void unpack(std::string);
        size_t order;
        Plazza::PizzaType type;
        Plazza::PizzaSize size;
        
};

#endif /* !__PIZZA_HPP__ */
