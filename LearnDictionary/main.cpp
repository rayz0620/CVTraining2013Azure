#include "SparseCoder.h"
#include "IO.h"

using namespace std;
using namespace SparseCoding;
using namespace IOUtils;

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
        printf("Insufficient arguments\n");
        return 0;
    }else
    {
        string configPath = argv[1];
        string initialDictPath = argv[2];
        string dictPath = argv[3];
        SparseCoder coder;
        coder.loadConfig(configPath);
        Mat X = readMatrixFromYML(initialDictPath);
        auto result = coder.encode(X);
        saveMatrixToYML(dictPath, result[0] );
    }
    return 0;
}
