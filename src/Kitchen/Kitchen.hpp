#ifndef __KITCHEN_HPP__
    #define __KITCHEN_HPP__

    #include "Chief.hpp"
    #include <vector>
    #include "Fork.hpp"
    #include "SocketClient.hpp"
    #include <memory>
    #include <thread>
    #include "Plazza.hpp"
    #include "String.hpp"
    #include "Pizza.hpp"
    #include "Status.hpp"

    #define CURRENT_PROCESS 0

class Plazza::Kitchen::Kitchen {
    private:
        float xPizza = 0;
        std::size_t xIngredient = 0;
        std::size_t nbCooks = 0;
        std::vector<std::shared_ptr<std::size_t>> chiefs_status;
        std::vector<std::thread> chiefs_t;
        std::thread readReception;
        std::thread loopRefillFridge;
        std::shared_ptr<bool> active;

    public:
        Kitchen(float xPizza, std::size_t nbCooks, std::size_t xIngredient);
        ~Kitchen();
        std::size_t getNbCooks() const;
        void run();
        void createChiefs();
        void loopReadReception();
        void addToQueue(Pizza);
        static void do_order_message(std::string message);
        SocketClient client;
        int fdSocket;
        static void refillFridge(std::size_t time, std::shared_ptr<bool>);
};

#endif