#include "DBEngine.h"

sqlite3 *db;
int dbmessages;
char *errors;

void DBEngineInit(const char *location)
{

    dbmessages = sqlite3_open(location, &db);


    if (dbmessages)
    {
        std::cout<< "Error initiating database code: "<< dbmessages << std::endl;
        sqlite3_close(db);
        exit(1);
    }

    else
    {
        std::cout<< "Database init at " << location << " sqlite3_libversion : "<< sqlite3_libversion() << std::endl;
    }
}

void executeQuery(std::string query, int client_id)
{
    std::cout<< query << std::endl << std::endl;
    sqlite3_exec(db, query.c_str(), queryResolver, 0, &errors);

    if (dbmessages)
    {

        std::cout<< "Failed to retrieve info from db." << std::endl  << std::endl;
        std::cout<< "Error:"<< errors << std::endl << std::endl;
        sqlite3_close(db);
    }



}

int queryResolver(void *client_id, int argc, char **argv, char **azColName)
{
    for (int i=0; i< argc; i++)
        printf("%s,\t", argv[i]);
    printf("\n");
    return 0;
}


