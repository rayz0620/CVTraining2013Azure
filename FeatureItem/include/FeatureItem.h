#pragma once
#include <opencv2/opencv.hpp>
#include <string>

#define FEA_ITEM_YAML_ELEM_NAME "feat"

using std::string;
using cv::Mat;
using cv::FileStorage;
using cv::FileNode;

struct FeatureItem{
	string id;
	Mat feaArr;
	double width;
	double height;
	Mat x;
	Mat y;

	void write(FileStorage& fs) const;
	void read(const FileNode& fs);
};

void write(FileStorage& fs, const std::string&, const FeatureItem& x);
void read(const FileNode& node, FeatureItem& x, const FeatureItem& default_value = FeatureItem());
