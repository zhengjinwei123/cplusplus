#pragma once
/************************************************************************/
/* ����������ΪҪ�����Ĵ����ܶ࣬���������ٶȵ���ѡ������
  ����������ѡ������ͬ
   1. ѡ�������Ǵ�ָ��λ��������
   2. ���������Ǵ�ָ��λ����ǰ��
*/
/************************************************************************/

#ifndef  _INSERT_SORT_H__
#define _INSERT_SORT_H__
#include <iostream>
using namespace std;


namespace insertsort {
	/************************************************************************/
	/* ��������ĺ���˼�룬�Ǵ�С�����������                                                                     */
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
	/* �Ż��Ĳ������򣬼��ٽ�������                                                                     */
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

	// �� arr [l...r] ��Χ�ڵ�������в�������
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