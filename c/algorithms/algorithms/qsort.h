#pragma once
#ifndef _Q_SORT_H__
#define _Q_SORT_H__
#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

namespace quicksort {
	template<typename T>
	int __partition(T arr[], int left, int right) {
		 swap(arr[left], arr[rand() % (right - left + 1) + left]);
		// 选择后面所有元素都要与之比较的元素，一般直接选第一个就好
		T ref = arr[left];
		// 开始考察元素 : arr[left...j] < v ; arr[j+1....i] >v
		int j = left;
		for (int i = left + 1; i <= right; i++) {
			// arr[i] > ref 的时候不需要挪动，因为已经在最右侧了
			if (arr[i] < ref) {
				// 小于参考元素的都往左边挪动
				swap(arr[j+1],arr[i]);
				j++;
			}
		}

		// 最后把餐开元素置换到之间去
		swap(arr[left], arr[j]);
		// 最后j 的位置就是切分点应该有的位置
		return j;
	}

	// 对 arr[left...right] 内的元素进行快速排序，需要用到递归
	template<typename T>
	void __quickSort(T arr[], int left, int right) {
		// 左右指针相遇的时候直接退出
		if (left >= right) {
			return;
		}

		// 选择切分点， 执行 __partition 使得arr[left...p-1] < arr[p] ; arr[p+1...right] > arr[p]
		int partition = quicksort::__partition(arr, left, right);
		// 递归进行左右两侧排序
		quicksort::__quickSort(arr, left, partition - 1);
		quicksort::__quickSort(arr, partition + 1, right);
	}

	template<typename T>
	void quickSort(T arr[], int n) {
		// 设置随机种子
		srand((unsigned int)time(NULL));
		quicksort::__quickSort(arr, 0, n - 1);
	}
}

#endif
