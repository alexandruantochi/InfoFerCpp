#include "SQLStatement.h"
#include <string>



SQLStatement::SQLStatement()
{

    prepare_class();
} ;



SQLStatement::SQLStatement(std::string dep_station,
                           std::string arr_station,
                           std::string dep_time,
                           std::string arr_time,
                           std::string delay, int client_id, bool hasPriority)
{
    this->dep_station=dep_station;
    this->arr_station=arr_station;
    this->dep_time=dep_time;
    this->arr_time=arr_time;
    this->delay=delay;
    this->client_id=client_id;
    prepare_class();
}

void SQLStatement::prepare_class()
{
    if (dep_station.empty())
    {
        dep_station="%";
    }
    if (arr_station.empty())
    {
        arr_station="%";
    }
    if (dep_time.empty())
    {
        dep_time="0";
    }
    if (delay.empty())
    {
        delay="0";
    }
}

void SQLStatement::getTrains()
{
    std::cout<< "Get trains "<< client_id << std::endl;
    std::cout<< arr_station + " " + dep_station + " " + dep_time + " " + arr_time + " " + delay + "\n";
}


void SQLStatement::postDelay()
{
    std::cout<<"Post delay " << client_id << std::endl;
}

void SQLStatement::postOntim()
{
    std::cout<<"Post on time " <<client_id << std::endl;
}
