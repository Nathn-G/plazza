#ifndef __ERROR_CONVERT_HPP__
    #define __ERROR_CONVERT_HPP__

    #include "PlazzaNamespace.hpp"
    #include "Utils/AError.hpp"

class Plazza::Error::Convert : public Plazza::AError {
    public:
    Convert(const std::string &what = "Conversion error", const std::string &where = "Unknown");
};

#endif