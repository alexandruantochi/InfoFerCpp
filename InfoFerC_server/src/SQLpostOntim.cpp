#include "SQLpostOntim.h"


SQLpostOntim::SQLpostOntim(SQLStatement* statement)
{
    this->statement=statement;
    this->id=statement->client_id;
    this->hasPriority=statement->hasPriority;
}

void SQLpostOntim::execute()
{
    statement->postOntim();
    std::cout<<"Executing postOntim on cliend_id: " << statement->client_id << std::endl;
}
