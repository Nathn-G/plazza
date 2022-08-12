#ifndef __CHIEF_HPP__
    #define __CHIEF_HPP__

    #include "PlazzaNamespace.hpp"
    #include <iostream>
    #include <memory>
    #include <condition_variable>
    #include <mutex>
    #include <queue>
    #include <map>
    #include "Plazza.hpp"
    #include "Pizza.hpp"
    #include <chrono>
    #include "SocketClient.hpp"
    #include <tuple>

class Plazza::Kitchen::Chief {
    private:
        std::queue<Pizza> m_queue_in;
        std::queue<Pizza> m_queue_out;
        std::mutex m_lock;
        std::condition_variable m_data_condition;
        float xPizza = 0;
        std::size_t xIngredient = 0;
        std::map<std::string, int> fridge = {
            {"doe", 5},
            {"tomato", 5},
            {"gruyere", 5},
            {"ham", 5},
            {"mushrooms", 5},
            {"steak", 5},
            {"eggplant", 5},
            {"goat cheese", 5},
            {"chief love", 5}
        };
        std::map<std::string, std::tuple<int, std::vector<std::string>>> pizzaReceipe;
        std::map<PizzaType, std::string> mapType = {
            {Regina, "regina"},
            {Margarita, "margarita"},
            {Americana, "americana"},
            {Fantasia, "fantasia"}
        };

    public:
        Chief();
        void Cooking(int, std::shared_ptr<std::size_t>, SocketClient client);
        void push(Pizza);
        void refillFridge();
        int getSizeQueueIn();
        bool checkIsIngredient(std::vector<std::string> required);
        int getNbElement(std::string element);
        void setxPizza(float time);
        void notify();
};

#endif