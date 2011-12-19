#ifndef STRING_COMMON_H__
#define STRING_COMMON_H__

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

class String : public std::string
{
public:
    String();
    String(const char *str);
    String(const std::string &ref);
    String(int val);
    virtual ~String();
    const std::vector<String> *split(char delim);
    int toInt();
    static int toInt(const std::string &);
public:
    int countNbWord(char delim);

};

#endif // STRING_H
