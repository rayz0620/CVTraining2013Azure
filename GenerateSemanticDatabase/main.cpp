#include <iostream>
#include "SemanticDatabase.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 4)
	{
        printf("Insufficient arguments\n");
        return 0;
    }else
    {
        string rawPath = argv[1];
        string outPath = argv[2];

        SemanticDatabase sdb;
        sdb.loadraw(rawPath);
        sdb.generateFeatureMatrix();
        sdb.generateTrivialRelationMatrix();
        sdb.saveSemanticInfo(outPath);
    }
    return 0;
}
