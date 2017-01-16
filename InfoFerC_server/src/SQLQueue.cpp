#include "SQLQueue.h"
#include <list>

extern void clear(int lines);

SQLQueue::SQLQueue()
{
    std::cout<< "SQLQueue instance created." << std::endl;
    clear(2);
}


void SQLQueue::addQuery(SQLInterface* sqlCommand)
{

    if (sqlCommand->hasPriority)
    {
        stmtList.push_front(sqlCommand);
        std::cout<<"Added query with id "<<sqlCommand->id <<" to the front of the line"<<std::endl;
        clear(2);
    }
    else

    {
        stmtList.push_back(sqlCommand);
        std::cout<<"Added query with id "<<sqlCommand->id <<" to the back of the line"<<std::endl;
        clear(2);
    }
}

void SQLQueue::startQuery()
{
    for (std::list<SQLInterface*>::iterator it= stmtList.begin(); it!=stmtList.end(); ++it)
    {
        (*it)->execute();
    }

}
