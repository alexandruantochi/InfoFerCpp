
#include <sqlite3.h>
#include <string>
#include <stdio.h>
#include <SQLStatement.h>
#include <SQLgetTrains.h>
#include <SQLInterface.h>
#include <SQLpostDelay.h>
#include <SQLQueue.h>
#include <list>
#include<iostream>


int main()
{

    SQLStatement stmt1("iasi","pascani","10","12","0",0,false);
    SQLStatement stmt2("letcani","suceava","15","13","1",1,false);
    SQLStatement stmt3("pascani","suceava","20","22","0",2, true);
    SQLStatement stmt4("podul iloaiei","piatra neamt","09","15","1",3, true);

    SQLQueue sqlQueue;

    std::cout << &stmt1 << std::endl;
    std::cout << &stmt2 << std::endl;
    std::cout << &stmt3 << std::endl;
    std::cout << &stmt4 << std::endl;

    sqlQueue.addQuery(new SQLgetTrains(&stmt1));
    sqlQueue.addQuery(new SQLgetTrains(&stmt2));
    sqlQueue.addQuery(new SQLpostDelay(&stmt3));

    sqlQueue.startQuery();

    sqlite3 *db;

    std::string empty_str;



    return 0;
}
