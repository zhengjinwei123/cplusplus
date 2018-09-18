#include "stdafx.h"
#include "BST.h"

void shuffle(int arr[], int n) {
	srand(unsigned int(time(NULL)));

	for (int i = n - 1; i >= 0; i--) {
		int x = rand() % (i + 1);
		swap(arr[i], arr[x]);
	}
}

void  testBST() {
	// 遍历
	srand(unsigned int(time(NULL)));
	BST<int, int> bst1 = BST<int, int>();

	// 取n个取值范围在[0...m)的随机整数放进二分搜索树中
	int N = 10;
	int M = 100;
	for (int i = 0; i < N; i++) {
		int key = rand() % M;
		int value = key;
		cout << key << " ";
		bst1.insert(key, value);
	}
	cout << endl;

	// 测试二分搜索树的size()
	cout << "size: " << bst1.size() << endl << endl;

	// 测试二分搜索树的前序遍历 preOrder
	cout << "preOrder: " << endl;
	bst1.preOrder();
	cout << endl;

	// 测试二分搜索树的中序遍历 inOrder 中序排序可用于排序(升序)
	cout << "inOrder: " << endl;
	bst1.inOrder();
	cout << endl;

	// 测试二分搜索树的后序遍历 postOrder 后序遍历可用于释放二叉搜索树
	cout << "postOrder: " << endl;
	bst1.postOrder();
	cout << endl;

	// 层序遍历
	cout << "levelOrder: " << endl;
	bst1.levelOrder();
	cout << endl;

	// 测试 removeMin
	// 输出的元素应该是从小到大排列的
	cout << "Test removeMin: " << endl;
	while (!bst1.isEmpty()) {
		cout << "min: " << bst1.min() << " , ";
		bst1.deleteMin();
		cout << "After deleteMin, size = " << bst1.size() << endl;
	}
	cout << endl;


	for (int i = 0; i < N; i++) {
		int key = rand() % N;
		// 为了后续测试方便,这里value值取和key值一样
		int value = key;
		//cout<<key<<" ";
		bst1.insert(key, value);
	}
	// 注意, 由于随机生成的数据有重复, 所以bst中的数据数量大概率是小于n的

	// 测试 removeMax
	// 输出的元素应该是从大到小排列的
	cout << "Test removeMax: " << endl;
	while (!bst1.isEmpty()) {
		cout << "max: " << bst1.max() << " , ";
		bst1.deleteMax();
		cout << "After deleteMax, size = " << bst1.size() << endl;
	}

	string filename = "ReadMe.txt";
	vector<string> words;

	if (FileOps::readFile(filename, words))
	{
		cout << "There are totally " << words.size() << " words in " << filename << endl;
		cout << endl;

		// 测试BST
		time_t startTime = clock();
		BST<string, int> bst = BST<string, int>();
		vector<string>::iterator iter = words.begin();
		for (iter; iter != words.end(); iter++) {
			int *res = bst.search(*iter);
			if (res == NULL) {
				bst.insert(*iter, 1);
			}
			else {
				(*res)++;
			}
		}

		if (bst.contain("algorithms"))
			cout << "'algorithms' : " << *bst.search("algorithms") << endl;
		else
			cout << "No word 'algorithms' in " << filename << endl;

		time_t  endTime = clock();

		cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
		cout << endl;
	}
}

