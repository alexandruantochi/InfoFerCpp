#ifndef SQLINTERFACE_H
#define SQLINTERFACE_H
#include <iostream>

class SQLInterface
{
public:
    virtual void execute()=0;

protected:
    SQLInterface();


private:

};

#endif // SQLINTERFACE_H
