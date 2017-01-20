#include "clientGUI.h"

void getResultFile(int sd);
void displayResults();
void showResults(std::string line, int flipFlop);

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
void postDelay(int sd, bool ontim)
{

    if (!ontim)
    sendCommand(2,sd);
    else
    sendCommand(3,sd);

    struct delay
    {
        int trainID;
        time_t time;
    } delayInfo;

    std::cout<<std::setw(20)<<std::left<<"ID Tren:";
    std::cin>>delayInfo.trainID;
    if (!ontim)
    {
    std::cout<<std::setw(20)<<std::left<<"Intarziere(min):";
    std::cin>>delayInfo.time;
    }

    if (ontim)
    delayInfo.time=0;


    if (write (sd,&delayInfo,sizeof(delayInfo)) <= 0)
    {
        std::cout<<"Error comunicating with server @ sending command 2"<<std::endl;
        return;
    }
    if (getResponse(sd)==SERVER_OK)
    {
        std::cout<<"Server confirms update.\n";
    }
    else
    {
        std::cout <<"Error, server did not send confirmation.\n";
    }

}

void logout(int sd)
{
    sendCommand(sd,4);

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


    displayResults();

}


void displayResults()
{
//    std::cout<<std::setw(45)<<std::fill('=')<<std::endl;
    std::ifstream input( "./response/train_info");
    std::string delimiter = "%";
    std::string token;

    int i=1;
    for( std::string line; getline( input, line ); )

    {
        showResults(line,i);
        i++;
    }

    if( remove( "./response/train_info" ) != 0 )
    {
        std::cout<<"Error deleting file"<<std::endl;
    }

}



void showResults(std::string line, int lineNo)
{
    std::string delimiter = "%";
    std::string token;
    line = line + delimiter;
    line.erase(0,1);
    std::string columns1[] = {"ID Tren:","Tip:","St.Plecare:","St.Sosire:","Inatarzieri:","Ora Plecare:"};
    std::string columns2[] = {"Distanta(km):","Durata:","Est.Sosire:"};
    if (lineNo%3==1)
    {
        std::cout<<"================================="<<"\n\n";
        while (line.length()>3)
        {
            for (int i=0; i<6; ++i)
            {
                token = line.substr(0, line.find(delimiter));
                line.erase(0, line.find(delimiter) + 1);
                std::cout<<std::setw(20)<<columns1[i]<<token<<std::endl;
            }
        }
    }
    else if (lineNo%3==2)
    {
        std::cout<<std::endl;
        std::cout<<"Traseu: ";
        while (line.length()>3)
        {

            token = line.substr(0, line.find(delimiter));
            line.erase(0, line.find(delimiter) + 1);
            std::cout<<token<<" ";
        }
        std::cout<<"\n";

    }
    else
    {
        while (line.length()>1)
        {
            for (int i=0; i<3; ++i)
            {
                token = line.substr(0, line.find(delimiter));
                line.erase(0, line.find(delimiter) + 1);
                std::cout<<std::setw(20)<<columns2[i]<<token<<std::endl;
            }

        }
        std::cout<<"\n";
    }
}


time_t makeUtime(time_t retTime)
{
    return ((retTime /  100 )* 3600 + (retTime % 100)*60);
}

