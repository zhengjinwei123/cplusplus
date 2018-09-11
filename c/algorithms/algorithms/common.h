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
}


#endif
