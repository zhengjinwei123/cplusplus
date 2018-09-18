#include "stdafx.h"
#include "fileOps.h"

namespace FileOps {
	// 读取文件名称为filename中的内容，并将其中包含的所有词语放进words中
	int firstCharacterIndex(const string& s, int start) {
		for (size_t  i = start; i < s.length(); i++) {
			cout << s << endl;
			if (isalpha(s[i]))// 是否英文字母
				return i;
		}
		return s.length();
	}

	// 将字符串s中的所有字母转换成小写之后返回
	string lowerS(const string& s) {
		string ret = "";
		for (size_t i = 0; i < s.length(); i++) {
			ret += tolower(s[i]);
		}

		return ret;
	}

	// 读取文件名称为filename中的内容，并将其中包含的所有词语放进words中
	bool readFile(const string& filename, vector<string> &words) {
		// 文件读取
		string line;
		string contents = "";
		ifstream file(filename);
		if (file.is_open()) {
			while (getline(file, line))
			{
				contents += (line + "\n");
			}
			file.close();
		}

		// 简单分词
		// 这个分词方式相对简陋, 没有考虑很多文本处理中的特殊问题
		// 在这里只做demo展示用
		int start = firstCharacterIndex(contents, 0);
		for (size_t i = start + 1; i <= contents.length();) {
			if (i == contents.length() || !isalpha(contents[i])) {
				words.push_back(lowerS(contents.substr(start, i - start)));
				start = firstCharacterIndex(contents, i);
				i = start + 1;
			}
			else {
				i++;
			}
		}

		return true;
	}

};