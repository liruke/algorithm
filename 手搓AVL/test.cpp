#include "AVL.h" // 假设 AVLTree.h 包含了 AVL 树的声明和定义

int main() {
    AVLTree avlTree;

    // 插入一些节点
    avlTree.Insert(10);
     avlTree.Insert(5);
    avlTree.Insert(15);
    avlTree.Insert(3);
    avlTree.Insert(8);
    avlTree.Insert(12);
    avlTree.Insert(17);

    // 中序遍历，期望输出：3 5 8 10 12 15 17
    std::cout << "Inorder traversal: ";
    avlTree.inOrderTraversal();
    std::cout << std::endl;

    // 删除节点 5
    avlTree.remove(5);

    // 中序遍历，期望输出：3 8 10 12 15 17
    std::cout << "Inorder traversal after removing 5: ";
    avlTree.inOrderTraversal();
    std::cout << std::endl;

    // 删除节点 12
    avlTree.remove(12);

    // 中序遍历，期望输出：3 8 10 15 17
    std::cout << "Inorder traversal after removing 12: ";
    avlTree.inOrderTraversal();
    std::cout << std::endl;
    return 0;
}
