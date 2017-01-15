#ifndef SQLINTERFACE_H
#define SQLINTERFACE_H
#include <iostream>

class SQLInterface
{
public:
    virtual void execute()=0;
    //checks if the query has priority
    bool hasPriority;
    //the id of the client that executes this query
    int id;
protected:
    SQLInterface();
private:


};

#endif // SQLINTERFACE_H
