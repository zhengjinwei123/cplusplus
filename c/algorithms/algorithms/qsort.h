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
		// ѡ���������Ԫ�ض�Ҫ��֮�Ƚϵ�Ԫ�أ�һ��ֱ��ѡ��һ���ͺ�
		T ref = arr[left];
		// ��ʼ����Ԫ�� : arr[left...j] < v ; arr[j+1....i] >v
		int j = left;
		for (int i = left + 1; i <= right; i++) {
			// arr[i] > ref ��ʱ����ҪŲ������Ϊ�Ѿ������Ҳ���
			if (arr[i] < ref) {
				// С�ڲο�Ԫ�صĶ������Ų��
				swap(arr[j+1],arr[i]);
				j++;
			}
		}

		// ���ѲͿ�Ԫ���û���֮��ȥ
		swap(arr[left], arr[j]);
		// ���j ��λ�þ����зֵ�Ӧ���е�λ��
		return j;
	}

	// �� arr[left...right] �ڵ�Ԫ�ؽ��п���������Ҫ�õ��ݹ�
	template<typename T>
	void __quickSort(T arr[], int left, int right) {
		// ����ָ��������ʱ��ֱ���˳�
		if (left >= right) {
			return;
		}

		// ѡ���зֵ㣬 ִ�� __partition ʹ��arr[left...p-1] < arr[p] ; arr[p+1...right] > arr[p]
		int partition = quicksort::__partition(arr, left, right);
		// �ݹ����������������
		quicksort::__quickSort(arr, left, partition - 1);
		quicksort::__quickSort(arr, partition + 1, right);
	}

	template<typename T>
	void quickSort(T arr[], int n) {
		// �����������
		srand((unsigned int)time(NULL));
		quicksort::__quickSort(arr, 0, n - 1);
	}
}

#endif
