#ifndef __PLAZZA_HPP__
    #define __PLAZZA_HPP__

    #include <map>

namespace Plazza {
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };
    
    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    typedef struct pizza_s {
        PizzaType type;
        PizzaSize size;
    } pizza_t;

    typedef struct kitchen_pizza_s {
        int nbOrder;
        Plazza::PizzaType type;
        Plazza::PizzaSize size;
        int status; // 0 need Cook; 1 Cooking; 2 Cooked
    } kitchen_pizza_t;
}

#endif