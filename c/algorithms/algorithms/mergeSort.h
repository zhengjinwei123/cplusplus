#pragma once
/************************************************************************/
/* 归并排序
*/
/************************************************************************/

#ifndef _MERGE_SORT_H__
#define _MERGE_SORT_H__

#include "insertSort.h"
#include<iostream>
#include <algorithm>
using namespace std;

namespace mergesort {
	// 对当前轮的元素进行归并:将arr[left...middle]和arr[mid+1...right]两部分进行归并。注意都是闭区间
	template<typename T>
	void __merge(T arr[], int left, int middle, int right) {
		// 声明辅助数组
		T *aux = new T[right - left + 1];
		//T aux[right - left + 1];
		// 元素统一拷贝到指定数组
		for (int i = left; i <= right; i++) {
			// 注意数组元素的偏移量是l
			aux[i - left] = arr[i];
		}
		// 开始合并
		// 左侧游标
		int i = left;
		// 右侧游标
		int j = middle + 1;
		// k为要在arr中放入元素的位置
		for (int k = left; k <= right; k++) {
			// 先判断特殊情况，一边已经快全部被拿走了，另一边还没动
			if (i > middle) {
				// 说明左边的元素排完了，只能用右边地了
				arr[k] = aux[j - left];
				j++;
			}
			else if (j > right) {
				// 右边元素已经排完了，只能用左边的了
				arr[k] = aux[i - left];
				i++;
			}
			else if (aux[i - left] < aux[j - left]) {
				// 左半边 < 右半边
				arr[k] = aux[i - left];
				i++;
			}
			else {
				// 右半边 < 左半边
				arr[k] = aux[j - left];
				j++;
			}
		}
		delete[] aux;

	}

	// 递归使用归并排序，对arr[left...right]的范围内的元素进行排序，注意左右都是闭区间
	template<typename T>
	void __mergeSort(T arr[], int left, int right) {
		// 如果左侧元素下标大于等于右侧元素下标，说明归并完成，直接退出即可
	/*	if (left >= right) {
			return;
		}*/

		// 优化
		if (right - left <= 15) {
		   // 插入排序
			insertsort::insertSortRange(arr, left, right);
			return;
		}

		int middle = (left + right) / 2;
		mergesort::__mergeSort(arr, left, middle);
		mergesort::__mergeSort(arr, middle + 1, right);
		//// merge操作
		//mergesort::__merge(arr, left, middle, right);

		// 优化
		if (arr[middle] > arr[middle + 1]) {
			mergesort::__merge(arr, left, middle, right);
		}
	}

	// 最终被调用的函数
	template<typename T>
	void mergeSort(T arr[], int n) {
		// 左闭右闭区间
		mergesort::__mergeSort(arr, 0, n - 1);
	}

	// 自底向上的归并
	template<typename T>
	void mergeSortBU(T arr[], int n) {
		// 每次增加一倍步幅去自底向上归并
		for (int size = 1; size <= n; size += size) {
			// 关键点1： i+ size < n是为了防止下面 __merge的时候越界 (因为i + size 可能大于n了)
			for (int i = 0; i + size < n; i += size + size) {
				// 对arr[i...i+size-1]和arr[i+size...i+size+size-1] 进行归并
				// 关键点2：虽然前面保证了1 + size < n，但是1 + size + size 也可能超过最大下标n-1,
				//         此处取它和n-1的更小值来保证merge的时候确实是两部分
				mergesort::__merge(arr, i, i + size - 1, min(i + size + size - 1, n - 1));
			}
		}
	}
};

#endif