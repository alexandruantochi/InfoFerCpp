#ifndef LOGINCHECKER_H_INCLUDED
#define LOGINCHECKER_H_INCLUDED
#include <string.h>

struct login
{
char username[255];
char password[255];
};

bool checkLogin(login loginDetails);


#endif // LOGINCHECKER_H_INCLUDED
