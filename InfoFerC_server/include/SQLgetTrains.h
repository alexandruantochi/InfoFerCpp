#ifndef SQLGETTRAINS_H
#define SQLGETTRAINS_H
#include <SQLStatement.h>

class SQLgetTrains
{
    public:
        SQLgetTrains(SQLStatement *statement);
        void execute();

    protected:

    private:
    SQLStatement* statement;
};

#endif // SQLGETTRAINS_H
