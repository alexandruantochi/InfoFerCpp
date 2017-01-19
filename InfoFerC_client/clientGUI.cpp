#include "clientGUI.h"

void getResultFile(int sd);
displayResults(FILE* trainInfo)

bool loginToServer(int sd)
{


    std::cout<<"username: ";
    std::cin>>loginDetails.username;
    std::cout<<"password: ";
    std::cin>>loginDetails.password;


    if (write (sd,&loginDetails,sizeof(loginDetails)) <= 0)
    {
        std::cout<<"Error comunicating with server @ sending login"<<std::endl;
        return false;
    }


    if (getResponse(sd)!=SERVER_OK)
    {
        std::cout<<"Disconnected from server because of invalid username or password."<<std::endl;
    }
    else
    {
        std::cout<<"Login succesfull."<<std::endl;
        return true;
    }

    return false;
}

int getResponse(int sd)
{
    int serverResponse=-1;

    if (read (sd,&serverResponse,sizeof(int)) <= 0)
    {
        std::cout<<"Error comunicating with server."<<std::endl;
        //return 0;
    }
    return serverResponse;
}

void sendCommand(int command, int sd)
{
   if (write (sd,&command,sizeof(int)) <= 0)
    {
        std::cout<<"Error comunicating with server @ sending command 1"<<std::endl;
        return;
    }
}

void executeQuery(int sd)
{

   struct response
{
    char dep_station[255];
    char arr_station[255];
    time_t dep_time;
    time_t arr_time;
} query ;

    std::cout<<std::setw(20)<<std::left<<"Departure station:";
    std::cin>>query.dep_station;
    std::cout<<std::setw(20)<<std::left<<"Arrival station:";
    std::cin>>query.arr_station;
    std::cout<<std::setw(20)<<std::left<<"Time lower:";
    std::cin>>query.dep_time;
    std::cout<<std::setw(20)<<std::left<<"Time upper:";
    std::cin>>query.arr_time;

    query.dep_time = makeUtime(query.dep_time);
    query.arr_time = makeUtime(query.arr_time);
    sendCommand(1, sd);

    if (write (sd,&query,sizeof(query)) <= 0)
    {
        std::cout<<"Error sending query."<<std::endl;
        return;
    }

    getResultFile(sd);



}
void postDelay(int sd)
{
    int command = 2;

}
void postOntim(int sd)
{
    int command = 3;

}
void logout(int sd)
{
int command = 4;

}

void getResultFile(int sd)
{
    struct stat stat_buf;


    if (read(sd,&stat_buf,sizeof(stat_buf))<0)
    {
    std::cout<<"Error reading file size from server."<<std::endl;
    }



    FILE* trainInfo;
    trainInfo=fopen("./response/train_info", "w+");
    char buffer[2048];


        if (trainInfo == NULL)
        {
                std::cout<<"Failed to open file"<<std::endl;
        }

        long len;

        while ( (stat_buf.st_size > 0)&&((len = recv(sd, buffer,2048, 0)) > 0) )
        {
                fwrite(buffer, sizeof(char), len, trainInfo);
                stat_buf.st_size -= len;
        }
        fclose(trainInfo);


        displayResults(trainInfo);

}


displayResults(FILE* trainInfo)
{



}

time_t makeUtime(time_t retTime)
{
 return ((retTime /  100 )* 3600 + (retTime % 100)*60);
}

