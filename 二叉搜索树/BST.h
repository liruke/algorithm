#pragma once
#include<iostream>
using namespace std;
class TreeNode
{
	friend class BST;
public:
	TreeNode(int val):_val(val),_left(nullptr),_right(nullptr){}
private:
	int _val;
	TreeNode* _left;
	TreeNode* _right;
};
class BST
{
public:
	BST();
	bool Search(int val);
	bool SearchNode(TreeNode* Node, int val);
	void Insert(int val);
	TreeNode* InsertNode(TreeNode* Node, int val);
	void Delete(int val);
	TreeNode* AssistDelete(TreeNode* Node, int val);
	TreeNode* FindPrev(TreeNode* root, TreeNode* Node);
	int GetMin();
	TreeNode* AssistGetMin(TreeNode*Node);
	int GetMax();
	TreeNode* AssistGetMax(TreeNode* Node);
	void PostOrder();
	void AssistPostOrder(TreeNode* Node);
	void InOrder();
	void AssistInOrder(TreeNode* Node);
	void PrevOrder();
	void AssistPrevOrder(TreeNode* Node);
private:
	TreeNode* _root;
};