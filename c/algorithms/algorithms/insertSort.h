#pragma once
/************************************************************************/
/* 插入排序，因为要交换的次数很多，所以运行速度低于选择排序
  插入排序与选择排序不同
   1. 选择排序是从指定位置往后找
   2. 插入排序是从指定位置往前找
*/
/************************************************************************/

#ifndef  _INSERT_SORT_H__
#define _INSERT_SORT_H__
#include <iostream>
using namespace std;


namespace insertsort {
	/************************************************************************/
	/* 插入排序的核心思想，是从小到大进行排序                                                                     */
	/************************************************************************/
	template<typename T>
	void insertSort(T arr[], int n) {
		for (int i = 1; i < n; ++i) {
			for (int j = i; j > 0; j--) {
				if (arr[j] < arr[j - 1]) {
					swap(arr[j], arr[j - 1]);
				}
				else {
					break;
				}
			}
		}
	}

	/************************************************************************/
	/* 优化的插入排序，减少交换次数                                                                     */
	/************************************************************************/
	template<typename T>
	void insertSortF(T arr[], int n) {
		for (int i = 1; i < n; ++i) {
			T tmp = arr[i];
			for (int j = i; j > 0; j--) {
				if (tmp < arr[j - 1]) {
					arr[j] = arr[j - 1];
				}
				else {
					arr[j] = tmp;
					break;
				}
			}
		}
	}

	// 对 arr [l...r] 范围内的数组进行插入排序
	template<typename T>
	void insertSortRange(T arr[], int left, int right) {
		for (int i = left + 1; i <= right; i++) {
			T e = arr[i];
			int j;
			for (j = i; j > left && arr[j - 1] > e; j--) {
				arr[j] = arr[j - 1];
			}

			arr[j] = e;
		}
		return;
	}
}

#endif