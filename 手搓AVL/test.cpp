#include "AVL.h" // ���� AVLTree.h ������ AVL ���������Ͷ���

int main() {
    AVLTree avlTree;

    // ����һЩ�ڵ�
    avlTree.Insert(10);
     avlTree.Insert(5);
    avlTree.Insert(15);
    avlTree.Insert(3);
    avlTree.Insert(8);
    avlTree.Insert(12);
    avlTree.Insert(17);

    // ������������������3 5 8 10 12 15 17
    std::cout << "Inorder traversal: ";
    avlTree.inOrderTraversal();
    std::cout << std::endl;

    // ɾ���ڵ� 5
    avlTree.remove(5);

    // ������������������3 8 10 12 15 17
    std::cout << "Inorder traversal after removing 5: ";
    avlTree.inOrderTraversal();
    std::cout << std::endl;

    // ɾ���ڵ� 12
    avlTree.remove(12);

    // ������������������3 8 10 15 17
    std::cout << "Inorder traversal after removing 12: ";
    avlTree.inOrderTraversal();
    std::cout << std::endl;
    return 0;
}
