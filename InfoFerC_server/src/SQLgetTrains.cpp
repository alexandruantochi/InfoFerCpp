#include "SQLgetTrains.h"


SQLgetTrains::SQLgetTrains(SQLStatement *statement)
{
    this->statement=statement;
    this->id=statement->client_id;
    this->hasPriority=statement->hasPriority;
}

void SQLgetTrains::execute()
{
    statement->getTrains();
}
