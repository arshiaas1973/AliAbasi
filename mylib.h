#ifndef MYLIB_H
#include <iostream>
#include <vector>
class mylib
{
private:
    static int len(std::string str);
public:
    static std::vector<std::string> Split(std::string text, char sep);
    static bool isNumeric(std::string text);
};

#define MYLIB_H
#endif // !MYLIB_H
