#include "SQLpostOntim.h"


SQLpostOntim::SQLpostOntim(SQLStatement* statement)
{
    this->statement=statement;
    this->hasPriority=statement->hasPriority;
}

void SQLpostOntim::execute()
{
    statement->postOntim();
    std::cout<<"Executed postOntim on train_id: " << statement->trainID << std::endl;
}
