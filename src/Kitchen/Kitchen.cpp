#include "Kitchen.hpp"

Plazza::Kitchen::Chief pool;
Status status;

namespace Plazza::Kitchen {

    /**
     * @brief Construct a new Kitchen, the kitchen is a forked class that 
     * contains Cooks
     * 
     * @param nbCooks : the number of cooks 
     */
    Kitchen::Kitchen(float xPizza, std::size_t nbCooks, std::size_t xIngredient)
    {
        this->nbCooks = nbCooks;
        this->xPizza = xPizza;
        this->xIngredient = xIngredient;
        this->active = std::make_shared<bool>(true);
        pool.setxPizza(this->xPizza);
        this->createChiefs();
    }

    Kitchen::~Kitchen()
    {
        for (std::size_t i = 0; i < nbCooks; i++) {
            this->chiefs_t[i].join();
        }
        this->loopRefillFridge.join();
    }

    void Kitchen::createChiefs()
    {
        for (std::size_t i = 0; i < nbCooks; i++) {
            this->chiefs_status.push_back(std::make_shared<std::size_t>(0));
            this->chiefs_t.push_back(std::thread(&Plazza::Kitchen::Chief::Cooking, &pool, i, this->chiefs_status[i], this->client));
        }
    }

    /**
     * @brief run loop of Kitchen
     * 
     */
    void Kitchen::run()
    {
        this->loopRefillFridge = std::thread(this->refillFridge, this->xIngredient, this->active);
        this->loopReadReception();
        // this->readReception = std::thread(this->loopReadReception, this->client, this->nbCooks, this->chiefs_status);
    }
    
    void Kitchen::loopReadReception()
    {
        std::string response;
        std::vector<std::string> messages;

        while (*this->active.get()) {
            response = this->client.readSocket();
            if (response.compare("exit") == 0) {
                *this->active = false;
                this->client.closeClient();
            } else if (response.compare("status") == 0) {
                status.waitingPizza = pool.getSizeQueueIn();
                status.cookStatus.clear();
                for (int i = 0; i < this->nbCooks; i++) {
                    status.cookStatus.push_back(*this->chiefs_status[i].get());
                }
                status.elements = {
                    {"doe", pool.getNbElement("doe")},
                    {"tomato", pool.getNbElement("tomato")},
                    {"gruyere", pool.getNbElement("gruyere")},
                    {"ham", pool.getNbElement("ham")},
                    {"mushrooms", pool.getNbElement("mushrooms")},
                    {"steak", pool.getNbElement("steak")},
                    {"eggplant", pool.getNbElement("eggplant")},
                    {"goat cheese", pool.getNbElement("goat cheese")},
                    {"chief love", pool.getNbElement("chief love")}
                };
                client.sendSocket(status.pack());
            } else if (response.compare(0, 5, "pizza") == 0) {
                messages = Utils::String::split(response, '\n');
                int i = 0;
                for (std::string message : messages) {
                    if (message.compare(0, 6, "pizza ") == 0) {
                        do_order_message(message);
                    }
                    i++;
                }
            }
        }
        for (std::size_t i = 0; i < nbCooks; i++) {
            *this->chiefs_status[i] = 2;
        }
        pool.notify();
    }

    void Kitchen::do_order_message(std::string message)
    {
        Pizza pizza;

        pizza.unpack(message);
        pool.push(pizza);
    }

    /**
     * @brief Get the number of cooks
     * 
     * @return std::size_t : the number of cooks
     */
    std::size_t Kitchen::getNbCooks() const
    {
        return (this->nbCooks);
    }

    void Kitchen::addToQueue(Pizza value)
    {
        pool.push(value);
    }

    void Kitchen::refillFridge(std::size_t time, std::shared_ptr<bool> active)
    {
        while (*active.get())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
            pool.refillFridge();
        }
    }
}