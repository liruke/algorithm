#include"AVL.h"

//构造函数
AVLTree::AVLTree(AVLNode* root) :_root(root) {}

//析构函数
AVLTree::~AVLTree()
{
	clear(_root);
}

//获取最小值
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

//获取最大值
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

//获取高度
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


//中序遍历
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

//前序遍历
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


//后序遍历
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

//获取AVL树的节点的个数
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

//删除所有节点
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

//判空
bool AVLTree::isEmpty()
{
	return _root == nullptr;
}

//左旋
void AVLTree::leftRotate(AVLNode*& node)
{
	AVLNode* right = node->_right;
	node->_right = right->_left;
	right->_left = node;
	node = right;
}
//右旋
void AVLTree::rightRotate(AVLNode*& node)
{
	AVLNode* left = node->_left;
	node->_left = left->_right;
	left->_right = node;
	node = left;
}
//先右旋再左旋
void AVLTree::rightleftRotate(AVLNode*& node)
{
	rightRotate(node->_right);
	leftRotate(node);
}
//先左旋再右旋
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
		//判断平衡因子是否是2，判断是LL型还是LR型
		if (getbalance(node) == 2)
		{
			//LL
			if (getbalance(node->_left) == 1)
			{
				//右旋
				rightRotate(node);
			}
			//LR
			else
			{
				//先左旋再右旋
				leftrightRotate(node);
			}
		}
	}
	else if (node->_key < key)
	{
		//向右边插入
		AssistInsert(key, node->_right);
		//如果是-2，那就是RR型或者是RL型
		if (getbalance(node) == -2)
		{
			//RR
			if (getbalance(node->_right) == -1)
			{
				//左旋
				leftRotate(node);
			}
			//RL
			else
			{
				//先右旋再左旋
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
		//空节点不需要删除直接返回nullptr
		return nullptr;
	}
	//要删除的值小于当前节点的值
	if (node->_key > key)
	{
		//递归左子树
		node->_left = Assistremove(key, node->_left);
	}
	//删除值大于当前节点的值
	else if (node->_key < key)
	{
		//递归右子树
		node->_right = Assistremove(key, node->_right);
	}
	else
	{
		//1.左子树是空树，右子树和左子树都是空树
		if (node->_left == nullptr)
		{
			AVLNode* tmp = node->_right;
			delete node;
			return tmp;
		}
		//只有右子树是空树的时候
		if (node->_right == nullptr)
		{
			AVLNode* tmp = node->_left;
			delete node;
			return tmp;
		}
		//左子树和右子树都不是空树时
		else
		{
			//找到右子树的最小值节点
			AVLNode* min = getMin(node->_right);
			//赋值
			node->_key = min->_key;
			//将删除有左子树和右子树的节点转换为删除末尾的节点
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