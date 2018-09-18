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
	// ����
	srand(unsigned int(time(NULL)));
	BST<int, int> bst1 = BST<int, int>();

	// ȡn��ȡֵ��Χ��[0...m)����������Ž�������������
	int N = 10;
	int M = 100;
	for (int i = 0; i < N; i++) {
		int key = rand() % M;
		int value = key;
		cout << key << " ";
		bst1.insert(key, value);
	}
	cout << endl;

	// ���Զ�����������size()
	cout << "size: " << bst1.size() << endl << endl;

	// ���Զ�����������ǰ����� preOrder
	cout << "preOrder: " << endl;
	bst1.preOrder();
	cout << endl;

	// ���Զ������������������ inOrder �����������������(����)
	cout << "inOrder: " << endl;
	bst1.inOrder();
	cout << endl;

	// ���Զ����������ĺ������ postOrder ��������������ͷŶ���������
	cout << "postOrder: " << endl;
	bst1.postOrder();
	cout << endl;

	// �������
	cout << "levelOrder: " << endl;
	bst1.levelOrder();
	cout << endl;

	// ���� removeMin
	// �����Ԫ��Ӧ���Ǵ�С�������е�
	cout << "Test removeMin: " << endl;
	while (!bst1.isEmpty()) {
		cout << "min: " << bst1.min() << " , ";
		bst1.deleteMin();
		cout << "After deleteMin, size = " << bst1.size() << endl;
	}
	cout << endl;


	for (int i = 0; i < N; i++) {
		int key = rand() % N;
		// Ϊ�˺������Է���,����valueֵȡ��keyֵһ��
		int value = key;
		//cout<<key<<" ";
		bst1.insert(key, value);
	}
	// ע��, ����������ɵ��������ظ�, ����bst�е����������������С��n��

	// ���� removeMax
	// �����Ԫ��Ӧ���ǴӴ�С���е�
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

		// ����BST
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

