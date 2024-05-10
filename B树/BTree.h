#pragma once
#include<iostream>
#include<vector>
using namespace std;

//����B��
class BTreeNode
{
public:
    //���캯��
	BTreeNode();
    //��������
	~BTreeNode();
    bool isLeaf() const;
    int getNumKeys() const;
    // �������ڻ�ȡָ���������Ĺؼ���
    int getKey(int index) const;
    // ������������ָ���������Ĺؼ���
    void setKey(int index, int key);
    // �����������ӹؼ�������
    void incrementNumKeys();
    // �������ڼ��ٹؼ�������
    void decrementNumKeys();
    // �������ڻ�ȡָ�����������ӽڵ�
    BTreeNode* getChild(int index) const;
    // ������������ָ�����������ӽڵ�
    void setChild(int index, BTreeNode* child);
    //����
    void Insert(int key);
    void AssistInsert(BTreeNode*& root, int key);
    //����
    bool Search(int key);
    bool AssistSearch(vector<BTreeNode*> root, int key);
private:
	vector<int> _key;//����������ؼ���
	vector<BTreeNode*> _children;//����������ֲ�
	int _num;//��Ǽ����ؼ���
};