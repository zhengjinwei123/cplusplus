// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdlib.h>
#include <ctype.h>
#include "stack_array.h"

#define DEBUG_PRINT printf("File %s line %d:"  \
	                                        " x=%d ,y = %d, z=%d \r\n", \
											__FILE__,__LINE__, \
											1,2,3);



int max(int a, int b){
	return (a) > (b) ? (a) : (b);
}

#define    MAX(a,b)  ( (a) > (b) ? (a) : (b))



void printStr(char const *strMessage)
{
	if (strMessage == NULL){
		return;
	}
	printf("[%s] [%d]   %s \r\n", __DATE__, __TIME__, strMessage);
}


typedef   void (*funcp)(void *param);

void callback(funcp p,void* param){
	(*p)(param);
}


void myCallback(void *p){
	int* a = (int*)(p);
	char pstr[20];// new char[100];
	_itoa_s(*a, pstr, 10);
	printStr(pstr);
}

int _tmain(int argc, _TCHAR* argv[])
{
	DEBUG_PRINT;


	int i = 1, j = 10;
	int a = max(i, j);
	int b = MAX(i++, j++);

	printf("%d,%d:i=%d,j=%d \r\n", a, b,i,j);

	printStr("hello,world");


	int n = 120;
	callback(myCallback, &n);

	push(1);
	push(2);
	push(3);

	system("pause");
	return 0;
}

