#include "SQLgetTrains.h"
#include <SQLStatement.h>

SQLgetTrains::SQLgetTrains(SQLStatement *statement)
{
    this->statement=statement;
}

void SQLgetTrains::execute()
{
    statement->getTrains();
}
