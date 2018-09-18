// algorithms.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// ������� ����
	int *arrp = sortTestHelper::generateRandomArray(10, 1, 100);
	selectsort::selectSortT(arrp, 10);
	sortTestHelper::printArray(arrp,10);
	delete[] arrp;

	// ѡ������
	int N = 1000;
	int *arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("Select sort", selectsort::selectSortT, arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// ��������
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("insert sort", insertsort::insertSort, arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// �Ż���Ĳ�������
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("insert sort fast", insertsort::insertSortF, arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// �鲢����
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("merge sort", mergesort::mergeSort,arrp2,N);
	sortTestHelper::printArray(arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// �Ե����Ϲ鲢
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("merge sort bu", mergesort::mergeSortBU, arrp2, N);
	sortTestHelper::printArray(arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// ��������
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("quick sort", quicksort::quickSort, arrp2, N);
	sortTestHelper::printArray(arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// ��·��������
	arrp2 = sortTestHelper::generateRandomArray(N, 0, N);
	sortTestHelper::testSort("quick sort 3 ways", quicksort3ways::quickSort, arrp2, N);
	sortTestHelper::printArray(arrp2, N);
	delete[] arrp2;
	arrp2 = NULL;

	// �Ѳ���
	cout << "--------------heap test------------------" << endl;
	MaxHeap<int> maxHeap = MaxHeap<int>(100);
	cout << "maxHeap.size:" << maxHeap.size() << endl;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 15; i++) {
		maxHeap.insert(rand() % 100);
	}
	maxHeap.testPrint();

	// ���ֲ��Ҳ���
	testBinarySearch();

	testFloorCeil();

	testBST();
	system("pause");
    return 0;
}

