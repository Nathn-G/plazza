/*
** EPITECH PROJECT, 2022
** Reception
** File description:
** class Reception
*/

#ifndef __RECEPTION_HPP__
    #define __RECEPTION_HPP__

    #include <iostream>
    #include "String.hpp"
    #include <map>
    #include "PlazzaNamespace.hpp"
    #include "Plazza.hpp"
    #include <vector>
    #include "Kitchen/Kitchen.hpp"
    #include "Errors/Convert.hpp"
    #include <iostream>
    #include "SocketServer.hpp"
    #include <sys/wait.h>
    #include "Pizza.hpp"
    #include "Status.hpp"
    #include <thread>
    #include <ctime>
    #include <memory>
    #include <fstream>

typedef struct kitchen_info_s kitchen_info_t;

struct kitchen_info_s {
    int id;
    int fd;
    int nbPizza;
    int64_t time;
    bool running;
};

class Plazza::Reception {
    public:
        Reception();
        ~Reception();
        int init(std::string cookingTime, std::string nbCook, std::string stock);
        void run();
        void handleLineShell(std::string line);
        void handleStatus();
        void handlePizza(std::string line);
        bool checkPizzaType(std::string str);
        bool checkPizzaSize(std::string str);
        bool checkPizzaQuantity(std::string str);
        bool createKitchen(std::size_t nb);
        void sendPizzaToKitchen(std::vector<Pizza> list);
        static bool compareKitchen(std::shared_ptr<kitchen_info_t> k1, std::shared_ptr<kitchen_info_t> k2);
        bool isFullKitchen(std::shared_ptr<kitchen_info_t> kitchen);
        static void receiveKitchenStatus(std::shared_ptr<kitchen_info_t> info, SocketServer server, size_t cookMax, std::shared_ptr<std::vector<int>> bookOrder, std::shared_ptr<std::mutex> m2_lock);
        static void checkTimeKitchen(std::shared_ptr<std::vector<std::shared_ptr<kitchen_info_t>>> info, std::shared_ptr<std::vector<std::thread>> readKitchen, SocketServer server, std::shared_ptr<std::mutex> m_lock);

    private:
        std::map<std::string, PizzaType> mapType = {
            {"regina", Regina},
            {"margarita", Margarita},
            {"americana", Americana},
            {"fantasia", Fantasia}
        };
        std::map<std::string, PizzaSize> mapSize = {
            {"S", S},
            {"M", M},
            {"L", L},
            {"XL", XL},
            {"XXL", XXL}
        };
        std::shared_ptr<std::vector<std::shared_ptr<kitchen_info_t>>> kitchen_info;
        float cookingTime = 0;
        std::size_t nbCook = 0;
        std::size_t stock = 0;
        SocketServer server;
        size_t nbOrder = 1; 
        size_t idKitchen = 1;
        std::shared_ptr<std::vector<std::thread>> readKitchen;
        std::thread checkCloseKitchen;
        std::shared_ptr<std::mutex> m_lock;
        std::shared_ptr<std::mutex> m2_lock;
        std::shared_ptr<std::vector<int>> bookOrder;
};

#endif /* !__RECEPTION_HPP__ */
