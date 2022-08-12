/*
** EPITECH PROJECT, 2022
** Reception
** File description:
** methods of class Reception
*/

#include "Reception/Reception.hpp"
#include <sys/wait.h>
#include <fstream>

std::vector<Status> statusResponse;
std::map<Plazza::PizzaType, std::string> mapTypeInvGlob = {
    {Plazza::PizzaType::Regina, "regina"},
    {Plazza::PizzaType::Margarita, "margarita"},
    {Plazza::PizzaType::Americana, "americana"},
    {Plazza::PizzaType::Fantasia, "fantasia"}
};

std::map<Plazza::PizzaSize, std::string> mapSizeGlob = {
    {Plazza::PizzaSize::S, "S"},
    {Plazza::PizzaSize::M, "M"},
    {Plazza::PizzaSize::L, "L"},
    {Plazza::PizzaSize::XL, "XL"},
    {Plazza::PizzaSize::XXL, "XXL"}
};

namespace Plazza {

    Reception::Reception()
    {
        std::fstream f("log.txt", std::fstream::trunc);
        if (!f.is_open())
            std::ofstream {"log.txt"};
        this->readKitchen = std::make_shared<std::vector<std::thread>>();
        this->kitchen_info = std::make_shared<std::vector<std::shared_ptr<kitchen_info_t>>>();
        this->m_lock = std::make_shared<std::mutex>();
        this->m2_lock = std::make_shared<std::mutex>();
        this->bookOrder = std::make_shared<std::vector<int>>();
    }

    Reception::~Reception()
    {
        for (int i = 0; i < this->readKitchen.get()->size(); i++) {
            (*this->readKitchen.get())[i].join();
        }
        if (this->checkCloseKitchen.joinable())
            this->checkCloseKitchen.join();
        this->server.closeServer();
    }

    /**
     * @brief Construct a new Reception::Reception object
     * Initialize the cooking time, the number of cooks and the stock
     * 
     * @param strTime : the cooking time
     * @param strCook : the number of cooks
     * @param strStock : the stock
     * @return int : 0 if the initialization is successful, 84 otherwise
     */
    int Reception::init(std::string strTime, std::string strCook, std::string strStock)
    {
        try {
            this->cookingTime = std::stof(strTime);
            this->nbCook = std::stoi(strCook);
            this->stock = std::stoi(strStock);
        } catch (__attribute__((unused))std::exception &err) {
            throw Plazza::Error::Convert("Error while converting string to float/int", "Reception::init");
        }
        if (this->cookingTime < 0 || this->nbCook <= 0)
            throw Plazza::Error::Convert("Error bad arguments values", "Reception::init");
        return (0);
    }

    /**
     * @brief Create nb kitchens in subprocess
     * 
     * @param nb : the number of kitchens to create
     */
    bool Reception::createKitchen(std::size_t nb)
    {
        for (std::size_t i = 0; i < nb; i++) {
            Fork fork;

            if (fork.getPid() == 0) {
                Plazza::Kitchen::Kitchen kitchen(this->cookingTime, this->nbCook, this->stock);
                kitchen.run();
                kitchen.~Kitchen();
                std::exit(0);
            } else {
                std::unique_lock<std::mutex> lock(*this->m_lock.get());
                std::shared_ptr<kitchen_info_t> info = std::make_shared<kitchen_info_t>();
                info->fd = this->server.acceptNewClient();
                info->nbPizza = 0;
                info->id = this->idKitchen;
                info->running = true;
                this->kitchen_info->push_back(info);
                this->idKitchen++;
                this->readKitchen.get()->push_back(std::thread(this->receiveKitchenStatus, info, this->server, this->nbCook, this->bookOrder, this->m2_lock));
                std::fstream f("log.txt", std::fstream::app);
                f << "New kitchen : " << info->id << " created\n";
                f.close();
                lock.unlock();
            }
        }
        return (true);
    }

    /**
     * @brief Run the reception
     * 
     */
    void Reception::run()
    {
        std::string line;
        std::cout << "> ";

        this->checkCloseKitchen = std::thread(this->checkTimeKitchen, this->kitchen_info, this->readKitchen, this->server, this->m_lock);
        while (std::getline(std::cin, line)) {
            handleLineShell(line);
            std::cout << "> ";
        }
    }

    /**
     * @brief : handle the line from the shell
     * 
     * @param line : the line from the shell
     */
    void Reception::handleLineShell(std::string line)
    {
        if (line.compare("status") == 0) {
            handleStatus();
        } else {
            handlePizza(line);
        }
    }

