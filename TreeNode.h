#ifndef COMPILERS_01_29_TREENODE_H
#define COMPILERS_01_29_TREENODE_H

#include <memory>
#include "StackMachine.h"

class TreeNode {
public:

    TreeNode() = default;

    static TreeNode* makeLeaf(int type, int value);
    static TreeNode* makeNode(int type,
                              TreeNode* a0 = nullptr,
                              TreeNode* a1 = nullptr,
                              TreeNode* a2 = nullptr);

    static void printTree(TreeNode* node);

    static TreeNode* optimizeTree(TreeNode* node);

    static int executeTree(TreeNode* node);

    static void generateStackMachine(TreeNode* node, StackMachine& smOut);

private:
    // If leaf:
    int type{}, value{};

    // If internal node:
    TreeNode* a0{}, *a1{}, *a2{};

    static void printTree(TreeNode* node, int level);

    static void optimizeTreeNode(TreeNode* originalNode, TreeNode* newNode);

    static bool exprContainsVariable(TreeNode* expr);

    static inline int lbl{};

    // copy ctor
    TreeNode(const TreeNode& t){
        type = t.type;
        value = t.value;
        if(t.a0){
            a0 = new TreeNode();
            *a0 = *t.a0;
        }

        if(t.a1){
            a1 = new TreeNode();
            *a1 = *t.a1;
        }

        if(t.a2){
            a2 = new TreeNode();
            *a2 = *t.a2;
        }

    }
};


#endif //COMPILERS_01_29_TREENODE_H
