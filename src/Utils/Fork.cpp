#include "Fork.hpp"

namespace Plazza {
    /**
     * @brief Construct a new Fork, the fork is an encapsulation for 
     * fork C function
     */
    Fork::Fork()
    {
        int status = fork();
        
        if (status < 0)
            throw (Plazza::Error::Fork("Error while forking", "Fork::start"));
        this->pid = status;
    }

    /**
     * @brief Get the pid
     * 
     * @return int : the pid
     */
    int Fork::getPid() const
    {
        return (this->pid);
    }
}