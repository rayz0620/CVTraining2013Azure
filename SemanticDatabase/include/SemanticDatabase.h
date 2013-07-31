#pragma once
#include <opencv2/opencv.hpp>
#include "RetrievalDataBase.h"
#include "Util.h"
#include "IO.h"

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

	void saveSemanticInfo(path destPath);

	void loadSemanticInfo(path srcPath);

private:
	Mat relationMatrix;
	Mat featureMatrix;
};
