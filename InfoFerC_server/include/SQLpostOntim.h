#ifndef SQLPOSTONTIM_H
#define SQLPOSTONTIM_H
#include <SQLStatement.h>
#include <SQLInterface.h>
#include <iostream>


class SQLpostOntim: public SQLInterface
{
    public:
        SQLpostOntim(SQLStatement* statement);
        void execute();

    protected:

    private:
        SQLStatement* statement;
};

#endif // SQLPOSTONTIM_H
