#ifndef SQLSTATEMENT_H
#define SQLSTATEMENT_H
#include <string>
#include <iostream>
#include <DBHandler.h>

class SQLStatement
{
public:

    int client_id;
    int trainID;
    bool hasPriority;

    SQLStatement(time_t delay, int trainID,bool hasPriority=true);

    SQLStatement(std::string dep_station,
                 std::string arr_station,
                 std::string dep_time,
                 std::string arr_time,
                 int client_id, bool hasPriority=false);

    void getTrains();
    void postDelay();
    void postOntim();


protected:

private:
    std::string dep_station;
    std::string arr_station;
    std::string dep_time;
    std::string arr_time;
    int delay;
    void prepare_class();
    std::string query;

};

#endif // SQLSTATEMENT_H
