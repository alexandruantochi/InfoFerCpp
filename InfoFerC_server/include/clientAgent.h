#ifndef CLIENTAGENT_H_INCLUDED
#define CLIENTAGENT_H_INCLUDED

#include <mutex>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <SQLStatement.h>
#include <SQLQueue.h>
#include <SQLgetTrains.h>

#define PORT 8005

typedef struct
{
    pthread_t threadID;
    int threadCount;
} threadInfo;


void startServer();

void threadCreate(int i);

void *treatClient(void* i);

#endif // CLIENTAGENT_H_INCLUDED
