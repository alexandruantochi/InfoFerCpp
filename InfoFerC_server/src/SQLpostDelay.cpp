#include "SQLpostDelay.h"


SQLpostDelay::SQLpostDelay(SQLStatement* statement)
{
    this->statement=statement;
}

void SQLpostDelay::execute()
{
    statement->postDelay();
    std::cout<<"Executing getTrains on cliend_id: " << statement->client_id << std::endl;
}
