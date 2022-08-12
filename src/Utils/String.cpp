#include "String.hpp"

/**
 * @brief String utility class that can be used to call more easily string function
 * and utils
 * 
 */
namespace Utils {

    /**
     * @brief Construct a new String:: String object
     * 
     * @param str : the string to be used, default ""
     */
    String::String(std::string str) {
        this->str = str;
    }

    /**
     * @brief Check if the string is a float,
     * this is a static function so it can be called without instancing the class
     * 
     * @param str : the string to be checked
     * @return bool : true if the string is a float, false otherwise
     */
    bool String::isFloat(std::string str)
    {
        std::istringstream iss(str);
        float f;

        iss >> std::noskipws >> f;
        return (iss.eof() && !iss.fail()); 
    }

    /**
     * @brief Check if the string is a float,
     * 
     * @return bool : true if the string is a float, false otherwise
     */
    bool String::isFloat()
    {
        return (this->isFloat(this->str));
    }

    /**
     * @brief Check if the string is an int,
     * this is a static function so it can be called without instancing the class
     * 
     * @param str : the string to be checked
     * @return bool : true if the string is an int, false otherwise
     */
    bool String::isInt(std::string str)
    {
        std::istringstream iss(str);
        int n;

        iss >> std::noskipws >> n;
        return (iss.eof() && !iss.fail()); 
    }

    /**
     * @brief Check if the string is an int,
     * 
     * @return bool : true if the string is an int, false otherwise
     *
     */
    bool String::isInt()
    {
        return (this->isInt(this->str));
    }

    /**
     * @brief Get the string object
     * 
     * @param str : the string to be used
     * @param delim : the delimiter to be used
     * @return std::vector<std::string> : the vector of string
     */
    std::vector<std::string> String::split(std::string str, char delim)
    {
        std::vector<std::string> array;
        size_t end = 0;
        size_t start = str.find_first_not_of(delim, end);

        while (start != std::string::npos) {
            end = str.find(delim, start);
            array.push_back(str.substr(start, end - start));
            start = str.find_first_not_of(delim, end);
        }
        return array;
    }

    /**
     * @brief : split the string with a delimiter
     * 
     * @param str : the string to be used
     * @param delim : the delimiter to be used
     * @return std::vector<std::string> : the vector of string
     */
    std::vector<std::string> String::splitSep(std::string str, char delim)
    {
        std::vector<std::string> array;
        std::string token;
        std::stringstream ss(str);

        while (getline(ss, token, delim)){
            trim(token);
            array.push_back(token);
        }
        return array;
    }

    /**
     * @brief : trim the string to the left
     * 
     * @param s : the string to be used
     */
    void String::ltrim(std::string &s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }

    /**
     * @brief : trim the string to the right
     * 
     * @param s : the string to be used
     */
    void String::rtrim(std::string &s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    /**
     * @brief : trim the string to the left and right
     * 
     * @param s : the string to be used
     */
    void String::trim(std::string &s)
    {
        ltrim(s);
        rtrim(s);
    }
}