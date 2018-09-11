// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "person.h"
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void writeToFile() {
	string buffer;
	Person person;
	person.set_age(27);
	person.set_name("zjw");
	person.set_email("zjw@qq.com");
	person.add_phonenum("123");
	person.add_phonenum("245");
	fstream output("myfile.txt", ios::out | ios::binary);
	person.SerializeToString(&buffer);
	output.write(buffer.c_str(), buffer.size());
}

void readFromFile() {
	Person *person = new Person;
	char buffer[BUFSIZ];
	fstream input("myfile.txt", ios::in | ios::binary);
	input.read(buffer, sizeof(Person));
	person->ParseFromString(buffer);
	cout << person->name() << ":" << person->phonenum(0) << endl;
}

int main()
{
    writeToFile();
	readFromFile();
	system("pause");
    return 0;
}

