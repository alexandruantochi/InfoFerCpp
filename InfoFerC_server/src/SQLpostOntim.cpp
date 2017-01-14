#include "SQLpostOntim.h"


SQLpostOntim::SQLpostOntim(SQLStatement* statement)
{
    this->statement=statement;
}

void SQLpostOntim::execute()
{
    statement->postOntim();
    std::cout<<"Executing postOntim on cliend_id: " << statement->client_id << std::endl;
}
