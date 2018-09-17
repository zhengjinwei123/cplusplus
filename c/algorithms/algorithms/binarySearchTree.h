#pragma once
#ifndef  _BINARY_SEARCH_TREE_H__
#define _BINARY_SEARCH_TREE_H__
#include <iostream>
#include <cassert>
using namespace std;

// ���ֲ��ҷ�������������arr �У�����target
// �ҵ�target �ͷ���target �������������򷵻�-1

template<typename T>
int binarySearch(T arr[], int n, T target) {
	// �� arr[left...right] ֮�в���target
	int left = 0, right = n - 1;
	while (left <= right) {
		// middle = (left + right) / 2 �У�left + right ����Խ�磬������ʵ�ַ�ʽ����
		int middle = left + (right - left) / 2;
		if (arr[middle] == target) {
			return middle;
		}
		else if (arr[middle] < target) {
			// ���Ұ벿��[middle +1....right ]
			left = middle + 1;
		}
		else {
			// ����벿�� [left ...middle - 1]
			right = middle - 1;
		}
	}
	return -1;
}

// �ݹ鷽��ʵ�ֶ��ַ�
template<typename T>
int __binarySearch2(T arr[], int left, int right, T target) {
	if (left > right) {
		return -1;
	}

	// middle  = (left + right) / 2 �У�left + right ����Խ�磬������ʵ�ַ�ʽ����
	int middle = left + (right - left) / 2;
	if (arr[middle] == target) {
		return middle;
	}
	else if (arr[middle] < target) {
		// ���Ұ벿�� [middle +1 ... right ]
		return __binarySearch2(arr, middle + 1, right, target);
	}
	else {
		// ����벿�� [left ... middle - 1]
		return __binarySearch2(arr, left, middle - 1, target);
	}
}

template<typename T>
int binarySearch2(T arr[], int n, T target) {
	return __binarySearch2(arr, 0, n - 1, target);
}

void testBinarySearch();


// �ڲ��ҹ����� ,floor �������ڷ���С��target �� ���ֵ
// ceil �������ڷ��ش���target ����Сֵ


/************************************************************************/
/* �Ҳ���target �Ļ�������С��target �����ֵ
���ֲ��ҷ�������������arr �У�����target
����ҵ�target �����ص�һ��target ��Ӧ������index
���û���ҵ�target������ ��target С�����ֵ��Ӧ�����������������ֵ�ж���������������
��� ���target �������������СԪ��ֵ��ҪС���򲻴������target �� floor ֵ������ -1
*/
/************************************************************************/

template<typename T>
int floor(T arr[], int n, T target) {
	assert(n >= 0);

	// Ѱ�ұ� target С���������
	int left = -1;
	int right = n - 1;
	while (left < right) {
		// ����ȡ����ֹ��ѭ��
		int middle = left + (right - left + 1) / 2;
		if (arr[middle] >= target) {
			right = middle - 1;
		}
		else
			left = middle;
	}


	// ��һ�������������+1 ����target, ˵���ҵ�target �ˣ�ֱ�ӷ���target ������
	if ((left + 1) < n && arr[left + 1] == target) {
		return left + 1;
	}

	// �ڶ��������˵��û���ҵ�target ,��ǰleft �������ؼ���
	return left;
}

// �Ҳ���target �Ļ������ش���target ����Сֵ
// ���ֲ��ҷ�������������arr �У�����target
// ��� �ҵ�target ,�������һ��target��Ӧ������index.
// ���û���ҵ�target.���ر�target �����Сֵ����Ӧ������index,������ֵ�ж����������С������
// ������target ��������������Ԫ�ص�ֵ��Ҫ���򲻴������target ��ceil ֵ�𣬷����������Ԫ�ظ���n
template<typename T>
int ceil(T arr[], int n, T target) {
	assert(n >= 0);

	// Ѱ�ұ�target �����Сֵ��Ӧ������
	int  left = 0; 
	int right = n;

	// Ѱ�ұ�target С�����ֵ������
	while (left < right) {
		// ����ȡ����ֹ��ѭ��
		int middle = left + (right - left) / 2;

		if (arr[middle] <= target) {
			left = middle + 1;
		}
		else {
			right = middle;
		}
	}

	// ȷ���������ָ��������
	assert(left == right);

	// ��һ������������� -1 ����target,˵���ҵ�target�ˣ�ֱ�ӷ��ظ�target ������
	if ((right - 1) >= 0 && arr[right - 1] == target) {
		return right - 1;
	}

	// �ڶ��������û���ҵ�target, ��ǰleft ���� ���ؼ���
	return right;
}

void testFloorCeil();
#endif