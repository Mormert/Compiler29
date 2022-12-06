#include "TreeNode.h"
#include "global.h"

TreeNode*
TreeNode::makeLeaf(int type, int value) {
    auto leaf = new TreeNode();
    leaf->type = type;
    leaf->value = value;
    return leaf;
}

TreeNode*
TreeNode::makeNode(int type,
                   TreeNode* a0,
                   TreeNode* a1,
                   TreeNode* a2) {
    auto internalNode = new TreeNode();
    internalNode->type = type;
    internalNode->a0 = a0;
    internalNode->a1 = a1;
    internalNode->a2 = a2;
    return internalNode;
}

void TreeNode::printTree(TreeNode* node) {
    printTree(node, 0);
}

void TreeNode::printTree(TreeNode* node, int level) {
    if(node == nullptr){
        return;
    }

    switch (node->type) {
        case ID:
            printf("%*s", 2*level, "");
            printf("%s\n", symtable[node->value].lexeme);
            break;

        case NUM:
            printf("%*s", 2*level, "");
            printf("%d\n", node->value);
            break;

        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '<':
        case '>':
        case '^':
        case '&':
        case '|':
        case '=':
            printf("%*s", 2*level, "");
            printf("%c\n", (char)node->type);
            printTree(node->a0, level + 1);
            printTree(node->a1, level + 1);
            break;

        case ';':
            printf("%*s", 2*level, "");
            printTree(node->a0, level + 1);
            printf("%*s", 2*level, "");
            printf(";\n");
            printTree(node->a1, level);
            break;
    }
}
