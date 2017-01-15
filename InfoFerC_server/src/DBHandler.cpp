#include "DBHandler.h"
#include <iostream>


DBHandler::DBHandler()
{
    std::cout<< "ERROR, db not init."<<std::endl;
}


DBHandler::DBHandler(const char* DBLocation)
{
    database =sqlite3_open(DBLocation, &db);

    if (database)
    {
        std::cout<< "Error initiating database code: "<< database <<std::endl;
        sqlite3_close(db);
        exit(1);
    }
    else
    {
        std::cout<< "Database init at " << DBLocation << " sqlite3_libversion : "<< sqlite3_libversion() << std::endl;
    }
}


void DBHandler::executeQuery(std::string query)
{
    std::cout<< query << std::endl << std::endl;
}

