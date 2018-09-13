#pragma once
#ifndef _HEAP_H__
#define _HEAP_H__
#include "stdafx.h"
#include <cassert>
#include <iostream>
using namespace std;

template<typename T>
class MaxHeap {
private:
	T* data;
	int count;
	int capacity;
private:
	// �ϸ�����
	void shiftUp(int k) {
		// k > 1 ����Ϊ�����ڵ�ʱ��û�и��ڵ��ˣ�����Ҫ�ٱȽ���
		while (k > 1 && data[k / 2] < data[k]) {
			swap(data[k / 2], data[k]);
			k = k / 2;
		}
	}

	// �������������һ��Ԫ�����Ƶ�����λ��
	void shiftDown(int k) {
		// �˽ڵ��к��Ӿ�Ҫһֱ������ȥ
		while (2 * k <= count) {
			// ��ȡ�Ӻ����±�
			int j = 2 * k;
			// �����Һ��Ӳ����Һ��Ӵ������ӣ���ô�Һ����и��ڵ㽻��
			if (j + 1 <= count && data[j + 1] > data[j])
				j++;// ѡ���ҽڵ���Ϊ������k���ڵ���н���

					// ���ڵ�������ӽڵ�Ľϴ�ֵ������ô����Ҫ����
			if (data[k] >= data[j])
				break;

			// ���ڵ�С�ں��ӽڵ�Ľϴ�ֵ����ô�ͺͽϴ�ֵ���ӽڵ㽻��
			swap(data[k], data[j]);
			// �ѻ�����ӽڵ���Ϊ���ڵ㣬����������
			k = j;
		}
	}
public:
	// ���캯��
	MaxHeap(int capacity) {
		data = new T[capacity + 1];
		count = 0;
		this->capacity = capacity;
	}

	// ��������
	~MaxHeap()
	{
		delete[] data;
	}

	// ��ȡ���ѵĴ�С
	int size() {
		return count;
	}

	// �ж������Ƿ�Ϊ��
	bool isEmpty() {
		return (count == 0);
	}


	//����Ԫ��
	void insert(T item) {
		// ��ֹ�����++ count Խ��
		assert(count + 1 <= capacity);
		// ������Ԫ�أ�Ԫ������1��֮������++ count ������count ++ ����Ϊ�����±��Ǵ�1 ��ʼ��
		data[++count] = item;
		shiftUp(count);
	}

	// ȡ�����ֵ(���ڵ�Ķ���)
	T popMax() {
		assert(count > 0);
		// ���Ԫ���ǵ�һ��Ԫ��
		T max = data[1];
		// �Ƴ����Ԫ�غ���Ҫ���������Ԫ���Ƶ�����ȥ
		swap(data[1], data[count]);
		count--;
		return max;
	}


	//��ӡ����
	void testPrint() {
		if (size() >= 100) {
			cout << "This print function can only work for less than 100 int";
			return;
		}

		if (typeid(T) != typeid(int)) {
			cout << "This print function can only work for int item";
			return;
		}

		cout << "The max heap size is :" << size() << endl;
		cout << "Data in the max heap: ";
		for (int i = 1; i <= size(); i++) {
			assert(data[i] >= 0 && data[i] < 100);
			cout << data[i] << " ";
		}
		cout << endl;
		cout << endl;

		int n = size();
		int max_level = 0;
		int number_per_level = 1;
		while (n > 0) {
			max_level += 1;
			n -= number_per_level;
			number_per_level *= 2;
		}

		int max_level_number = int(pow(2, max_level - 1));
		int cur_tree_max_level_number = max_level_number;
		int index = 1;
		for (int level = 0; level < max_level; level++) {
			string line1 = string(max_level_number * 3 - 1, ' ');

			int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
			bool isLeft = true;
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++) {
				putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
				isLeft = !isLeft;
			}
			cout << line1 << endl;

			if (level == max_level - 1)
				break;

			string line2 = string(max_level_number * 3 - 1, ' ');
			for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
				putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
			cout << line2 << endl;

			cur_tree_max_level_number /= 2;
		}
	}

private:

	void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft) {

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
		assert(offset + 1 < line.size());
		if (num >= 10) {
			line[offset + 0] = '0' + num / 10;
			line[offset + 1] = '0' + num % 10;
		}
		else {
			if (isLeft)
				line[offset + 0] = '0' + num;
			else
				line[offset + 1] = '0' + num;
		}
	}

	void putBranchInLine(string &line, int index_cur_level, int cur_tree_width) {

		int sub_tree_width = (cur_tree_width - 1) / 2;
		int sub_sub_tree_width = (sub_tree_width - 1) / 2;
		int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
		assert((offset_left + 1) < line.size());
		int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
		assert(offset_right < line.size());

		line[offset_left + 1] = '/';
		line[offset_right + 0] = '\\';
	}
};

#endif