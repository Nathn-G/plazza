#include "AError.hpp"

namespace Plazza {
    /**
     * @brief Build a new abstract error
     * 
     * @param what 
     * @param where 
     */
    AError::AError(const std::string &what, const std::string &where)
    {
        this->message = what;
        this->location = where;
    }

    /**
     * @brief Get the error message
     * 
     * @return const char * : the error message
     */
    const char *AError::what() const noexcept
    {
        return (this->message.c_str());
    }

    /**
     * @brief Get the error location
     * 
     * @return const char * : the error location
     */
    const char *AError::where() const noexcept
    {
        return (this->location.c_str());
    }

    /**
     * @brief Print the error message
     * 
     */
    void AError::printError()
    {
        std::cerr << "Error !!!" << std::endl;
        std::cerr << "What : " << this->what() << std::endl;
        std::cerr << "Where : " << this->where() << std::endl;
    }
};