#include "stdafx.h"
#include "fileOps.h"

namespace FileOps {
	// ��ȡ�ļ�����Ϊfilename�е����ݣ��������а��������д���Ž�words��
	int firstCharacterIndex(const string& s, int start) {
		for (size_t  i = start; i < s.length(); i++) {
			cout << s << endl;
			if (isalpha(s[i]))// �Ƿ�Ӣ����ĸ
				return i;
		}
		return s.length();
	}

	// ���ַ���s�е�������ĸת����Сд֮�󷵻�
	string lowerS(const string& s) {
		string ret = "";
		for (size_t i = 0; i < s.length(); i++) {
			ret += tolower(s[i]);
		}

		return ret;
	}

	// ��ȡ�ļ�����Ϊfilename�е����ݣ��������а��������д���Ž�words��
	bool readFile(const string& filename, vector<string> &words) {
		// �ļ���ȡ
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

		// �򵥷ִ�
		// ����ִʷ�ʽ��Լ�ª, û�п��Ǻܶ��ı������е���������
		// ������ֻ��demoչʾ��
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