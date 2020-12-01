#include "receiver.h"

extern "C"{
const char* execute(const char* command){
    char *response=new char[10] {'B','a','c','k','e','n','d','\0'};
    return response;
}
}
