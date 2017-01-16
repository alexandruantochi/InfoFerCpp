#ifndef DBENGINE_H_INCLUDED
#define DBENGINE_H_INCLUDED
#include <iostream>
#include <string>
#include <sqlite3.h>
#include <map>
#include <vector>




void DBEngineInit(const char *location);
//connect to the database

void executeQuery(std::string query, int client_id);
//execute the given query from the SQLQueue


int queryResolver(void *client_id, int argc, char **argv, char **azColName);
//get the results, parse them


void resetResults();
//reset results, used everytime a new query is executed


int fileGenerator(int client_id, std::map<std::string, std::string>);
//generate the file to send it to the client


#endif // DBENGINE_H_INCLUDED
