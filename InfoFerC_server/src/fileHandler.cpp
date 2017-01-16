#include "fileHandler.h"

extern void clear(int lines);

std::vector<FILE*> resultFiles (15);

int fileGenerator(int client_id, std::map<std::string, std::string> resultMap)
{

    std::string location = "clientFiles/"+ (std::to_string(client_id));

    std::ofstream client_file(location);

    for (auto itt = resultMap.begin(); itt!=resultMap.end(); ++itt)
    {
        client_file<<itt->second;
        client_file<<"\n";
    }

    client_file.close();

    FILE *clientFilePtr;


    if ((clientFilePtr=fopen(location.c_str(),"r"))==NULL)
    {
        std::cout<<"Error pointing to  client file!"<<std::endl;
        return 0;
    }
    else
    {
    resultFiles[client_id]=clientFilePtr;
    return 1;
    }


    clear(1);
    return 1;
}
