#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include "RetrievalDatabase.h"
#include "Util.h"
#include "IO.h"

using namespace std;
using namespace IOUtils;

class SemanticDatabase: public RetrievalDatabase{
public:
	SemanticDatabase();
	~SemanticDatabase();

	Mat RelationMatrix() const;

	Mat getFeatureMatrix();
	Mat getRelationMatrix();

	void generateFeatureMatrix();
	void generateTrivialRelationMatrix();

	void saveSemanticInfo(string destPath);

	void loadSemanticInfo(string srcPath);

private:
	Mat relationMatrix;
	Mat featureMatrix;
};
