#pragma once
#ifndef _COMMON_H__
#define _COMMON_H__
#include <iostream>
#include <cassert>
#include <ctime>
using namespace std;

namespace sortTestHelper {
	template<typename T>
	void printArray(T arr[], int n = 0) {
		for (int i = 0; i < n; i++) {
			std::cout << arr[i] << ",";
		}
		std::cout << endl << endl;
	}

	int* generateRandomArray(int n, int rangeL, int rangeR);

	// 判断数组是否有序
	template<typename T>
	bool isSorted(T arr[], int n) {
		for (int i = 0; i < n - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	void testSort(const string &sortName, void(*sort)(T[], int), T arr[], int n) {
		clock_t startTime = clock();
		sort(arr, n);
		clock_t endTime = clock();

		assert(isSorted(arr, n));

		cout << sortName << ":" << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
	}
}
#endif
