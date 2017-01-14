#include "SQLgetTrains.h"


SQLgetTrains::SQLgetTrains(SQLStatement *statement)
{
    this->statement=statement;
}

void SQLgetTrains::execute()
{
    statement->getTrains();
    std::cout<<"Executing getTrains on cliend_id: " << statement->client_id << std::endl;
}
