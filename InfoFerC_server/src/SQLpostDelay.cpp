#include "SQLpostDelay.h"


SQLpostDelay::SQLpostDelay(SQLStatement* statement)
{
    this->statement=statement;
    this->id=statement->client_id;
    this->hasPriority=statement->hasPriority;
}

void SQLpostDelay::execute()
{
    statement->postDelay();
}
