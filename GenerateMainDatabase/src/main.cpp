#include <iostream>
#include "RetrievalDatabase.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
	{
        printf("Insufficient arguments\n");
        printf("Usage: maindb [rawPath] [outPath]\n");
        return 0;
    }else
    {
        string rawPath = argv[1];
        string outPath = argv[2];

        RetrievalDatabase sdb;
        sdb.loadraw(rawPath);
        sdb.save(outPath);
    }
    return 0;
}
