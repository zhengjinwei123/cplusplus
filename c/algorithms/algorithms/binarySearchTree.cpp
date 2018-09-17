#include "stdafx.h"
#include "binarySearchTree.h"
#include <ctime>
#include <cassert>
#include <iostream>
using namespace std;


void testBinarySearch() {
	int n = 1000000;
	int *arr = new int[n];
	for (int i = 0; i < n; i++) {
		arr[i] = i;
	}

	// ²âÊÔ·ÇµÝ¹é
	clock_t startTime = clock();
	for (int i = 0; i < 2 * n; i++) {
		int v = binarySearch(arr, n, i);
		if (i < n) {
			assert(v == i);
		}
		else {
			assert(v == -1);
		}
	}

	clock_t endTime = clock();
	cout << "Binary Search(Without Recursion):" << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

	// ²âÊÔµÝ¹é
	startTime = clock();
	for (int i = 0; i < 2 * n; i++) {
		int v = binarySearch2(arr, n, i);
		if (i < n) {
			assert(v == i);
		}
		else {
			assert(v == -1);
		}
	}
	endTime = clock();
	cout << "Binary Search(With Recursion):" << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
	delete [] arr;
}

void testFloorCeil() {
	int a[] = {1,1,1,2,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6};
	int n = sizeof(a) / sizeof(int);

	for (int i = 0; i <= 8; i++) {
		int floorIndex = floor(a, n, i);
		cout << "the floor index of " << i << " is " << floorIndex << ".";
		if (floorIndex >= 0 && floorIndex < n)
			cout << "The value is " << a[floorIndex] << ".";
		cout << endl;

		int ceilIndex = ceil(a, sizeof(a) / sizeof(int), i);
		cout << "the ceil index of " << i << " is " << ceilIndex << ".";
		if (ceilIndex >= 0 && ceilIndex < n)
			cout << "The value is " << a[ceilIndex] << ".";
		cout << endl;

		cout << endl;
	}
}