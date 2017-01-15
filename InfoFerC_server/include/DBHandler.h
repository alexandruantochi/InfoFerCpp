#ifndef DBHANDLER_H
#define DBHANDLER_H
#include <sqlite3.h>
#include <string>


class DBHandler
{
    public:
        DBHandler();
        DBHandler(const char* DBLocation);
        void executeQuery(std::string);

    protected:

    private:
    sqlite3 *db;
    int database;

};
#endif // DBHANDLER_H
