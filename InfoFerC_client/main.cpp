#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <iomanip>


#define PORT 8007
#define SERV_IP "127.0.0.1"
#define SERVER_OK 0
#define SERVER_NOK 9

bool loginToServer(int socketFd);
int getResponse(int sd);
void executeQuery(int sd);
void postDelay(int sd,bool ontim);
void logout(int sd);

int main (int argc, char *argv[])
{
  int sd;
  struct sockaddr_in server;


  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      std::cout<<"Socket error"<<std::endl;
    }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(SERV_IP);
  server.sin_port = htons (PORT);

    if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      std::cout<<"Connection error."<<std::endl;
      return 0;
    }


    if (!loginToServer(sd)) {return 0;}
    bool loggedIn=true;
    int option;

    while (loggedIn)
{
    std::cout<<"Choose your option:"<<std::endl;
    std::cout<<"1 - Get Train Information"<<std::endl;
    std::cout<<"2 - Post Train Delay"<<std::endl;
    std::cout<<"3 - Post Train On Time"<<std::endl;
    std::cout<<"4 - Logout"<<std::endl;
    std::cin >> option;

    switch(option)
    {
    case 1: executeQuery(sd); break;
    case 2: postDelay(sd, false); break;
    case 3: postDelay(sd, true); break;
    case 4: logout(sd); break;
    default: std::cout<<"Invalid option."<<std::endl;
    }
}

//    strncpy(query.dep_station,"Iasi",sizeof("Iasi"));
//    strncpy(query.arr_station,"Suceava",sizeof("Suceava"));
//    query.dep_time=0;
//    query.arr_time=85000;



//
//     if (write (sd,&query,sizeof(query)) <= 0)
//    {
//      perror ("[client]Eroare la write() spre server.\n");
//      return errno;
//    }

  /* citirea raspunsului dat de server
     (apel blocant pina cind serverul raspunde) */

  /* afisam mesajul primit */


  /* inchidem conexiunea, am terminat */
  //close (sd);
}



