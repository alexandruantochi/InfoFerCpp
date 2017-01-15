#include <string>
#include <stdio.h>
#include <SQLStatement.h>
#include <SQLgetTrains.h>
#include <SQLInterface.h>
#include <SQLpostDelay.h>
#include <SQLQueue.h>
#include <DBEngine.h>
#include <list>
#include <iostream>
#include <pthread.h>


extern void dbengineTest();

int main()
{

    const std::string dbLocation = "database/infofercpp.sqlite";



    SQLStatement stmt1("iasi","pascani","10","12","0",0,false);
    SQLStatement stmt2("letcani","suceava","15","13","1",1,false);
    SQLStatement stmt3("podul iloaiei","piatra neamt","09","15","1",3, true);

    SQLQueue sqlQueue;




    sqlQueue.addQuery(new SQLgetTrains(&stmt1));
    sqlQueue.addQuery(new SQLgetTrains(&stmt2));
    sqlQueue.addQuery(new SQLpostDelay(&stmt3));

    sqlQueue.startQuery();
    return 0;
}

