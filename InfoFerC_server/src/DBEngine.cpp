#include "DBEngine.h"

extern void clear(int lines);
extern int fileGenerator(int client_id,std::map<std::string,std::string>);
void resetResults(bool map);
std::string makeTime(time_t uTime);

sqlite3 *db;
int dbmessages;
char *errors;
std::string result;
std::map<std::string,std::string> resultMap;
time_t durata, durataT, delay;
int distanta,counter;
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
    int fileGenerated;

    resetResults(true);

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

    resultVector[client_id]=resultMap;

    fileGenerated = fileGenerator(client_id, resultMap);

    if (!fileGenerated)
    {
        std::cout<<"File generator error!" << std::endl;
    }
    else
    {
        std::cout<<"File generated for client "<<client_id << std::endl;
    }

    clear(2);
}




int queryResolver(void *client_id, int argc, char **argv, char **azColName)
{
    if (!resultMap.count(argv[0]))
    {
        resetResults();

        for (int i=0; i<4; ++i)
        {
            result = result +"%"+ argv[i];
        }
        delay = atoi(argv[4]);
        result = result + "%" + makeTime(delay);
        result = result + "%" + makeTime(durataT=atoi(argv[5]));
        result = result + "\n";
        result = result +  "%" + argv[6];
        resultMap[argv[0]]=result;
    }
    else
    {
        result=result+"%"+argv[6];
        durata  = durata + atoi(argv[7]);
        counter++;
        distanta = distanta + atoi(argv[8]);
        resultMap[argv[0]]=result + "%" + std::to_string(distanta) + "%" + makeTime(durata) +  "%" + makeTime(durataT+durata+delay/counter) +"\n";
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

std::string makeTime(time_t uTime)
{

    struct tm * timeinfo;
    char buffer[80];
    timeinfo = localtime(&uTime);

    strftime(buffer,80,"%H:%M",timeinfo);
    std::string str(buffer);
    return str;
}

void resetResults(bool map)
{
    result="";
    durata=0;
    distanta=0;
    durataT=0;
    delay=0;
    counter=0;
    if (map)
    {
        resultMap.clear();
    }
}

