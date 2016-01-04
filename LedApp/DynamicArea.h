#pragma once

#include <vector>
using namespace std;

struct DynamicArea
{
	int areaID;
	int left;
	int top;
	int width;
	int height;

	vector<CString> contents;
};

struct AreaContent
{
	int fileOrd;
	CString content;
};