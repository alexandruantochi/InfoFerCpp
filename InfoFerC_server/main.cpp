#include <string>
#include <stdio.h>
#include <SQLStatement.h>
#include <SQLgetTrains.h>
#include <SQLInterface.h>
#include <SQLpostDelay.h>
#include <SQLQueue.h>
#include <DBEngine.h>
#include <fileHandler.h>
#include <list>
#include <iostream>
#include <pthread.h>

extern void DBEngineInit(char* dbLocation);
extern void checkResults();
extern std::vector<FILE*> resultFiles;
void testServer();

void clear(int lines)
{
    if (lines<1)
    {
        std::cout<<"Invalid lines to clear"<<std::endl;
        return;
    }
    for (int i=0; i<lines; ++i)
    {
        std::cout<<std::endl;
    }

}

int main()
{
    const std::string dbLocation = "database/infofercpp.sqlite";
    DBEngineInit(dbLocation.c_str());






    return 0;
}

void testServer()
{
    SQLStatement stmt1("Iasi","Pascani","10","85000","0",0,false);
    SQLStatement stmt2("Pascani","Suceava","15","85000","1",1,false);
    SQLStatement stmt3("podul iloaiei","piatra neamt","09","85000","1",3, true);

    SQLQueue sqlQueue;



    sqlQueue.addQuery(new SQLgetTrains(&stmt1));
    sqlQueue.addQuery(new SQLgetTrains(&stmt2));
    //sqlQueue.addQuery(new SQLpostDelay(&stmt3));

    sqlQueue.startQuery();

    clear(4);

    std::cout<<resultFiles[1]<<std::endl;

}
