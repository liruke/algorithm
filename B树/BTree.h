#pragma once
#include<iostream>
#include<vector>
using namespace std;

//二阶B树
class BTreeNode
{
public:
    //构造函数
	BTreeNode();
    //析构函数
	~BTreeNode();
    bool isLeaf() const;
    int getNumKeys() const;
    // 函数用于获取指定索引处的关键字
    int getKey(int index) const;
    // 函数用于设置指定索引处的关键字
    void setKey(int index, int key);
    // 函数用于增加关键字数量
    void incrementNumKeys();
    // 函数用于减少关键字数量
    void decrementNumKeys();
    // 函数用于获取指定索引处的子节点
    BTreeNode* getChild(int index) const;
    // 函数用于设置指定索引处的子节点
    void setChild(int index, BTreeNode* child);
    //插入
    void Insert(int key);
    void AssistInsert(BTreeNode*& root, int key);
    //查找
    bool Search(int key);
    bool AssistSearch(vector<BTreeNode*> root, int key);
private:
	vector<int> _key;//最多有两个关键字
	vector<BTreeNode*> _children;//最多有三个分叉
	int _num;//标记几个关键字
};