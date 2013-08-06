#include <opencv2/opencv.hpp>
#include "FeatureItem.h"
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

namespace LLC{
	using namespace cv;

	class LLCoder{
	public:
		LLCoder();
		bool generateLLCDatabase(path srcPath, path destPath);
		Mat calculateLLC( FeatureItem feaSet);

		void saveConfig(const string& filename);
		void loadConfig(const string& filename);

		Mat B;
		Mat pyramid;
		int knn;
		bool isParallel;
		int threads;

	private:
		void generateLLCSingle(path srcPath, path destPath);
		bool saveSingle(Mat item, path destPath, const string& filename, const string& extension = ".yml");
	};
}
