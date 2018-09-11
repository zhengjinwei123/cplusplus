// pbtest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "person/person.pb.h"
#include "person/result.pb.h"

using namespace std;

//int _tmain(int argc, _TCHAR* argv[])
int main(int argc, char* argv[])
{
	//У��Э��汾
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	Message::CPerson outPerson;
	Message::CPerson inPerson;

	outPerson.set_id(123);
	outPerson.set_name("aaron");
	outPerson.set_email("aaron@example.com");

	Message::CResult *pResult = NULL;
	pResult = outPerson.add_result();
	pResult->set_url("url01");
	pResult->set_title("title01");
	pResult->set_url("snippets01");
	pResult = outPerson.add_result();
	pResult->set_url("url02");
	pResult->set_title("title02");
	pResult->set_url("snippets02");

	if (0)
	{
		//������д��person.pb�ļ�
		fstream outFile("person.pb", ios::out | ios::binary | ios::trunc);
		outPerson.SerializeToOstream(&outFile);
		outFile.close();

		//��person.pb�ļ���ȡ����
		fstream inFile("person.pb", ios::in | ios::binary);
		if (!inPerson.ParseFromIstream(&inFile))
		{
			cerr << "Failed to parse person.pb." << endl;
			exit(1);
		}
	}
	else
	{
		stringstream outStream;
		stringstream inStream;

		outPerson.SerializeToOstream(&outStream);
		inStream << outStream.str();
		inPerson.ParseFromIstream(&inStream);
	}

	//
	cout << "ID:"  << inPerson.id() << endl;
	cout << "Name:"  << inPerson.name() << endl;
	if (inPerson.has_email())
	{
		cout << "e-mail:"  << inPerson.email() << endl;
	}

	for(int i = 0; i < inPerson.result_size(); i++)
	{
		cout << "title:"  << inPerson.result(i).title() << endl;
	}

	getchar();
	return 0;
}

