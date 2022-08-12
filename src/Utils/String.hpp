#ifndef __STRING_HPP__
    #define __STRING_HPP__

    #include "UtilsNamespace.hpp"

    #include <string>
    #include <sstream>
    #include <vector>
    #include <algorithm> 

class Utils::String {
    private:
    std::string str;

    public:
    String(std::string str = "");
    bool isInt();
    bool isFloat();
    // Static function that can be called without instancing the class
    static bool isInt(std::string str);
    static bool isFloat(std::string str);
    static std::vector<std::string> split(std::string str, char delim);
    static std::vector<std::string> splitSep(std::string str, char delim);
    static void ltrim(std::string &s);
    static void rtrim(std::string &s);
    static void trim(std::string &s);
};

#endif