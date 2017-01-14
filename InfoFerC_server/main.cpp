#include <iostream>
#include <sqlite3.h>
#include <string>
#include <stdio.h>
#include <SQLStatement.h>

using namespace std;

int main()
{



    sqlite3 *db;

    SQLStatement test1("Iasi","Pascani","5","200","0",0);

    string banana;

    SQLStatement test2(banana,banana,banana,banana,banana,1, true);

    test1.getTrains();
    test1.postDelay();
    test1.postOntim();

    test2.getTrains();
    test2.postDelay();
    test2.postOntim();

    if (test2.hasPriority)
    {
    cout<< "Priority";
    }


    return 0;
}
