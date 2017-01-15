#ifndef SQLGETTRAINS_H
#define SQLGETTRAINS_H
#include <SQLStatement.h>
#include <SQLInterface.h>
#include <iostream>

class SQLgetTrains: public SQLInterface
{
    public:
        SQLgetTrains(SQLStatement *statement);
        void execute();

    protected:

    private:
    SQLStatement* statement;
};

#endif // SQLGETTRAINS_H
