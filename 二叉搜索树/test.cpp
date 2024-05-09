#include"BST.h"

int main()
{
    BST bst;
    bst.Insert(5);
    bst.Insert(3);
    bst.Insert(7);
    bst.Insert(1);
    bst.Insert(4);
    bst.InOrder();
    cout << endl;
    cout << bst.GetMin() << endl;
    cout << bst.GetMax() << endl;
    bst.Delete(4);
    bst.InOrder();
	return 0;
}