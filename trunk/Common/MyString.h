#ifndef STRING_COMMON_H__
#define STRING_COMMON_H__

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "SystemDefines.h"

class String : public std::string
{
public:
    String();
    String(const char *str);
    String(const std::string &ref);
    String(int val);
    virtual ~String();
    const std::vector<String> *split(char delim) const;
    int toInt() const;
    int countNbWord(char delim) const;
    static int toInt(const std::string &);
    static String toString(int nb);
    static String byteToString(UInt8 nb);

private:
    std::string _tmptmp;
};

#endif // STRING_H
