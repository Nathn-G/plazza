#ifndef __FORK_HPP__
    #define __FORK_HPP__

    #include "PlazzaNamespace.hpp"
    #include <sys/types.h>
    #include <unistd.h>
    #include "Errors/Fork.hpp"

class Plazza::Fork {
    private:
    int pid = -1;

    public:
    Fork();
    int getPid() const;
};

#endif