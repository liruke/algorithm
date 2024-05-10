#include"BTree.h"


//���캯��
BTreeNode::BTreeNode():_num(0){}

//��������
BTreeNode::~BTreeNode()
{
	for (int i = 0;i < _children.size();i++)
	{
		delete _children[i];
	}
}

// �������ڼ��ڵ��Ƿ�ΪҶ�ӽڵ�
bool BTreeNode::isLeaf() const
{
	return _children.empty();//���û�к����ˣ���֤��ΪҶ�ӽڵ�
}

// ��ȡ�ؼ���������getter����
int BTreeNode::getNumKeys() const
{
	return _num;
}
// �������ڻ�ȡָ���������Ĺؼ���
int BTreeNode::getKey(int index) const
{
	return _key[index];
}
// ������������ָ���������Ĺؼ���
void BTreeNode::setKey(int index, int key)
{
	_key[index] = key;
}
// �����������ӹؼ�������
void BTreeNode::incrementNumKeys()
{
	_num++;
}
// �������ڼ��ٹؼ�������
void BTreeNode::decrementNumKeys()
{
	_num--;
}
// �������ڻ�ȡָ�����������ӽڵ�
BTreeNode* BTreeNode::getChild(int index) const
{
	return _children[index];
}
// ������������ָ�����������ӽڵ�
void BTreeNode::setChild(int index, BTreeNode* child)
{
	_children[index] = child;
}

void BTreeNode::Insert(int key)
{
    AssistInsert(_children[0], key);
}

void BTreeNode::AssistInsert(BTreeNode*& root, int key) {
    // ������ڵ�Ϊ�գ�����һ���µĸ��ڵ�
    if (root == nullptr)
    {
        root = new BTreeNode();//����һ���ڵ�
        root->setKey(0, key);//���ø��ڵ��ֵ
        root->incrementNumKeys();//���¹ؼ��ֵĸ���
    }
    else
    {
        // ������ڵ���������Ҫ���з���
        if (root->_num == 2)
        {
            //����һ���µĸ��ڵ��һ�����ӽڵ�
            BTreeNode* newRoot = new BTreeNode();
            BTreeNode* newChild = new BTreeNode();
            newChild->setKey(0, root->_key[1]); // �����ڵ�ĵڶ����ؼ����Ƶ��µ��ӽڵ�
            newChild->incrementNumKeys();//���¹ؼ��ָ���
            root->setKey(1, 0); // ��ո��ڵ�ĵڶ����ؼ���
            root->decrementNumKeys();

            // ��ԭ���ڵ�����ӽڵ���Ϊ�¸��ڵ���ӽڵ�
            newRoot->_children[0] = root;
            newRoot->_children[1] = newChild;
            newRoot->incrementNumKeys();
        }

        // �ڷ����ڵ�����µĹؼ���
        int i = root->_num - 1;
        while (i >= 0 && key < root->_key[i])
        {
            root->_key[i + 1] = root->_key[i]; // ���ƹؼ���
            i--;
        }
        root->_key[i + 1] = key; // �����µĹؼ���
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
