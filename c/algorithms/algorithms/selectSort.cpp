#include "stdafx.h"
#include "selectSort.h"
#include <iostream>
using namespace std;

namespace selectsort {
	void selectSort(int arr[], int n) {
		for (int i = 0; i < n; ++i) {
			int minIndex = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[minIndex]) {
					minIndex = j;
				}
			}

			swap(arr[i], arr[minIndex]);
		}
	}
};
