#include "Convert.hpp"

namespace Plazza::Error {
    /**
     * @brief Construct a new Convert Error, occurs when trying to convert
     * between types
     * 
     * @param what : the error message
     * @param where : the error location
     */
    Convert::Convert(const std::string &what, const std::string &where)
    : AError(what, where)
    {
    }
}