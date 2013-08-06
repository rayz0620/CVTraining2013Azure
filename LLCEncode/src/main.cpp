#include <iostream>

#include "LLC.h"

using namespace std;
using namespace LLC;

int main(int argc, char *argv[])
{
    if (argc < 4)
	{
        printf("Insufficient arguments\n");
        printf("Usage: llc [configPath] [imgFeatPath] [LLCFeatPath]\n");
        return 0;
    }else
    {
        string configPath = argv[1];
        string imgFeatPath = argv[2];
        string LLCFeatPath = argv[3];
        LLCoder coder;

        coder.loadConfig(configPath);
        bool success = coder.generateLLCDatabase(imgFeatPath, LLCFeatPath);
        if (success)
        {
            printf("LLC Coding successfully completed\n");
        }else
        {
            printf("LLC Coding failed! (Maybe the paths are wrong?)\n");
        }
    }
    return 0;
}
