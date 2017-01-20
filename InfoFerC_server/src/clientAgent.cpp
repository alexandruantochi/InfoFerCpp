#include <clientAgent.h>
#include <pthread.h>
#include <fileHandler.h>


int SERVER_OK=0;

extern std::vector<FILE*> resultFiles;

threadInfo* threadList = (threadInfo*)calloc(15,sizeof(threadInfo));
int sd;
int threadCount=15;
std::mutex mutexLock;
std::mutex q_mutexLock;
struct sockaddr_in server;
void threadCreate(int);


extern bool checkLogin(login loginDetails);
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
    int client_id = *((int*)(&i));

    std::cout<<"Thread started "<< client_id << std::endl;


    for( ; ; )
    {
        socklen_t length = sizeof (from);
        mutexLock.lock();

        if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0)
        {
            std::cout<<"Client accept error, id="<< client_id<<std::endl;
        }
        else
        {
            std::cout << "Client connected, id="<< client_id << std::endl;

        }
        mutexLock.unlock();
        processClientReq(client_id, client);
        close (client);
    }
};


void processClientReq(int client_id, socklen_t connection)
{
    int command=0; //1-select, 2-postdelay, 3-postontim, 4-logout
    login loginDetails;

    if (read (connection, &loginDetails,sizeof(loginDetails)) <= 0)
    {
        std::cout<<"Login read error."<<std::endl;
    }



    if (!checkLogin(loginDetails))
    {
        std::cout<<"Client " << client_id << " disconnected for bad credentials."<<std::endl;
        return;
    }
    else
    {
        std::cout<<"Client logged in."<<std::endl;
    }

    if (write (connection,&SERVER_OK,sizeof(int)) <= 0)
    {
        std::cout<<"Error sending OK to client."<<std::endl;
    }
    command=0;

    while(command!=4)
    {

        if (read (connection, &command,sizeof(int)) <= 0)
        {
            std::cout<<"Command read error."<<std::endl;
            return;
        }
        std::cout<<"Read command "<<command<< " from client no. "<<client_id<<"\n";
        switch(command)
        {
        case 1:
            getQuery(client_id, connection);
            break;
        case 2:
            getUpdate(client_id, connection);
            break;
        case 3:
            getOntim(client_id, connection);
            break;
        case 4:
            logoutClient(client_id,connection);
            break;
        default:
            close(client_id);
            break;
        }
    }



}


void getQuery(int client_id, socklen_t connection)
{


    struct response
    {
        char dep_station[255];
        char arr_station[255];
        time_t dep_time;
        time_t arr_time;
    } query ;


    if ((read (connection, &query,sizeof(query))) <= 0)
    {
        std::cout<<"Error while reading command query"<<std::endl;
    }



    SQLStatement stmt(std::string(query.dep_station),
                      std::string(query.arr_station),
                      std::to_string(query.dep_time),
                      std::to_string(query.arr_time), client_id);

    q_mutexLock.lock();
    SQLQueue::addQuery(new SQLgetTrains(&stmt));
    q_mutexLock.unlock();
    sleep(1);
    q_mutexLock.lock();
    SQLQueue::startQuery();
    q_mutexLock.unlock();

    sendResultFile(client_id, connection);

}


void getUpdate(int client_id,socklen_t connection)
{

    struct delay
    {
        int trainID;
        time_t time;
    } delayInfo;


    if ((read (connection, &delayInfo,sizeof(delayInfo))) <= 0)
    {
        std::cout<<"Error while reading command postDelay."<<std::endl;
    }

    SQLStatement stmt(delayInfo.time,delayInfo.trainID, true);
    q_mutexLock.lock();
    SQLQueue::addQuery(new SQLpostDelay(&stmt));
    q_mutexLock.unlock();
    sleep(1);
    q_mutexLock.lock();
    SQLQueue::startQuery();
    q_mutexLock.unlock();

    if (write (connection,&SERVER_OK,sizeof(int)) <= 0)
    {
        std::cout<<"Error sending OK to client."<<std::endl;
    }


}
void getOntim(int client_id, socklen_t connection)
{

    struct delay
    {
        int trainID;
        time_t time;
    } delayInfo;


    if ((read (connection, &delayInfo,sizeof(delayInfo))) <= 0)
    {
        std::cout<<"Error while reading command postOntim."<<std::endl;
    }

    SQLStatement stmt(delayInfo.time,delayInfo.trainID, true);
    q_mutexLock.lock();
    SQLQueue::addQuery(new SQLpostOntim(&stmt));
    q_mutexLock.unlock();
    sleep(1);
    q_mutexLock.lock();
    SQLQueue::startQuery();
    q_mutexLock.unlock();

    if (write (connection,&SERVER_OK,sizeof(int)) <= 0)
    {
        std::cout<<"Error sending OK to client."<<std::endl;
    }


}

void logoutClient(int client_id, socklen_t connection)
{
    if (write (connection,&SERVER_OK,sizeof(int)) <= 0)
    {
        std::cout<<"Error sending OK to client."<<std::endl;
    }

    close(connection);
}


void sendResultFile(int client_id, socklen_t connection)
{

    struct stat stat_buf;
    off_t offset = 0;

    fstat(fileno(resultFiles[client_id]), &stat_buf);

    write(connection,&stat_buf,sizeof(stat_buf));

    if ((sendfile (connection, fileno(resultFiles[client_id]), &offset, stat_buf.st_size)) < 0)
    {
        std::cout<<"Error sending file to client "<<client_id<<std::endl;
    }

    std::cout<<"File sent."<<std::endl;

}

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
