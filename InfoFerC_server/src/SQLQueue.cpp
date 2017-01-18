#include "SQLQueue.h"

std::list<SQLInterface*> SQLQueue::stmtList;


extern void clear(int lines);



SQLQueue::SQLQueue()
{
    std::cout<< "Something went wrong.." << std::endl;
    clear(2);
}


void SQLQueue::addQuery(SQLInterface* sqlCommand)
{

    if (sqlCommand->hasPriority)
    {
        SQLQueue::stmtList.push_front(sqlCommand);
        std::cout<<"Added query with id "<<sqlCommand->id <<" to the front of the line"<<std::endl;
        clear(2);
    }
    else

    {
        SQLQueue::stmtList.push_back(sqlCommand);
        std::cout<<"Added query with id "<<sqlCommand->id <<" to the back of the line"<<std::endl;
        clear(2);
    }
}

void SQLQueue::startQuery()
{
    if (!SQLQueue::stmtList.empty())
    for (std::list<SQLInterface*>::iterator it= SQLQueue::stmtList.begin(); it!=SQLQueue::stmtList.end(); ++it)
    {
        (*it)->execute();
    }
    stmtList.clear();
}


