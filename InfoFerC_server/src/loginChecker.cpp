#include "loginChecker.h"

#include <iostream>
//todo sql query if I have enough time
//to be extended


bool checkLogin(login loginDetails)
{
    return (strcmp(loginDetails.username,"admin") ==0 && strcmp(loginDetails.password,"root")==0);
}
