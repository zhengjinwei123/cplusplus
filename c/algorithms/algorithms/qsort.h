#pragma once
#ifndef _Q_SORT_H__
#define _Q_SORT_H__
#include "stdafx.h"
#include "insertSort.h"
#include <iostream>
#include <ctime>

using namespace std;

namespace quicksort3ways {
	// 三路快速排序处理 arr[left...right]
	// 将arr[left...right] 分为 <v =v , >v 三部分
	// 之后递归对  <v > v 两部分继续今夕三路快速排序
	template<typename T>
	void __quickSort(T arr[], int left, int right) {
		// 左右指针相遇的时候直接退出
		if (left >= right) {
			return;
		}

		// 下面是切分部分
		swap(arr[left], arr[rand() % (right - left + 1) + left]);
		// 选择后面所有元素都要与之比较的元素，一般直接选第一个就好
		T ref = arr[left];
		// lt - less than ，含义是: arr[left+1...lt] < v
	   // gt - greater than 含义是: arr[gt .... right] > v
		int lt = left;
		int gt = right + 1;

		int i = left + 1;//arr[lt+1 ... i)  == v
		// 还没有相遇之前，gt 是不断的 -- 的
		while (i < gt) {
			if (arr[i] < ref) {
				swap(arr[i], arr[lt + 1]);
				lt++;
				i++;
			}
			else if (arr[i] > ref) {
				swap(arr[i], arr[gt - 1]);
				gt--;
			}
			else {
				i++;
			}
		}

		swap(arr[left], arr[lt]);
		
		quicksort3ways::__quickSort(arr, left, lt - 1);
		quicksort3ways::__quickSort(arr, gt, right);
	}


	template<typename T>
	void quickSort(T arr[], int n) {
		// 设置随机种子
		srand((unsigned int)time(NULL));
		__quickSort(arr, 0, n - 1);
	}
};

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

	// 返回合适的且分点，最终结果如下：返回p，使得arr[left...p-1] < arr[p] ; arr[p+1...right] > arr[p] 
	// 这个优化阻止 在数据存在大量相同的情况下成为 0(N^2)的算法
	template<typename T>
	int __partition2(T arr[], int left, int right) {
		swap(arr[left], arr[rand() % (right - left + 1) + left]);
		// 选择后面所有元素都要与之比较的元素，一般直接选第一个就好
		T ref = arr[left];
		//开始考察元素： arr[left+1...j] <= v ; arr[j...right] >= v
		int i = left + 1;
		int j = right;
		while (true) {
			while (i <= right && arr[i] < ref) {
				i++;
			}
			while (j >= left + 1 && arr[j] > ref) {
				j--;
			}
			if (i > j) {
				break;
			}
			// arr[i] >= v 并且 arr[j] <= v的时候该把i和j的元素进行交换的情况
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
		// 最后把参考元素置换到中间去
		swap(arr[left], arr[j]);
		// 最后j的位置就是切分点应该在的位置
		return j;
	}
	// 对 arr[left...right] 内的元素进行快速排序，需要用到递归
	template<typename T>
	void __quickSort(T arr[], int left, int right) {
		// 左右指针相遇的时候直接退出
		if (left >= right) {
			return;
		}

		// 优化
		if (right - left <= 15) {
			insertsort::insertSortRange(arr, left, right);
			return;
		}

		// 选择切分点， 执行 __partition 使得arr[left...p-1] < arr[p] ; arr[p+1...right] > arr[p]
		int partition = quicksort::__partition2(arr, left, right);
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
