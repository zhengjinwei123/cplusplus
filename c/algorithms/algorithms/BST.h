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
		// 左子节点
		Node* left;
		// 右子节点
		Node* right;
		// 构造函数
		Node(Key key, Value value) {
			// key 是唯一的，不能重复
			this->key = key;
			this->value = value;
			this->left = NULL;
			this->right = NULL;
		}

		Node(Node *node) {
			// key是唯一地，不能重复
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};
	// 根节点
	Node* root;
	// 节点数
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

	//前序遍历
	void preOrder() {
		preOrder(root);
	}

	// 中序遍历
	void inOrder() {
		inOrder(root);
	}

	// 后序遍历
	void postOrder() {
		postOrder(root);
	}

	// 层序遍历，又称广度优先遍历
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
	// 寻找最小的键值
	Key min() {
		assert(count > 0);
		Node *minNode = min(root);
		return minNode->key;
	}
	// 寻找最大的键值
	Key max() {
		assert(count > 0);
		Node* maxNode = max(root);
		return maxNode->key;
	}
	// 删除最小值对应的节点
	void deleteMin() {
		if (root != NULL) {
			root = deleteMin(root);
		}
	}
	// 删除最大值对应的节点
	void deleteMax() {
		if (root != NULL) {
			root = deleteMax(root);
		}
	}
private:
	// 向以node 为根节点的二叉搜索树中，插入节点(key,value)。返回插入新节点的二叉搜索树的根
	Node* insert(Node* node, Key key, Value value) {
		// 处理最基本的事件，即可以退出递归的事件
		if (node == NULL) {
			// 递归到没有子树了，就在这个位置插入。
			count++;
			// 把当前要插入的节点作为根节点返回，一层层递归后会跟新树路径上的节点关系地
			return new Node(key, value);
		}

		if (key < node->key) {
			// 小于根节点的键，往左边子树插入
			node->left = insert(node->left, key, value);
		}
		else if (key > node->key) {
			// 大于根节点的键，往右边子树插入
			node->right = insert(node->right, key, value);
		}
		else {
			// 如果key相等就直接更新(注意二叉搜索树的键是唯一地)
			node->value = value;
		}

		return node;
	}
	// 被递归调用来判断是否包含指定key的函数
	bool contain(Node* node, Key key) {
		// 递归退出条件.最后到达树底，下面没节点了(NULL),返回false
		if (node == NULL) {
			return false;
		}

		if (key > node->key) {
			//大于就在右边找
			return contain(node->right, key);
		}
		else if (key < node->key) {
			// 小于就在左边找
			return contain(node->left, key);
		}
		else {
			// 等于就返回true,代表找到含有这个key 的节点了
			return true;
		}
	}

	// 在以node 为根的二叉搜索树中查找key 对应的value
	Value* search(Node* node, Key key) {
		// 递归退出条件.最后到达树底，返回NULL
		if (node == NULL) {
			return  NULL;
		}

		if (key > node->key) {
			// 大于就在右边找
			return search(node->right, key);
		}
		else if (key < node->key) {
			// 小于就在左边找
			return search(node->left, key);
		}
		else {
			// 等于就返回true,代表找到含有这个key地节点了,返回Value的地址
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

	// 在以node 为根的二叉搜索树中，返回最小键值的点
	Node* min(Node* node) {
		// 没有左子节点的时候就到了最小点了
		if (node->left == NULL) {
			return node;
		}
		return min(node->left);
	}

	// 在以node 为根的二叉搜索树中，返回最大键值的点
	Node* max(Node* node) {
		// 没有右子节点的时候就到了最大点了
		if (node->right == NULL) {
			return node;
		}
		return max(node->right);
	}

	// 删除 以node 为根的子树中的最小值
	Node* deleteMin(Node* node) {
		if (node->left == NULL) {
			// 没有左节点了，就要看看右节点是否存在
			Node * rightNode = node->right;
			delete node;
			count--;
			return rightNode;
		}

		node->left = deleteMin(node->left);
		return node;
	}

	// 删除以node 为根节点的子树中的最大值
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

	// 删除指定节点作为树的根的二叉搜索树中键值为key的节点
	// 返回删除节点后的新的二叉搜索树的根
	// 删除最小节点后的替换值实际从删除节点的右子树中找最小节点即可
	Node* deleteNode(Node* node, Key key) {
		// 节点为null 时，就可以退出了
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
