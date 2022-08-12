#ifndef __FORK_ERROR_HPP__
    #define __FORK_ERROR_HPP__

    #include "AError.hpp"

class Plazza::Error::Fork : public Plazza::AError {
    public:
    Fork(std::string what = "Error while forking", std::string where = "Unknown");
};

#endif