#pragma once
#pragma once
#include<iostream>
using namespace std;

class AVLNode
{
	friend class AVLTree;
public:
	AVLNode(int key, AVLNode* left, AVLNode* right, int hight = 0)
	{
		_key = key;
		_left = left;
		_right = right;
		_height = hight;
	}
private:
	AVLNode* _left;
	AVLNode* _right;
	int _key;
	int _height;
};


class AVLTree
{
public:
	AVLTree(AVLNode* root = nullptr);
	~AVLTree();

	int getbalance(AVLNode* root);

	AVLNode* AssistInsert(int key, AVLNode*& node);
	void Insert(int key);

	void leftRotate(AVLNode*& node);
	void rightRotate(AVLNode*& node);
	void rightleftRotate(AVLNode*& node);
	void leftrightRotate(AVLNode*& node);

	AVLNode* Assistremove(int key, AVLNode*& node);
	void remove(int key);

	bool search(int key);
	bool search(int key, AVLNode* node);

	int getMin();
	AVLNode* getMin(AVLNode* node);
	int getMax();
	int AssistgetHeight(AVLNode* root);
	int getHeight();

	void inOrderTraversal();
	void AssistinOrderTraversal(AVLNode* _root);
	void preOrderTraversal();
	void AssistpreOrderTraversal(AVLNode* _root);
	void postOrderTraversal();
	void AssistpostOrderTraversal(AVLNode* _root);

	int getSize();
	int AssistgetSize(AVLNode* root);
	void clear(AVLNode* node);
	bool isEmpty();
private:
	AVLNode* _root;
};