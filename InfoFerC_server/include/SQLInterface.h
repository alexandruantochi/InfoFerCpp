#ifndef SQLINTERFACE_H
#define SQLINTERFACE_H
#include <iostream>

class SQLInterface
{
    public:


    protected:
        virtual void execute()=0;

    private:
        SQLInterface();
};

#endif // SQLINTERFACE_H