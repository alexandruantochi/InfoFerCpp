#include "DBEngine.h"

sqlite3 *db;
int dbmessages;
char *errors;
std::string result;
std::map<std::string,std::string> resultMap;
long durata, distanta;
std::vector<std::map<std::string,std::string>> resultVector (15);

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


    result="";
    durata=0;
    distanta=0;
    resultMap.clear();

    sqlite3_exec(db, query.c_str(), queryResolver, &client_id, &errors);

    if (dbmessages)
    {

        std::cout<< "Failed to retrieve info from db." << std::endl  << std::endl;
        std::cout<< "Error:"<< errors << std::endl << std::endl;
        sqlite3_close(db);
    }
    for (std::map<std::string,std::string>::iterator itt=resultMap.begin(); itt!=resultMap.end(); ++itt)
    {
        std::cout<< itt->first << std::endl << itt->second << std::endl;
    }
    std::cout<< "\n\n CLIENT ID:"<<client_id << std::endl;
    resultVector[client_id]=resultMap;


}




int queryResolver(void *client_id, int argc, char **argv, char **azColName)
{
    if (!resultMap.count(argv[0]))
    {
        result="";
        for (int i=0; i<6;++i)
        {
            result = result + argv[i]+"%";

        }
        result = result + "\n";
        result = result + argv[6] + "%";
        resultMap[argv[0]]=result;

    }
    else
    {
        result=result+argv[6]+"%";
        durata  = durata+ atoi(argv[7]);
        distanta = distanta+ atoi(argv[8]);
        resultMap[argv[0]]=result + "%" + std::to_string(durata) + "%" + std::to_string(distanta);
    }
    return 0;
}

void checkResults()
{
    for (unsigned int i=0; i<resultVector.size(); ++i)
    {
        std::cout<< " ======================= "<<std::endl;
       for (auto it=resultVector[i].begin(); it!=resultVector[i].end(); ++it)
       {
        std::cout<< it->second <<std::endl;
       }
    }
}

