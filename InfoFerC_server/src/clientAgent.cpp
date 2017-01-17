#include <clientAgent.h>
#include <pthread.h>

threadInfo* threadList = (threadInfo*)calloc(15,sizeof(threadInfo));
int sd;
int threadCount=15;
std::mutex mutexLock;
struct sockaddr_in server;
void threadCreate(int);


extern void testServer();

void startServer()
{
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout<<"Socket error!"<<std::endl;
        return;
    }

    int on=1;
    setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));


    bzero (&server, sizeof (server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    server.sin_port = htons (PORT);


    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
        std::cout<<"Bind error!"<<std::endl;
        return;
    }

    if (listen (sd, 2) == -1)
    {
        std::cout<<"Listen error!"<<std::endl;
    }


    for(int i=0; i<threadCount; ++i)
        threadCreate(i);

    std::cout<<"startServer job done."<<std::endl;

    pause();
};



void threadCreate(int i)
{
    void *treat(void *);

    pthread_create(&threadList[i].threadID,NULL,&treatClient,(void*)i);
    return;
}

void *treatClient(void* i)
{
    socklen_t client;

    struct sockaddr_in from;
    bzero (&from, sizeof (from));


    std::cout<<"Thread started "<< *((int*)(&i)) << std::endl;

    if (*((int*)(&i)) == 5)
    testServer();

    for( ; ; )
    {
       socklen_t length = sizeof (from);
        mutexLock.lock();

        if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0)
        {
            std::cout<<"Client accept error, id="<< *((int*)(&i))<<std::endl;
        }

        mutexLock.unlock();
        threadList[*((int*)(&i))].threadCount++;

        close (client);
    }
};


//void raspunde(int cl,int idThread)
//{
//    int nr;		//mesajul primit de trimis la client
//
//    if (read (cl, &nr,sizeof(int)) <= 0)
//    {
//        printf("[Thread %d]\n",idThread);
//        perror ("Eroare la read() de la client.\n");
//
//    }
//
//    printf ("[Thread %d]Mesajul a fost receptionat...%d\n",idThread, nr);
//
//    /*pregatim mesajul de raspuns */
//    nr++;
//    printf("[Thread %d]Trimitem mesajul inapoi...%d\n",idThread, nr);
//
//
//    /* returnam mesajul clientului */
//    if (write (cl, &nr, sizeof(int)) <= 0)
//    {
//        printf("[Thread %d] ",idThread);
//        perror ("[Thread]Eroare la write() catre client.\n");
//    }
//    else
//        printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",idThread);
//
//}
