#include <iostream>
#include "SemanticDatabase.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
	{
        printf("Insufficient arguments\n");
        printf("Usage: semdb [rawPath] [SemanticInfoOutputPath] [DatabseOutputPath]\n");
        return 0;
    }else
    {
        string rawPath = argv[1];
        string semPath = argv[2];
        string dbPath = argv[3];
        SemanticDatabase sdb;
        sdb.loadraw(rawPath);
        sdb.generateFeatureMatrix();
        sdb.generateTrivialRelationMatrix();
        sdb.saveSemanticInfo(semPath);
        sdb.save(dbPath);
    }
    return 0;
}
