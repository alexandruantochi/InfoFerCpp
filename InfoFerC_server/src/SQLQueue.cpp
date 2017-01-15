#include "SQLQueue.h"
#include <list>

SQLQueue::SQLQueue()
{
    std::cout<< "SQLQueue instance created." << std::endl;
}


void SQLQueue::addQuery(SQLInterface* sqlCommand)
{

    if (sqlCommand->hasPriority)
    {
        stmtList.push_front(sqlCommand);
        std::cout<<"Added query with id "<<sqlCommand->id <<" to the front of the line"<<std::endl;
    }
    else

    {
        stmtList.push_back(sqlCommand);
        std::cout<<"Added query with id "<<sqlCommand->id <<" to the back of the line"<<std::endl;
    }
}

void SQLQueue::startQuery()
{
    for (std::list<SQLInterface*>::iterator it= stmtList.begin(); it!=stmtList.end(); ++it)
    {
        (*it)->execute();
    }

}
