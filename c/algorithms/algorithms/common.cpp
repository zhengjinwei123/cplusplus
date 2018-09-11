#include "stdafx.h"
#include "common.h"

namespace sortTestHelper {
	int* generateRandomArray(int n, int rangeL, int rangeR) {
		assert(rangeL < rangeR);

		int *arr = new int[n];
		srand((unsigned int)time(NULL));
		for (int i = 0; i < n; ++i) {
			arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
		}
		return arr;
	}
};

