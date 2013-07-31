#include <iostream>
#include <string>
#include "FeatureDatabase.h"

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
        printf("Insufficient arguments\n");
        return 0;
    }else
    {
        string featPath = argv[1];
        string dictPath = argv[2];
        string percentage = argv[3];
        FeatureDatabase db;
        db.randomDictionary(featPath, dictPath, atof(percentage.c_str()));
    }
	return 0;
}
