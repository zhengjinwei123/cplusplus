#pragma once
#ifndef  _BINARY_SEARCH_TREE_H__
#define _BINARY_SEARCH_TREE_H__
#include <iostream>
#include <cassert>
using namespace std;

// 二分查找法，在有序数组arr 中，查找target
// 找到target 就返回target 所在索引，否则返回-1

template<typename T>
int binarySearch(T arr[], int n, T target) {
	// 在 arr[left...right] 之中查找target
	int left = 0, right = n - 1;
	while (left <= right) {
		// middle = (left + right) / 2 中，left + right 可能越界，完美的实现方式如下
		int middle = left + (right - left) / 2;
		if (arr[middle] == target) {
			return middle;
		}
		else if (arr[middle] < target) {
			// 在右半部分[middle +1....right ]
			left = middle + 1;
		}
		else {
			// 在左半部分 [left ...middle - 1]
			right = middle - 1;
		}
	}
	return -1;
}

// 递归方法实现二分法
template<typename T>
int __binarySearch2(T arr[], int left, int right, T target) {
	if (left > right) {
		return -1;
	}

	// middle  = (left + right) / 2 中，left + right 可能越界，完美的实现方式如下
	int middle = left + (right - left) / 2;
	if (arr[middle] == target) {
		return middle;
	}
	else if (arr[middle] < target) {
		// 在右半部分 [middle +1 ... right ]
		return __binarySearch2(arr, middle + 1, right, target);
	}
	else {
		// 在左半部分 [left ... middle - 1]
		return __binarySearch2(arr, left, middle - 1, target);
	}
}

template<typename T>
int binarySearch2(T arr[], int n, T target) {
	return __binarySearch2(arr, 0, n - 1, target);
}

void testBinarySearch();


// 在查找过程中 ,floor 函数用于返回小于target 的 最大值
// ceil 函数用于返回大于target 的最小值


/************************************************************************/
/* 找不到target 的话，返回小于target 的最大值
二分查找法，在有序数组arr 中，查找target
如果找到target ，返回第一个target 相应的索引index
如果没有找到target，返回 比target 小的最大值相应的索引，如果这个最大值有多个，返回最大索引
如果 这个target 比整个数组的最小元素值还要小，则不存在这个target 的 floor 值，返回 -1
*/
/************************************************************************/

template<typename T>
int floor(T arr[], int n, T target) {
	assert(n >= 0);

	// 寻找比 target 小的最大索引
	int left = -1;
	int right = n - 1;
	while (left < right) {
		// 向上取整防止死循环
		int middle = left + (right - left + 1) / 2;
		if (arr[middle] >= target) {
			right = middle - 1;
		}
		else
			left = middle;
	}


	// 第一种情况，该索引+1 就是target, 说明找到target 了，直接返回target 的索引
	if ((left + 1) < n && arr[left + 1] == target) {
		return left + 1;
	}

	// 第二种情况，说明没有找到target ,当前left 索引返回即可
	return left;
}

// 找不到target 的话，返回大于target 的最小值
// 二分查找法，再有序数组arr 中，查找target
// 如果 找到target ,返回最后一个target相应的索引index.
// 如果没有找到target.返回比target 大的最小值的相应的索引index,如果这个值有多个，返回最小的索引
// 如果这个target 比整个数组的最大元素的值还要大，则不存在这个target 的ceil 值吗，返回这个数组元素个数n
template<typename T>
int ceil(T arr[], int n, T target) {
	assert(n >= 0);

	// 寻找比target 大的最小值对应的索引
	int  left = 0; 
	int right = n;

	// 寻找比target 小的最大值的索引
	while (left < right) {
		// 向下取整防止死循环
		int middle = left + (right - left) / 2;

		if (arr[middle] <= target) {
			left = middle + 1;
		}
		else {
			right = middle;
		}
	}

	// 确认最后左右指针相遇了
	assert(left == right);

	// 第一种情况，该索引 -1 就是target,说明找到target了，直接返回该target 的索引
	if ((right - 1) >= 0 && arr[right - 1] == target) {
		return right - 1;
	}

	// 第二种情况，没有找到target, 当前left 索引 返回即可
	return right;
}

void testFloorCeil();
#endif