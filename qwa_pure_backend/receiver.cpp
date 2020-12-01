#include "receiver.h"
#include <string>

extern "C"{
const char* execute(const char* command){
    std::string responseStr="Returned from backend:"+std::string(command);
    char *responseBytes=new char[responseStr.length()+1];
    responseStr.copy(responseBytes,responseStr.length(),0);
    responseBytes[responseStr.length()]='\0';
//    char *responseBytes=new char[10] {'B','a','c','k','e','n','d','\0'};
    return responseBytes;
}
}
