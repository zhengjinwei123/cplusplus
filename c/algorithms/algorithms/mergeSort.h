#pragma once
/************************************************************************/
/* �鲢����
*/
/************************************************************************/

#ifndef _MERGE_SORT_H__
#define _MERGE_SORT_H__

#include "insertSort.h"
#include<iostream>
#include <algorithm>
using namespace std;

namespace mergesort {
	// �Ե�ǰ�ֵ�Ԫ�ؽ��й鲢:��arr[left...middle]��arr[mid+1...right]�����ֽ��й鲢��ע�ⶼ�Ǳ�����
	template<typename T>
	void __merge(T arr[], int left, int middle, int right) {
		// ������������
		T *aux = new T[right - left + 1];
		//T aux[right - left + 1];
		// Ԫ��ͳһ������ָ������
		for (int i = left; i <= right; i++) {
			// ע������Ԫ�ص�ƫ������l
			aux[i - left] = arr[i];
		}
		// ��ʼ�ϲ�
		// ����α�
		int i = left;
		// �Ҳ��α�
		int j = middle + 1;
		// kΪҪ��arr�з���Ԫ�ص�λ��
		for (int k = left; k <= right; k++) {
			// ���ж����������һ���Ѿ���ȫ���������ˣ���һ�߻�û��
			if (i > middle) {
				// ˵����ߵ�Ԫ�������ˣ�ֻ�����ұߵ���
				arr[k] = aux[j - left];
				j++;
			}
			else if (j > right) {
				// �ұ�Ԫ���Ѿ������ˣ�ֻ������ߵ���
				arr[k] = aux[i - left];
				i++;
			}
			else if (aux[i - left] < aux[j - left]) {
				// ���� < �Ұ��
				arr[k] = aux[i - left];
				i++;
			}
			else {
				// �Ұ�� < ����
				arr[k] = aux[j - left];
				j++;
			}
		}
		delete[] aux;

	}

	// �ݹ�ʹ�ù鲢���򣬶�arr[left...right]�ķ�Χ�ڵ�Ԫ�ؽ�������ע�����Ҷ��Ǳ�����
	template<typename T>
	void __mergeSort(T arr[], int left, int right) {
		// ������Ԫ���±���ڵ����Ҳ�Ԫ���±꣬˵���鲢��ɣ�ֱ���˳�����
	/*	if (left >= right) {
			return;
		}*/

		// �Ż�
		if (right - left <= 15) {
		   // ��������
			insertsort::insertSortRange(arr, left, right);
			return;
		}

		int middle = (left + right) / 2;
		mergesort::__mergeSort(arr, left, middle);
		mergesort::__mergeSort(arr, middle + 1, right);
		//// merge����
		//mergesort::__merge(arr, left, middle, right);

		// �Ż�
		if (arr[middle] > arr[middle + 1]) {
			mergesort::__merge(arr, left, middle, right);
		}
	}

	// ���ձ����õĺ���
	template<typename T>
	void mergeSort(T arr[], int n) {
		// ����ұ�����
		mergesort::__mergeSort(arr, 0, n - 1);
	}

	// �Ե����ϵĹ鲢
	template<typename T>
	void mergeSortBU(T arr[], int n) {
		// ÿ������һ������ȥ�Ե����Ϲ鲢
		for (int size = 1; size <= n; size += size) {
			// �ؼ���1�� i+ size < n��Ϊ�˷�ֹ���� __merge��ʱ��Խ�� (��Ϊi + size ���ܴ���n��)
			for (int i = 0; i + size < n; i += size + size) {
				// ��arr[i...i+size-1]��arr[i+size...i+size+size-1] ���й鲢
				// �ؼ���2����Ȼǰ�汣֤��1 + size < n������1 + size + size Ҳ���ܳ�������±�n-1,
				//         �˴�ȡ����n-1�ĸ�Сֵ����֤merge��ʱ��ȷʵ��������
				mergesort::__merge(arr, i, i + size - 1, min(i + size + size - 1, n - 1));
			}
		}
	}
};

#endif