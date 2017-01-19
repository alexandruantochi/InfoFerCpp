#ifndef CLIENTAGENT_H_INCLUDED
#define CLIENTAGENT_H_INCLUDED

#include <mutex>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <SQLStatement.h>
#include <SQLQueue.h>
#include <SQLgetTrains.h>
#include <SQLpostDelay.h>
#include <SQLpostOntim.h>
#include <loginChecker.h>
#include <sys/sendfile.h>
#include <sys/stat.h>


#define PORT 8007

typedef struct
{
    pthread_t threadID;
    int threadCount; //threadcount not implemented yet
} threadInfo;


void startServer();

void threadCreate(int i);

void *treatClient(void* i);

void getQuery(int client_id, socklen_t connection);

void getUpdate(int client_id, socklen_t connection);

void getOntim(int client_id, socklen_t connection);

void sendResultFile(int client_id, socklen_t connection);

void processClientReq(int client_id, socklen_t connection);


#endif // CLIENTAGENT_H_INCLUDED
