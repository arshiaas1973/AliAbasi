#ifndef ERRORHANDLING_H
#include <iostream>
#include "ErrorType.h"
class ErrorHandling
{
public:
    ErrorHandling(std::string message, int errornum, ErrorType type)
    {
      if(type == ERROR){
          std::cout << "ERR "<< errornum <<": " << message << std::endl;
          exit(errornum);
      }else if (type == WARNING)
      {
          std::cout << "WARNING: " << message << std::endl;
      }

    }

};

#define ERRORHANLING_H
#endif
