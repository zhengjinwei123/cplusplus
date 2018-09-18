#pragma once
#ifndef  _FILE_OPS_H__
#define _FILE_OPS_H__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// �ļ���ز���
namespace FileOps {
	// ��ȡ�ļ�����Ϊfilename�е����ݣ��������а��������д���Ž�words��
	int firstCharacterIndex(const string& s, int start);

	// ���ַ���s�е�������ĸת����Сд֮�󷵻�
	string lowerS(const string& s);

	// ��ȡ�ļ�����Ϊfilename�е����ݣ��������а��������д���Ž�words��
	bool readFile(const string& filename, vector<string> &words);
}

#endif