// algorithms.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "selectSort.h"
#include "common.h"

int main()
{
	int arr[10] = { 3,1,7,0,10,11,12,9,4,89 };
	selectsort::selectSort(arr, 10);
	sortTestHelper::printArray(arr, 10);

	double arrd[3] = { 1.2,0.22,3.9 };
	selectsort::selectSortT(arrd, 3);
	sortTestHelper::printArray(arrd, 3);

	selectsort::Student s[4] = { { "B",78 },{ "A", 86 },{ "G",34 },{ "D",78 } };
	selectsort::selectSortT(s, 4);
	sortTestHelper::printArray(s, 4);

	// 随机生成 数据
	int *arrp = sortTestHelper::generateRandomArray(10, 1, 100);
	selectsort::selectSortT(arrp, 10);
	sortTestHelper::printArray(arrp,10);
	delete[] arrp;

	system("pause");
    return 0;
}