    // bool sortStatusById

    /**
     * @brief : handle the status
     * 
     */
    void Reception::handleStatus()
    {
        std::unique_lock<std::mutex> lock(*this->m_lock.get());
        for (std::shared_ptr<kitchen_info_t> info : (*this->kitchen_info.get())) {
            this->server.sendSocket(info->fd, "status");
        }
        lock.unlock();
        lock.lock();
        std::unique_lock<std::mutex> lock2(*this->m2_lock.get());
        while (statusResponse.size() < this->kitchen_info->size()) {
            lock2.unlock();
            lock.unlock();
            lock2.lock();
            lock.lock();
        }
        lock2.unlock();
        lock.unlock();
        lock2.lock();
        lock.lock();
        std::sort(statusResponse.begin(), statusResponse.end());
        std::cout << "********** STATUS ************" << std::endl;
        if (this->kitchen_info->size() == 0)
            std::cout << "no kitchen are currently running" << std::endl;
        for (Status status : statusResponse) {
            std::cout << "--------- KITCHEN " << status.kitchenId << " ----------" << std::endl;
            std::cout << "Waiting pizza : " << status.waitingPizza << std::endl;
            for (size_t i = 0; i < status.cookStatus.size(); i++) {
                std::cout << "Cook " << i << " : ";
                if (status.cookStatus[i] == 0)
                    std::cout << "Free" << std::endl;
                else
                    std::cout << "Cooking Pizza" << std::endl;
            }
            std::cout << "INGREDIENTS" << std::endl;
            std::cout << "doe : " << status.elements["doe"] << std::endl;
            std::cout << "tomato : " << status.elements["tomato"] << std::endl;
            std::cout << "gruyere : " << status.elements["gruyere"] << std::endl;
            std::cout << "ham : " << status.elements["ham"] << std::endl;
            std::cout << "mushrooms : " << status.elements["mushrooms"] << std::endl;
            std::cout << "steak : " << status.elements["steak"] << std::endl;
            std::cout << "eggplant : " << status.elements["eggplant"] << std::endl;
            std::cout << "goat cheese : " << status.elements["goat cheese"] << std::endl;
            std::cout << "chief love : " << status.elements["chief love"] << std::endl;
        }
        statusResponse.clear();
        lock2.unlock();
        lock.unlock();
    }

    /**
     * @brief : handle the pizza
     * 
     * @param line : the pizza
     */
    void Reception::handlePizza(std::string line)
    {
        line = line + " ";
        std::vector<std::string> list = Utils::String::splitSep(line, ';');
        std::vector<Pizza> listPizza;
    
        for (std::string str : list) {
            std::vector<std::string> command = Utils::String::split(str, ' ');
            if (command.size() != 3 || !checkPizzaType(command[0]) ||
            !checkPizzaSize(command[1]) || !checkPizzaQuantity(command[2])) {
                std::cout << "Input : Invalid Syntax" << std::endl;
                return;
            }
            Pizza pizza;
            pizza.type = this->mapType[command[0]];
            pizza.size = this->mapSize[command[1]];
            pizza.order = this->nbOrder;
            int quantity = std::stoi(command[2].substr(1, command[2].length() - 1));
            for (int i = 0; i < quantity; i++)
                listPizza.push_back(pizza);
        }
        if (this->kitchen_info->size() == 0) {
            this->createKitchen(1);
        }
        this->sendPizzaToKitchen(listPizza);
    }

    bool Reception::compareKitchen(std::shared_ptr<kitchen_info_t> k1, std::shared_ptr<kitchen_info_t> k2)
    {
        return (k1->nbPizza < k2->nbPizza);
    }

    bool Reception::isFullKitchen(std::shared_ptr<kitchen_info_t> kitchen)
    {
        return (kitchen->nbPizza >= this->nbCook * 2);
    }

