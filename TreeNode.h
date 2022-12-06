#ifndef COMPILERS_01_29_TREENODE_H
#define COMPILERS_01_29_TREENODE_H

#include <memory>

class TreeNode {
public:
    static TreeNode* makeLeaf(int type, int value);
    static TreeNode* makeNode(int type,
                              TreeNode* a0 = nullptr,
                              TreeNode* a1 = nullptr,
                              TreeNode* a2 = nullptr);

    static void printTree(TreeNode* node);

private:
    // If leaf:
    int type, value;

    // If internal node:
    TreeNode* a0, *a1, *a2;

    static void printTree(TreeNode* node, int level);

};


#endif //COMPILERS_01_29_TREENODE_H
