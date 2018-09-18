// algorithms.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "selectSort.h"
#include "insertSort.h"
#include "mergeSort.h"
#include "common.h"
#include "qsort.h"
#include "heap.h"
#include "binarySearchTree.h"
#include "BST.h"




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

	// 选择排序
	int N = 1000;
	int *arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("Select sort", selectsort::selectSortT, arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// 插入排序
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("insert sort", insertsort::insertSort, arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// 优化后的插入排序
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("insert sort fast", insertsort::insertSortF, arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// 归并排序
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("merge sort", mergesort::mergeSort,arrp2,N);
	sortTestHelper::printArray(arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// 自底向上归并
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("merge sort bu", mergesort::mergeSortBU, arrp2, N);
	sortTestHelper::printArray(arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// 快速排序
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("quick sort", quicksort::quickSort, arrp2, N);
	sortTestHelper::printArray(arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// 三路快速排序
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("quick sort 3 ways", quicksort3ways::quickSort, arrp2, N);
	sortTestHelper::printArray(arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// 堆测试
	cout << "--------------heap test------------------" << endl;
	MaxHeap<int> maxHeap = MaxHeap<int>(100);
	cout << "maxHeap.size:" << maxHeap.size() << endl;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 15; i++) {
		maxHeap.insert(rand() % 100);
	}
	maxHeap.testPrint();

	// 二分查找测试
	testBinarySearch();

	testFloorCeil();

	testBST();
	system("pause");
    return 0;
}

