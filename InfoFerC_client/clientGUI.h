#ifndef CLIENTGUI_H_INCLUDED
#define CLIENTGUI_H_INCLUDED


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cstring>

#define SERVER_OK 0

time_t makeUtime(time_t retTime);
int getResponse(int sd);
void executeQuery(int sd);
void postDelay(int sd, bool ontim);
void logout(int sd);
void getResultFile(int sd);
void displayResults();
void showResults(std::string line, int flipFlop);




struct login
{
    char username[255];
    char password[255];
} loginDetails;




#endif // CLIENTGUI_H_INCLUDED
