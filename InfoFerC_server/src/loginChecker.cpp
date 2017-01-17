#include "loginChecker.h"

//todo sql query if I have enough time



bool checkLogin(login loginDetails)
{
    return (loginDetails.username =="admin" && loginDetails.password =="root");
}
