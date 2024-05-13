#include"AVL.h"

//���캯��
AVLTree::AVLTree(AVLNode* root) :_root(root) {}

//��������
AVLTree::~AVLTree()
{
	clear(_root);
}

//��ȡ��Сֵ
int AVLTree::getMin()
{
	if (_root == nullptr)
	{
		return INT_MIN;
	}
	AVLNode* root = _root;
	while (root->_left != nullptr)
	{
		root = root->_left;
	}
	return root->_key;
}

//��ȡ���ֵ
int AVLTree::getMax()
{
	if (_root == nullptr)
	{
		return INT_MAX;
	}
	AVLNode* root = _root;
	while (root->_right != nullptr)
	{
		root = root->_right;
	}
	return root->_key;
}

//��ȡ�߶�
int AVLTree::getHeight()
{
	return AssistgetHeight(_root);
}
int AVLTree::AssistgetHeight(AVLNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return root->_height;
}


//�������
void AVLTree::AssistinOrderTraversal(AVLNode* _root)
{
	if (_root == nullptr)
	{
		return;
	}
	AssistinOrderTraversal(_root->_left);
	cout << _root->_key << ' ';
	AssistinOrderTraversal(_root->_right);
}
void AVLTree::inOrderTraversal()
{
	AssistinOrderTraversal(_root);
}

//ǰ�����
void AVLTree::preOrderTraversal()
{
	AssistpreOrderTraversal(_root);
}
void AVLTree::AssistpreOrderTraversal(AVLNode* root)
{
	if (root == nullptr)
	{
		return;
	}
	cout << root->_key << ' ';
	AssistpreOrderTraversal(root->_left);
	AssistpreOrderTraversal(root->_right);
}


//�������
void AVLTree::AssistpostOrderTraversal(AVLNode* root)
{
	if (root == nullptr)
	{
		return;
	}
	AssistpostOrderTraversal(root->_left);
	AssistpostOrderTraversal(root->_right);
	cout << root->_key << ' ';
}
void AVLTree::postOrderTraversal()
{
	AssistpostOrderTraversal(_root);
}

//��ȡAVL���Ľڵ�ĸ���
int AVLTree::AssistgetSize(AVLNode* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	return AssistgetSize(root->_left) + AssistgetSize(root->_right) + 1;
}
int AVLTree::getSize()
{
	return AssistgetSize(_root);
}

//ɾ�����нڵ�
void AVLTree::clear(AVLNode* node)
{
	if (node == nullptr)
	{
		return;
	}
	clear(node->_left);
	clear(node->_right);
	delete node;
}

//�п�
bool AVLTree::isEmpty()
{
	return _root == nullptr;
}

//����
void AVLTree::leftRotate(AVLNode*& node)
{
	AVLNode* right = node->_right;
	node->_right = right->_left;
	right->_left = node;
	node = right;
}
//����
void AVLTree::rightRotate(AVLNode*& node)
{
	AVLNode* left = node->_left;
	node->_left = left->_right;
	left->_right = node;
	node = left;
}
//������������
void AVLTree::rightleftRotate(AVLNode*& node)
{
	rightRotate(node->_right);
	leftRotate(node);
}
//������������
void AVLTree::leftrightRotate(AVLNode*& node)
{
	leftRotate(node->_left);
	rightRotate(node);
}


int AVLTree::getbalance(AVLNode* root)
{
	if (root->_left == nullptr && root->_right == nullptr)
	{
		return 0;
	}
	else if (root->_left == nullptr)
	{
		return AssistgetHeight(root->_right);
	}
	else if (root->_right == nullptr)
	{
		return AssistgetHeight(root->_left);
	}
	return AssistgetHeight(root->_left) - AssistgetHeight(root->_right);
}
AVLNode* AVLTree::AssistInsert(int key, AVLNode*& node)
{
	if (node == nullptr)
	{
		node = new AVLNode(key, nullptr, nullptr);
		return node;
	}
  	else if (node->_key > key)
	{
		AssistInsert(key, node->_left);
		//�ж�ƽ�������Ƿ���2���ж���LL�ͻ���LR��
		if (getbalance(node) == 2)
		{
			//LL
			if (getbalance(node->_left) == 1)
			{
				//����
				rightRotate(node);
			}
			//LR
			else
			{
				//������������
				leftrightRotate(node);
			}
		}
	}
	else if (node->_key < key)
	{
		//���ұ߲���
		AssistInsert(key, node->_right);
		//�����-2���Ǿ���RR�ͻ�����RL��
		if (getbalance(node) == -2)
		{
			//RR
			if (getbalance(node->_right) == -1)
			{
				//����
				leftRotate(node);
			}
			//RL
			else
			{
				//������������
				rightleftRotate(node);
			}
		}
	}
	node->_height = max(AssistgetHeight(node->_left), AssistgetHeight(node->_right)) + 1;
	return node;
}

void AVLTree::Insert(int key)
{
	_root = AssistInsert(key, _root);
}

AVLNode* AVLTree::getMin(AVLNode* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	while (node->_left != nullptr)
	{
		node = node->_left;
	}
	return node;
}
AVLNode* AVLTree::Assistremove(int key, AVLNode*& node)
{
	if (node == nullptr)
	{
		//�սڵ㲻��Ҫɾ��ֱ�ӷ���nullptr
		return nullptr;
	}
	//Ҫɾ����ֵС�ڵ�ǰ�ڵ��ֵ
	if (node->_key > key)
	{
		//�ݹ�������
		node->_left = Assistremove(key, node->_left);
	}
	//ɾ��ֵ���ڵ�ǰ�ڵ��ֵ
	else if (node->_key < key)
	{
		//�ݹ�������
		node->_right = Assistremove(key, node->_right);
	}
	else
	{
		//1.�������ǿ����������������������ǿ���
		if (node->_left == nullptr)
		{
			AVLNode* tmp = node->_right;
			delete node;
			return tmp;
		}
		//ֻ���������ǿ�����ʱ��
		if (node->_right == nullptr)
		{
			AVLNode* tmp = node->_left;
			delete node;
			return tmp;
		}
		//�������������������ǿ���ʱ
		else
		{
			//�ҵ�����������Сֵ�ڵ�
			AVLNode* min = getMin(node->_right);
			//��ֵ
			node->_key = min->_key;
			//��ɾ�������������������Ľڵ�ת��Ϊɾ��ĩβ�Ľڵ�
			node->_right = Assistremove(min->_key, node->_right);
		}
	}
	node->_height = max(AssistgetHeight(node->_left), AssistgetHeight(node->_right)) + 1;
	int balance = getbalance(node);
	if (balance == 2)
	{
		if (getbalance(node->_left) == 1)
		{
			rightRotate(node);
		}
		else
		{
			leftrightRotate(node);
		}
	}
	else if (balance == -2)
	{
		if (getbalance(node->_right) == -1)
		{
			leftRotate(node);
		}
		else
		{
			rightleftRotate(node);
		}
	}
	return node;
}
void AVLTree::remove(int key)
{
	_root = Assistremove(key, _root);
}

bool AVLTree::search(int key, AVLNode* node)
{
	if (node == nullptr)
	{
		return false;
	}
	if (node->_key == key)
	{
		return true;
	}
	if (node->_key > key)
	{
		return search(key, node->_left);
	}
	else
	{
		return search(key, node->_right);
	}
}

bool AVLTree::search(int key)
{
	return search(key, _root); 
}