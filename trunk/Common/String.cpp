#include "String.h"

String::String() : std::string()
{
}

String::String(const char *str) : std::string(str)
{
}

String::~String()
{
}

String::String(const std::string &ref) : std::string(ref)
{
}

const std::vector<String> *String::split(char delim)
{
    std::vector<String> *vect = new std::vector<String>();
    vect->reserve(countNbWord(delim));
    std::stringstream ss(*this);
    unsigned int i = 0;
    std::string tmp;
    while(std::getline(ss, tmp, delim)) {
        if (!tmp.empty())
            vect->push_back(tmp);
        i++;
    }
    return (vect);
}

String::String(int val)
{
    std::ostringstream oss;
    oss << val;
    (*this) = oss.str();
}

int String::toInt()
{
    std::istringstream iss((*this));
    int nombre;
    iss >> nombre;
    return (nombre);
}

int String::toInt(const std::string &val)
{
    std::istringstream iss(val);
    int nombre;
    iss >> nombre;
    return (nombre);
}

int String::countNbWord(char delim)
{
    unsigned int i = 0;
    unsigned int nbWord = 0;
    std::string *tmp = this;

    while (i < this->size())
    {
        while (i < this->size() && (*tmp)[i] == delim)
            i++;
        if (i < this->size() && (*tmp)[i] != delim)
           nbWord++;
        while (i < this->size() && (*tmp)[i] != delim)
            i++;
    }
    return (nbWord);
}
