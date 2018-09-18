#pragma once
#ifndef _BST_H__
#define _BST_H__

#include "fileOps.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <queue>
#include <cassert>
using namespace std;

template<typename Key, typename Value>
class BST {
private:
	struct Node
	{
		Key key;
		Value value;
		// ���ӽڵ�
		Node* left;
		// ���ӽڵ�
		Node* right;
		// ���캯��
		Node(Key key, Value value) {
			// key ��Ψһ�ģ������ظ�
			this->key = key;
			this->value = value;
			this->left = NULL;
			this->right = NULL;
		}

		Node(Node *node) {
			// key��Ψһ�أ������ظ�
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};
	// ���ڵ�
	Node* root;
	// �ڵ���
	int count;

public:
	BST() {
		root = NULL;
		count = 0;
	}

	~BST() {
		// TODO
		destroy(root);
	}

	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}

	void insert(Key key, Value value) {
		root = insert(root, key, value);
	}

	bool contain(Key key) {
		return contain(root, key);
	}

	Value* search(Key key) {
		return search(root, key);
	}

	//ǰ�����
	void preOrder() {
		preOrder(root);
	}

	// �������
	void inOrder() {
		inOrder(root);
	}

	// �������
	void postOrder() {
		postOrder(root);
	}

	// ����������ֳƹ�����ȱ���
	void levelOrder() {
		queue<Node*> queue;
		queue.push(root);

		while (!queue.empty()) {
			Node* node = queue.front();
			queue.pop();

			cout << node->key << endl;
			if (node->left != NULL) {
				queue.push(node->left);
			}
			if (node->right != NULL) {
				queue.push(node->right);
			}
		}
	}
	// Ѱ����С�ļ�ֵ
	Key min() {
		assert(count > 0);
		Node *minNode = min(root);
		return minNode->key;
	}
	// Ѱ�����ļ�ֵ
	Key max() {
		assert(count > 0);
		Node* maxNode = max(root);
		return maxNode->key;
	}
	// ɾ����Сֵ��Ӧ�Ľڵ�
	void deleteMin() {
		if (root != NULL) {
			root = deleteMin(root);
		}
	}
	// ɾ�����ֵ��Ӧ�Ľڵ�
	void deleteMax() {
		if (root != NULL) {
			root = deleteMax(root);
		}
	}
private:
	// ����node Ϊ���ڵ�Ķ����������У�����ڵ�(key,value)�����ز����½ڵ�Ķ����������ĸ�
	Node* insert(Node* node, Key key, Value value) {
		// ������������¼����������˳��ݹ���¼�
		if (node == NULL) {
			// �ݹ鵽û�������ˣ��������λ�ò��롣
			count++;
			// �ѵ�ǰҪ����Ľڵ���Ϊ���ڵ㷵�أ�һ���ݹ��������·���ϵĽڵ��ϵ��
			return new Node(key, value);
		}

		if (key < node->key) {
			// С�ڸ��ڵ�ļ����������������
			node->left = insert(node->left, key, value);
		}
		else if (key > node->key) {
			// ���ڸ��ڵ�ļ������ұ���������
			node->right = insert(node->right, key, value);
		}
		else {
			// ���key��Ⱦ�ֱ�Ӹ���(ע������������ļ���Ψһ��)
			node->value = value;
		}

		return node;
	}
	// ���ݹ�������ж��Ƿ����ָ��key�ĺ���
	bool contain(Node* node, Key key) {
		// �ݹ��˳�����.��󵽴����ף�����û�ڵ���(NULL),����false
		if (node == NULL) {
			return false;
		}

		if (key > node->key) {
			//���ھ����ұ���
			return contain(node->right, key);
		}
		else if (key < node->key) {
			// С�ھ��������
			return contain(node->left, key);
		}
		else {
			// ���ھͷ���true,�����ҵ��������key �Ľڵ���
			return true;
		}
	}

	// ����node Ϊ���Ķ����������в���key ��Ӧ��value
	Value* search(Node* node, Key key) {
		// �ݹ��˳�����.��󵽴����ף�����NULL
		if (node == NULL) {
			return  NULL;
		}

		if (key > node->key) {
			// ���ھ����ұ���
			return search(node->right, key);
		}
		else if (key < node->key) {
			// С�ھ��������
			return search(node->left, key);
		}
		else {
			// ���ھͷ���true,�����ҵ��������key�ؽڵ���,����Value�ĵ�ַ
			return &(node->value);
		}
	}
	void preOrder(Node* node) {
		if (node != NULL) {
			cout << node->key << endl;
			preOrder(node->left);
			preOrder(node->right);
		}
	}

	void inOrder(Node * node) {
		if (node != NULL) {
			inOrder(node->left);
			cout << node->key << endl;
			inOrder(node->right);
		}
	}

	void postOrder(Node* node) {
		if (node != NULL) {
			postOrder(node->left);
			postOrder(node->right);
			cout << node->key << endl;
		}
	}

	void destroy(Node* node) {
		if (node != NULL) {
			destroy(node->left);
			destroy(node->right);
			delete node;
			count--;
		}
	}

	// ����node Ϊ���Ķ����������У�������С��ֵ�ĵ�
	Node* min(Node* node) {
		// û�����ӽڵ��ʱ��͵�����С����
		if (node->left == NULL) {
			return node;
		}
		return min(node->left);
	}

	// ����node Ϊ���Ķ����������У���������ֵ�ĵ�
	Node* max(Node* node) {
		// û�����ӽڵ��ʱ��͵���������
		if (node->right == NULL) {
			return node;
		}
		return max(node->right);
	}

	// ɾ�� ��node Ϊ���������е���Сֵ
	Node* deleteMin(Node* node) {
		if (node->left == NULL) {
			// û����ڵ��ˣ���Ҫ�����ҽڵ��Ƿ����
			Node * rightNode = node->right;
			delete node;
			count--;
			return rightNode;
		}

		node->left = deleteMin(node->left);
		return node;
	}

	// ɾ����node Ϊ���ڵ�������е����ֵ
	Node* deleteMax(Node* node) {
		if (node->right == NULL) {
			Node* leftNode = node->left;
			delete node;
			count--;
			return leftNode;
		}
		node->right = deleteMax(node->right);
		return node;
	}

	// ɾ��ָ���ڵ���Ϊ���ĸ��Ķ����������м�ֵΪkey�Ľڵ�
	// ����ɾ���ڵ����µĶ����������ĸ�
	// ɾ����С�ڵ����滻ֵʵ�ʴ�ɾ���ڵ��������������С�ڵ㼴��
	Node* deleteNode(Node* node, Key key) {
		// �ڵ�Ϊnull ʱ���Ϳ����˳���
		if (node == NULL) {
			return NULL;
		}
		if (key < node->key) {
			node->left = deleteNode(node->left, key);
			return node;
		}
		else if (key > node->key) {
			node->right = deleteNode(node->right, key);
			return node;
		}
		else {
			if (node->left == NULL) {
				Node * rightNode = node->right;
				delete node;
				count--;
				return rightNode;
			}
			if (node->right == NULL) {
				Node* leftNode = node->left;
				delete node;
				count--;
				return leftNode;
			}

			Node* successor = new Node(min(node->right));
			count++;
			successor->right = deleteMin(node->right);
			successor->left = node->left;
			delete node;
			count--;
			return successor;
		}
	}
};

void shuffle(int arr[], int n);
void  testBST();

#endif
