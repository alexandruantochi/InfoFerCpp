#ifndef SQLSTATEMENT_H
#define SQLSTATEMENT_H
#include <string>
#include <iostream>
#include <DBHandler.h>

class SQLStatement
{
public:
    int client_id;
    bool hasPriority;
    SQLStatement();
    SQLStatement(std::string dep_station,
                 std::string arr_station,
                 std::string dep_time,
                 std::string arr_time,
                 std::string delay, int client_id, bool hasPriority, DBHandler* dbHandler);

    void getTrains();
    void postDelay();
    void postOntim();


protected:

private:
    std::string dep_station;
    std::string arr_station;
    std::string dep_time;
    std::string arr_time;
    std::string delay;
    void prepare_class();
    std::string query;
    DBHandler* dbHandler;

};

#endif // SQLSTATEMENT_H
