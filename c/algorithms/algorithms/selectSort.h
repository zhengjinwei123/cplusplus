#pragma once
#ifndef _SELECT_SORT_H__
#define _SELECT_SORT_H__
#include <string>
#include <iostream>
using namespace std;

namespace selectsort {
	void selectSort(int arr[], int n);

	template<typename T>
	void selectSortT(T arr[], int n) {
		for (int i = 0; i < n; ++i) {
			int minIndex = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < arr[minIndex]) {
					minIndex = j;
				}
			}

			swap(arr[i], arr[minIndex]);
		}
	}

	struct Student {
		string name;
		int score;

		bool operator < (const Student &otherStudent) {
			return score != otherStudent.score ? score > otherStudent.score : name < otherStudent.name;
		}

		friend ostream& operator<<(ostream &os, const Student &student) {
			os << "Student: " << student.name << " " << student.score << endl;
			return os;
		}
	};
};


#endif

