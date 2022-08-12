#include "Chief.hpp"
#include <chrono>
#include <thread>

namespace Plazza::Kitchen {
    Chief::Chief()
    {
        this->pizzaReceipe["margarita"] = {1, {"doe", "tomato", "gruyere"}};
        this->pizzaReceipe["regina"] = {2, {"doe", "tomato", "gruyere", "ham", "mushrooms"}};
        this->pizzaReceipe["americana"] = {2, {"doe", "tomato", "gruyere", "steak"}};
        this->pizzaReceipe["fantasia"] = {4, {"doe", "tomato", "eggplant", "goat cheese", "chief love"}};
    }

    bool Chief::checkIsIngredient(std::vector<std::string> required)
    {
        for (auto item : required) {
            if (this->fridge.at(item) == 0) {
                return false;
            }
        }
        return true;
    }

    int Chief::getNbElement(std::string element)
    {
        return this->fridge.at(element);
    }

    void Chief::Cooking(int iddx, std::shared_ptr<std::size_t> status, SocketClient client)
    {
        Pizza pizza;
        bool canCook = false;
        std::tuple<int, std::vector<std::string>> currentPizza;

        while (*status.get() != 2) {
            canCook = false;
            std::unique_lock<std::mutex> lock(m_lock);
            if (this->m_queue_in.size() == 0) {
                m_data_condition.wait(lock, [this, status]()
                    {
                        return (!this->m_queue_in.empty());
                    }
                );
            }
            if (*status.get() == 2) {
                break;
            }
            pizza = this->m_queue_in.front();
            this->m_queue_in.pop();
            lock.unlock();
            *status = 1;
            while (canCook == false) {
                currentPizza = this->pizzaReceipe[this->mapType[pizza.type]];
                lock.lock();
                if (checkIsIngredient(std::get<1>(currentPizza)) == true)
                    canCook = true;
                if (canCook == true) {
                    for (auto item : std::get<1>(currentPizza)) {
                       this->fridge.at(item) -= 1;
                    }
                }
                lock.unlock();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(std::get<0>(currentPizza) * 1000 * this->xPizza)));
            *status = 0;
            lock.lock();
            this->m_queue_out.push(pizza);
            client.sendSocket(pizza.pack());
            lock.unlock();
        }
    }

    void Chief::push(Pizza pizza)
    {
        std::unique_lock<std::mutex> lock(this->m_lock);

        this->m_queue_in.push(pizza);
        lock.unlock();
        this->m_data_condition.notify_all();
    }

    void Chief::notify()
    {
        this->m_data_condition.notify_all();
    }

    void Chief::refillFridge()
    {
        std::unique_lock<std::mutex> lock(this->m_lock);

        for (auto item : this->fridge) {
            if (this->fridge.at(item.first) < 5)
                this->fridge.at(item.first) += 1;
        }
        lock.unlock();
    }

    int Chief::getSizeQueueIn()
    {
        return this->m_queue_in.size();
    }

    void Chief::setxPizza(float time)
    {
        this->xPizza = time;
    }
} 
