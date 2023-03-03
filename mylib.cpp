#include "mylib.h"

int mylib::len(std::string str)
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}

std::vector<std::string> mylib::Split(std::string text, char sep){
    std::vector<std::string> ret;
    int currIndex = 0, i = 0;
    int startIndex = 0, endIndex = 0;
    while (i<=len(text))
    {
        if(text[i]==sep||i==len(text))
        {
            endIndex=i;
            std::string subStr = "";
            subStr.append(text,startIndex,endIndex-startIndex);
            ret.insert(ret.end(),subStr);
            // ret[currIndex] = subStr;
            currIndex+=1;
            startIndex = endIndex+1;
        }
        i++;
    }
    return ret;
}

bool mylib::isNumeric(std::string text){
    std::string numbers = "0123456789";
    bool isnum = false;
    for(auto character : text)
    {
        for(auto num : numbers)
        {
            if(num==character)
                isnum = true;
        }
        if (!isnum)
            return false;
        isnum = false;
    }
    return true;
}
