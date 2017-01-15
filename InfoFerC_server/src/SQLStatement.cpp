#include "SQLStatement.h"
#include <string>
#include "DBEngine.h"

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
    if (delay.empty())
    {
        //second day
        delay="86460";
    }
}

void SQLStatement::getTrains()
{
    query = "select id_tren, tip_tren, statie_plecare, statie_sosire, ifnull(intarzieri,0),"
" ora_plecare, nume_statie, durata, distanta"
" from traseuri t left join trenuri tr on t.id_traseu = tr.traseu"
" where"
" t.id_traseu in"
	" (select t1.id_traseu from traseuri t1 join traseuri t2 on t1.id_traseu = t2.id_traseu"
	" where t1.nume_statie like '%'"
	" and t2.nume_statie like '%'"
	" and t1.id_statie < t2.id_statie+1"
	" and t.id_statie < t2.id_statie + 1"
	" and t.id_statie > t1.id_statie - 1)"
" and ora_plecare >= 0 and ora_plecare <= 86400"
" order by tr.id_tren;";
    dbengineTest();
}


void SQLStatement::postDelay()
{
    query = "Select * from trenuri";
    dbengineTest();
}

void SQLStatement::postOntim()
{
    query = "select * from trenuri";
    dbengineTest();
}
