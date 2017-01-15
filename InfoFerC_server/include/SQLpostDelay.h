#ifndef SQLPOSTDELAY_H
#define SQLPOSTDELAY_H
#include <SQLStatement.h>
#include <SQLInterface.h>
#include <iostream>

class SQLpostDelay: public SQLInterface
{
public:
    SQLpostDelay(SQLStatement* statement);
    void execute();
protected:

private:
    SQLStatement* statement;
};

#endif // SQLPOSTDELAY_H
