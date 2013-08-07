#include "SemanticDatabase.h"

void SemanticDatabase::generateTrivialRelationMatrix()
{
	Mat semRelation = Mat::zeros(size(), size(), CV_32F);

	int rowCounter = 0;
	for (auto i: *this)
	{
		int colCounter = 0;
		for (auto j : *this)
		{
			if (i.second.label[0] == j.second.label[0])
			{
				semRelation.at<MatElem>(rowCounter, colCounter) = 1;
				semRelation.at<MatElem>(colCounter, rowCounter) = 1;
			}
			colCounter++;
		}
		rowCounter++;
	}
	relationMatrix = semRelation;
}

SemanticDatabase::~SemanticDatabase()
{
	clear();
}

SemanticDatabase::SemanticDatabase()
{

}

Mat SemanticDatabase::RelationMatrix() const
{
	return relationMatrix;
}

Mat SemanticDatabase::getFeatureMatrix()
{
	if (!empty())
	{
		if (featureMatrix.empty())
		{
			generateFeatureMatrix();
		}
		return featureMatrix;
	}
	return featureMatrix;
}

void SemanticDatabase::generateFeatureMatrix()
{
	auto a = this->begin();
	Mat featureM(0,
		a->second.feature.size().height,
		a->second.feature.type());

	for (auto item : *this)
	{
		Mat col = item.second.feature.t();
		featureM.push_back(col);
	}
	featureM = featureM.t();
	featureMatrix = featureM;
}

Mat SemanticDatabase::getRelationMatrix()
{
	if (relationMatrix.empty())
	{
		generateTrivialRelationMatrix();
	}
	return relationMatrix;
}

void SemanticDatabase::saveSemanticInfo(string destPath)
	{
        path relPath(destPath);
        relPath /= "relation.gz";
        saveMatrixToYML(relPath, relationMatrix);

        path feaPath(destPath);
        feaPath /= "auxfeat.gz";
        saveMatrixToYML(feaPath, featureMatrix);
	}

void SemanticDatabase::loadSemanticInfo(string srcPath)
{
    path relPath(srcPath);
    relPath /= "relation.gz";
    relationMatrix = readMatrixFromYML(relPath);

    path feaPath(srcPath);
    feaPath /= "relation.gz";
    featureMatrix = readMatrixFromYML(feaPath);
}
