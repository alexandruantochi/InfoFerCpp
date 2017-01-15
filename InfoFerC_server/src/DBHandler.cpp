//#include "DBHandler.h"
//#include <iostream>
//
//
//DBHandler::DBHandler()
//{
//    std::cout<< "ERROR, db not init."<<std::endl;
//}
//
//
//DBHandler::DBHandler(const char* DBLocation)
//{
//    database = sqlite3_open(DBLocation, &db);
//    this->errors=0;
//
//    if (database)
//    {
//        std::cout<< "Error initiating database code: "<< database <<std::endl;
//        sqlite3_close(db);
//        exit(1);
//    }
//    else
//    {
//        std::cout<< "Database init at " << DBLocation << " sqlite3_libversion : "<< sqlite3_libversion() << std::endl;
//    }
//}
//
//
//void DBHandler::executeQuery(std::string query, int client_id)
//{
//    std::cout<< query << std::endl << std::endl;
//
//    database = sqlite3_exec(db, query.c_str(), this->queryResolver, (void*)client_id, &errors);
//
//    if (database)
//    {
//
//        std::cout<< "Failed to retrieve info from db." << std::endl  << std::endl;
//        std::cout<< "Error:"<< errors << std::endl << std::endl;
//        sqlite3_close(db);
//    }
//
//
//}
//
//int DBHandler::queryResolver(void *client_id, int argc, char **argv,
//                  char **azColName)
//{
//    std::cout<< "DBHandler client_id = " << client_id;
//    return 0;
//}
//
