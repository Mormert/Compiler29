#include "TreeNode.h"
#include "global.h"

#include <iostream>

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

        case WHILE:
            printf("%*s", 2*level, "");
            printf("while");
            TreeNode::printTree(node->a0, level+1);
            TreeNode::printTree(node->a1, level+1);
            break;

        case IF:
            printf("%*s", 2*level, "");
            printf("if");
            TreeNode::printTree(node->a0, level+1);
            TreeNode::printTree(node->a1, level+1);
            TreeNode::printTree(node->a2, level+1);
            break;

        case PRINT:
            printf("%*s", 2*level, "");
            printf("print");
            TreeNode::printTree(node->a0, level+1);
            break;

        case READ:
            printf("%*s", 2*level, "");
            printf("read");
            TreeNode::printTree(node->a0, level+1);
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

int TreeNode::executeTree(TreeNode *node) {
    if(!node){
        return 0;
    }

    int v = 0;
    switch (node->type) {
        case NUM:
            return node->value;
        case ID:
            return symtable[node->value].value;
        case WHILE:
            while(executeTree(node->a0))
            {
                executeTree(node->a1);
            }
            return 0;
        case IF:
            if(executeTree(node->a0)){
                executeTree(node->a1);
            }else if(node->a2 != nullptr){
                executeTree(node->a2);
            }
            return 0;
        case PRINT:
            printf("%d\n", executeTree(node->a0));
            return 0;
        case READ:
            std::cout << "\nENTER INPUT FOR READ (" << symtable[node->a0->value].lexeme << "):" << std::flush;
            std::cin >> v;
            return symtable[node->a0->value].value = v;
        case ';':
            executeTree(node->a0);
            return executeTree(node->a1);
        case '=':
            v = executeTree(node->a1);
            return symtable[node->a0->value].value = v;
        case '+':
            return executeTree(node->a0) + executeTree(node->a1);
        case '-':
            return executeTree(node->a0) - executeTree(node->a1);
        case '*':
            return executeTree(node->a0) * executeTree(node->a1);
        case '/':
            return executeTree(node->a0) / executeTree(node->a1);
        case '<':
            return executeTree(node->a0) < executeTree(node->a1);
        case '>':
            return executeTree(node->a0) > executeTree(node->a1);
        case '%':
            return executeTree(node->a0) % executeTree(node->a1);
        default:
            printf("ERROR: UNKNOWN NODE TYPE : %c", node->type); exit(0);
    }
    return 0;

}
