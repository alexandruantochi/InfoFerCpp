#ifndef LOGINCHECKER_H_INCLUDED
#define LOGINCHECKER_H_INCLUDED
#include <string>

struct login
{
std::string username;
std::string password;
};

bool checkLogin(login loginDetails);


#endif // LOGINCHECKER_H_INCLUDED