    void Reception::sendPizzaToKitchen(std::vector<Pizza> list)
    {
        std::string message = "";
        size_t index = 0;
        size_t ipizza = 0;

        this->bookOrder->push_back(list.size());
        for (Pizza pizza : list) {
            ipizza++;

            std::unique_lock<std::mutex> lock(*this->m_lock.get());
            std::sort(this->kitchen_info->begin(), this->kitchen_info->end(), compareKitchen);
            message = pizza.pack();
            while (index < this->kitchen_info->size() && isFullKitchen((*this->kitchen_info.get())[index]))
                index++;
            if (index >= this->kitchen_info->size()) {
                lock.unlock();
                this->createKitchen(1);
                lock.lock();
            }
            if (index < this->kitchen_info->size()) {
                this->server.sendSocket((*this->kitchen_info.get())[index]->fd, message);
                (*this->kitchen_info.get())[index]->nbPizza += 1;
                std::fstream f("log.txt", std::fstream::app);

                f << "Order " << pizza.order << ": Send " << mapTypeInvGlob[pizza.type]
                << " " << mapSizeGlob[pizza.size] << " sent to kitchen "
                << (*this->kitchen_info.get())[index]->id << "\n";
                f.close();
            }
            lock.unlock();
            if (ipizza == 20) {
                ipizza = 0;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            index = 0;
        }
        this->nbOrder++;
    }

    /**
     * @brief : check if the string is a type of pizza
     * 
     * @param str : the string
     * @return bool : return true is the string match with a type of pizza otherwise false
     */
    bool Reception::checkPizzaType(std::string str)
    {
        if (this->mapType.find(str) == this->mapType.end())
            return false;
        return true;
    }

    /**
     * @brief : check if the string is a size of pizza
     * 
     * @param str : the string
     * @return bool : return true is the string match with a size of pizza otherwise false
     */
    bool Reception::checkPizzaSize(std::string str)
    {
        if (this->mapSize.find(str) == this->mapSize.end())
            return false;
        return true;
    }

    /**
     * @brief : check if the string is a quantity of pizza
     * 
     * @param str : the string
     * @return bool : return true is the string match with a quantity of pizza otherwise false
     */
    bool Reception::checkPizzaQuantity(std::string str)
    {
        if (str.at(0) != 'x')
            return false;
        if (!Utils::String::isInt(str.substr(1, str.length() - 1)))
            return false;
        return true;
    }

    void Reception::receiveKitchenStatus(std::shared_ptr<kitchen_info_t> info, SocketServer server, size_t cookMax, std::shared_ptr<std::vector<int>> bookOrder, std::shared_ptr<std::mutex> m2_lock)
    {
        std::string message;
        Pizza pizza;

        while (true) {
            message = server.readSocket(info->fd);
            if (info->running == false) {
                break;
            }
            if (message.compare(0, 6, "status") == 0) {
                std::vector<std::string>messages = Utils::String::split(message, '\n');
                std::unique_lock<std::mutex> lock2(*m2_lock.get());

                for (std::string line : messages) {
                    Status status;
                    status.unpack(line, cookMax);
                    status.kitchenId = info->id;
                    statusResponse.push_back(status);
                }
                lock2.unlock();
            } else if (message.compare(0, 5, "pizza") == 0) {
                std::vector<std::string>messages = Utils::String::split(message, '\n');
                std::fstream f("log.txt", std::fstream::app);

                for (std::string line : messages) {
                    pizza.unpack(line);
                    f << "Order " << pizza.order << " : ";
                    f << mapTypeInvGlob[pizza.type] << " ";
                    f << mapSizeGlob[pizza.size] << " ";
                    f << "cooked from Kitchen : " << info.get()->id << "\n";
                    info->nbPizza--;
                    (*bookOrder.get())[pizza.order - 1] -= 1;
                    if ((*bookOrder.get())[pizza.order - 1] == 0) {
                        f << "Order " << pizza.order << " : ";
                        f << "all pizza are cooked !\n";
                    }
                }
                f.close();
            }
        }
    }

    void Reception::checkTimeKitchen(std::shared_ptr<std::vector<std::shared_ptr<kitchen_info_t>>> info, std::shared_ptr<std::vector<std::thread>> readKitchen, SocketServer server, std::shared_ptr<std::mutex> m_lock)
    {
        int64_t now = 0;

        while (true) {
            now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            std::unique_lock<std::mutex> lock(*m_lock.get());

            for (int i = 0; i < info->size(); i++) {
                if ((*info.get())[i].get()->nbPizza != 0) {
                    (*info.get())[i].get()->time = now;
                } else if ((*info.get())[i].get()->time != 0 && (now - (*info.get())[i].get()->time) > 5000) {
                    server.sendSocket((*info.get())[i].get()->fd, "exit");
                    (*info.get())[i].get()->running = false;
                    std::fstream f("log.txt", std::fstream::app);
                    f << "Kitchen : " << (*info.get())[i].get()->id << " deleted\n";
                    f.close();
                    info->erase(info->begin() + i);
                    i--;
                }
            }
            lock.unlock();
        }
    }
}