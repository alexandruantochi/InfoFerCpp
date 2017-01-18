#ifndef SQLQUEUE_H
#define SQLQUEUE_H
#include <iostream>
#include <SQLInterface.h>
#include <list>



class SQLQueue
{
    public:
        static std::list<SQLInterface*> stmtList;
        static void addQuery(SQLInterface* sqlCommand);
            // if the command has priority, it will push it in the front of the list
            // else the command will be on a first-come-first-server basis
        static void startQuery();
    protected:

    private:
        SQLQueue();

};


#endif // SQLQUEUE_H
