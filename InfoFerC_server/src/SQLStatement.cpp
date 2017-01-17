#include "SQLStatement.h"
#include <string>
#include "DBEngine.h"

SQLStatement::SQLStatement(time_t delay, int trainID, bool hasPriority)
{
    this->delay=delay;
    this->trainID = trainID;
    this->delay = delay;
} ;



SQLStatement::SQLStatement(std::string dep_station,
                           std::string arr_station,
                           std::string dep_time,
                           std::string arr_time,
                           int client_id, bool hasPriority)
{
    this->dep_station=dep_station;
    this->arr_station=arr_station;
    this->dep_time=dep_time;
    this->arr_time=arr_time;
    this->delay=delay;
    this->client_id=client_id;
    this->hasPriority=hasPriority;
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
    if (arr_time.empty())
    {
        //second day
        arr_time="86460";
    }
}

void SQLStatement::getTrains()
{

    query = "select id_tren, tip_tren, statie_plecare, statie_sosire, intarzieri,"
            " ora_plecare, nume_statie, durata, distanta"
            " from traseuri t left join trenuri tr on t.id_traseu = tr.traseu"
            " where t.id_traseu in"
            " (select t1.id_traseu from traseuri t1 join traseuri t2 on t1.id_traseu = t2.id_traseu"
            " where t1.nume_statie ='"+this->dep_station+"'"
            " and t2.nume_statie ='"+this->arr_station+"'"
            " and t1.id_statie < t2.id_statie+1"
            " and t.id_statie < t2.id_statie + 1"
            " and t.id_statie > t1.id_statie - 1"
            " and ora_plecare >="+this->dep_time+" and ora_plecare <=" + this->arr_time + ")"
            " order by tr.id_tren;";

    executeQuery(query, this->client_id);
}


void SQLStatement::postDelay()
{
    delay = delay * 60;
    query = "update trenuri set intarzieri="+std::to_string(delay)+" where id_tren="+std::to_string(trainID)+";";
    executeUpdate(query);

}

void SQLStatement::postOntim()
{
    query = "update trenuri set intarzieri=0 where id_tren = " + std::to_string(trainID) +";";
    executeUpdate(query);
}
