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
        printf("Usage: imgfea [configPath] [imgPath] [featPath]\n");
        return 0;
    }else
    {
        string configPath = argv[1];
        string imagePath = argv[2];
        string featPath = argv[3];

        FeatureDatabase db;
        db.loadConfig(configPath);
        db.generateDatabase(imagePath, featPath);
    }
	return 0;
}
