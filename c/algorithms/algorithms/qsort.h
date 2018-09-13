#pragma once
#ifndef _Q_SORT_H__
#define _Q_SORT_H__
#include "stdafx.h"
#include "insertSort.h"
#include <iostream>
#include <ctime>

using namespace std;

namespace quicksort3ways {
	// ��·���������� arr[left...right]
	// ��arr[left...right] ��Ϊ <v =v , >v ������
	// ֮��ݹ��  <v > v �����ּ�����Ϧ��·��������
	template<typename T>
	void __quickSort(T arr[], int left, int right) {
		// ����ָ��������ʱ��ֱ���˳�
		if (left >= right) {
			return;
		}

		// �������зֲ���
		swap(arr[left], arr[rand() % (right - left + 1) + left]);
		// ѡ���������Ԫ�ض�Ҫ��֮�Ƚϵ�Ԫ�أ�һ��ֱ��ѡ��һ���ͺ�
		T ref = arr[left];
		// lt - less than ��������: arr[left+1...lt] < v
	   // gt - greater than ������: arr[gt .... right] > v
		int lt = left;
		int gt = right + 1;

		int i = left + 1;//arr[lt+1 ... i)  == v
		// ��û������֮ǰ��gt �ǲ��ϵ� -- ��
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
		// �����������
		srand((unsigned int)time(NULL));
		__quickSort(arr, 0, n - 1);
	}
};

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

	// ���غ��ʵ��ҷֵ㣬���ս�����£�����p��ʹ��arr[left...p-1] < arr[p] ; arr[p+1...right] > arr[p] 
	// ����Ż���ֹ �����ݴ��ڴ�����ͬ������³�Ϊ 0(N^2)���㷨
	template<typename T>
	int __partition2(T arr[], int left, int right) {
		swap(arr[left], arr[rand() % (right - left + 1) + left]);
		// ѡ���������Ԫ�ض�Ҫ��֮�Ƚϵ�Ԫ�أ�һ��ֱ��ѡ��һ���ͺ�
		T ref = arr[left];
		//��ʼ����Ԫ�أ� arr[left+1...j] <= v ; arr[j...right] >= v
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
			// arr[i] >= v ���� arr[j] <= v��ʱ��ð�i��j��Ԫ�ؽ��н��������
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
		// ���Ѳο�Ԫ���û����м�ȥ
		swap(arr[left], arr[j]);
		// ���j��λ�þ����зֵ�Ӧ���ڵ�λ��
		return j;
	}
	// �� arr[left...right] �ڵ�Ԫ�ؽ��п���������Ҫ�õ��ݹ�
	template<typename T>
	void __quickSort(T arr[], int left, int right) {
		// ����ָ��������ʱ��ֱ���˳�
		if (left >= right) {
			return;
		}

		// �Ż�
		if (right - left <= 15) {
			insertsort::insertSortRange(arr, left, right);
			return;
		}

		// ѡ���зֵ㣬 ִ�� __partition ʹ��arr[left...p-1] < arr[p] ; arr[p+1...right] > arr[p]
		int partition = quicksort::__partition2(arr, left, right);
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
