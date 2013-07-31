#include "FeatureItem.h"


void FeatureItem::write( FileStorage& fs ) const
{
	fs << "{";
	fs << "id" << id;
	fs << "feaArr" << feaArr;
	fs << "width" << width;
	fs << "height" << height;
	fs << "x" << x;
	fs << "y" << y;
	fs << "}";
}

void FeatureItem::read( const FileNode& fs )
{
	fs["id"] >> id;
	fs["feaArr"] >> feaArr;
	fs["width"] >> width;
	fs["height"] >> height;
	fs["x"] >> x;
	fs["y"] >> y;
}

void write( FileStorage& fs, const std::string&, const FeatureItem& x )
{
	x.write(fs);
}

void read( const FileNode& node, FeatureItem& x, const FeatureItem& default_value /*= FeatureItem()*/ )
{
	if(node.empty())
		x = default_value;
	else
		x.read(node);
}
