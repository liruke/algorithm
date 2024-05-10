#include"BTree.h"


//构造函数
BTreeNode::BTreeNode():_num(0){}

//析构函数
BTreeNode::~BTreeNode()
{
	for (int i = 0;i < _children.size();i++)
	{
		delete _children[i];
	}
}

// 函数用于检查节点是否为叶子节点
bool BTreeNode::isLeaf() const
{
	return _children.empty();//如果没有孩子了，则证明为叶子节点
}

// 获取关键字数量的getter函数
int BTreeNode::getNumKeys() const
{
	return _num;
}
// 函数用于获取指定索引处的关键字
int BTreeNode::getKey(int index) const
{
	return _key[index];
}
// 函数用于设置指定索引处的关键字
void BTreeNode::setKey(int index, int key)
{
	_key[index] = key;
}
// 函数用于增加关键字数量
void BTreeNode::incrementNumKeys()
{
	_num++;
}
// 函数用于减少关键字数量
void BTreeNode::decrementNumKeys()
{
	_num--;
}
// 函数用于获取指定索引处的子节点
BTreeNode* BTreeNode::getChild(int index) const
{
	return _children[index];
}
// 函数用于设置指定索引处的子节点
void BTreeNode::setChild(int index, BTreeNode* child)
{
	_children[index] = child;
}

void BTreeNode::Insert(int key)
{
    AssistInsert(_children[0], key);
}

void BTreeNode::AssistInsert(BTreeNode*& root, int key) {
    // 如果根节点为空，创建一个新的根节点
    if (root == nullptr)
    {
        root = new BTreeNode();//创建一个节点
        root->setKey(0, key);//设置根节点的值
        root->incrementNumKeys();//更新关键字的个数
    }
    else
    {
        // 如果根节点已满，需要进行分裂
        if (root->_num == 2)
        {
            //创造一个新的根节点和一个孩子节点
            BTreeNode* newRoot = new BTreeNode();
            BTreeNode* newChild = new BTreeNode();
            newChild->setKey(0, root->_key[1]); // 将根节点的第二个关键字移到新的子节点
            newChild->incrementNumKeys();//更新关键字个数
            root->setKey(1, 0); // 清空根节点的第二个关键字
            root->decrementNumKeys();

            // 将原根节点和新子节点作为新根节点的子节点
            newRoot->_children[0] = root;
            newRoot->_children[1] = newChild;
            newRoot->incrementNumKeys();
        }

        // 在非满节点插入新的关键字
        int i = root->_num - 1;
        while (i >= 0 && key < root->_key[i])
        {
            root->_key[i + 1] = root->_key[i]; // 后移关键字
            i--;
        }
        root->_key[i + 1] = key; // 插入新的关键字
        root->incrementNumKeys();
    }
}


bool BTreeNode::Search(int key)
{
    return AssistSearch(_children, key);
}
bool BTreeNode::AssistSearch(vector<BTreeNode*> root, int key)
{
}
