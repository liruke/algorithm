#include"BST.h"


BST::BST():_root(nullptr){}
bool BST::Search(int val)
{
	return SearchNode(_root, val);
}
bool BST::SearchNode(TreeNode* Node, int val)
{
	if (Node == nullptr)
	{
		return false;
	}
	if (Node->_val == val)
	{
		return true;
	}
	else if (val < Node->_val)
	{
		return SearchNode(Node->_left, val);
	}
	else
	{
		return SearchNode(Node->_right, val);
	}
}
void BST::Insert(int val)
{
	_root = InsertNode(_root, val);
}
TreeNode* BST::InsertNode(TreeNode* Node, int val)
{
	if (Node == nullptr)
	{
		return new TreeNode(val);//����һ���ڵ�
	}
	if (Node->_val < val)
	{
		Node->_right = InsertNode(Node->_right, val);
	}
	else if (Node->_val > val)
	{
		Node->_left = InsertNode(Node->_left, val);
	}
	return Node;
}

void BST::Delete(int val)
{
	_root = AssistDelete(_root, val);
}

TreeNode* BST::FindPrev(TreeNode* root, TreeNode* Node)
{
	if (root->_left == Node || root->_right == Node)
	{
		return root;
	}
	if (root->_val < Node->_val)
	{
		FindPrev(root->_right, Node);
	}
	if (root->_val > Node->_val)
	{
		FindPrev(root->_left, Node);
	}
}
TreeNode* BST::AssistDelete(TreeNode* node, int val)
{
	if (node == nullptr)
	{
		return node;
	}
	// �ҵ�Ҫɾ���Ľڵ�
	if (val < node->_val)
	{
		node->_left = AssistDelete(node->_left, val);
	}
	else if (val > node->_val)
	{
		node->_right = AssistDelete(node->_right, val);
	}
	else
	{
		// Ҫɾ���Ľڵ���һ����û�к���
		if (node->_left == nullptr)
		{
			TreeNode* temp = node->_right;
			delete node;
			return temp;
		}
		else if (node->_right == nullptr)
		{
			TreeNode* temp = node->_left;
			delete node;
			return temp;
		}

		// Ҫɾ���Ľڵ�����������
		// �ҵ�Ҫɾ���ڵ�ĺ�̽ڵ㣨�������е���С�ڵ㣩
		TreeNode* temp = AssistGetMin(node->_right);
		// ����̽ڵ��ֵ���Ƶ�Ҫɾ���Ľڵ���
		node->_val = temp->_val;
		// �ݹ�ɾ����̽ڵ�
		node->_right = AssistDelete(node->_right, temp->_val);
	}

	return node;
}
int BST::GetMin()
{
	if (_root == nullptr)
	{
		return INT_MAX;
	}
	TreeNode* min = AssistGetMin(_root);
	return min->_val;
}
TreeNode* BST::AssistGetMin(TreeNode* Node)
{
	if (Node->_left == nullptr)
	{
		return Node;
	}
	return AssistGetMin(Node->_left);
}

int BST::GetMax()
{
	if (_root == nullptr)
	{
		return INT_MAX;
	}
	TreeNode* max = AssistGetMax(_root);
	return max->_val;
}
TreeNode* BST::AssistGetMax(TreeNode* Node)
{
	if (Node->_right == nullptr)
	{
		return Node;
	}
	return AssistGetMax(Node->_right);
}

void BST::PostOrder()
{
	AssistPostOrder(_root);
}
void BST::AssistPostOrder(TreeNode* Node)
{
	if (Node == nullptr)
	{
		return;
	}
	AssistPostOrder(Node->_left);
	AssistPostOrder(Node->_right);
	cout << Node->_val << ' ';
}
void BST::InOrder()
{
	AssistInOrder(_root);
}
void BST::AssistInOrder(TreeNode* Node)
{
	if (Node == nullptr)
	{
		return;
	}
	AssistInOrder(Node->_left);
	cout << Node->_val << ' ';
	AssistInOrder(Node->_right);
}
void BST::PrevOrder()
{
	AssistPrevOrder(_root);
}
void BST::AssistPrevOrder(TreeNode* Node)
{
	if (Node == nullptr)
	{
		return;
	}
	cout << Node->_val << ' ';
	AssistPrevOrder(Node->_left);
	AssistPrevOrder(Node->_right);
}

