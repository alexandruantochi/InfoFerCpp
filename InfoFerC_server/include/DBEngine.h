#ifndef DBENGINE_H_INCLUDED
#define DBENGINE_H_INCLUDED
#include <iostream>
#include <sqlite3.h>
#include <map>
#include <vector>

void DBEngineInit(const char *location);

void executeQuery(std::string query, int client_id);

int queryResolver(void *client_id, int argc, char **argv, char **azColName);

#endif // DBENGINE_H_INCLUDED
