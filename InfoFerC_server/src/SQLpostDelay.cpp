#include "SQLpostDelay.h"


SQLpostDelay::SQLpostDelay(SQLStatement* statement)
{
    this->statement=statement;
    this->hasPriority=statement->hasPriority;
}

void SQLpostDelay::execute()
{
    statement->postDelay();
    std::cout<<"Executed postDelay on train_id: " << statement->trainID << std::endl;
}
