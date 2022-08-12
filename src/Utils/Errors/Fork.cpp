#include "Fork.hpp"

namespace Plazza::Error {
    /**
     * @brief Construct a new Fork Error, this error occurs when fork return -1
     * 
     * @param what : the error message
     * @param where : the error location
     */
    Fork::Fork(std::string what, std::string where)
    : AError(what, where)
    {
    }
}