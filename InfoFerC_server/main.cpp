
#include <sqlite3.h>
#include <string>
#include <stdio.h>
#include <SQLStatement.h>
#include <SQLgetTrains.h>
#include <SQLInterface.h>
#include <SQLpostDelay.h>
#include <list>
#include<iostream>


int main()
{

    SQLStatement stmt1("iasi","pascani","10","12","0",0);
    SQLStatement stmt2("letcani","suceava","15","13","1",1);

    SQLgetTrains get1(&stmt1);
    SQLgetTrains get2(&stmt2);
    SQLpostDelay post1(&stmt1);
    SQLpostDelay post2(&stmt2);

    get1.execute();
    get2.execute();
    post1.execute();
    post2.execute();

    std::list<SQLInterface*> stmt_list;

    stmt_list.push_back(&get1);
    stmt_list.push_back(&get2);

    for (std::list<SQLInterface*>::iterator it=stmt_list.begin(); it!=stmt_list.end(); ++it)
    {
        (*it)->execute();
    }

    sqlite3 *db;

    std::string empty_str;



    return 0;
}
