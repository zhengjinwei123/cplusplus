#pragma once
#ifndef  _FILE_OPS_H__
#define _FILE_OPS_H__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// 文件相关操作
namespace FileOps {
	// 读取文件名称为filename中的内容，并将其中包含的所有词语放进words中
	int firstCharacterIndex(const string& s, int start);

	// 将字符串s中的所有字母转换成小写之后返回
	string lowerS(const string& s);

	// 读取文件名称为filename中的内容，并将其中包含的所有词语放进words中
	bool readFile(const string& filename, vector<string> &words);
}

#endif