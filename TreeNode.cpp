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

void TreeNode::generateStackMachine(TreeNode *node, StackMachine &sm) {

    if(!node) {
        return;
    }

    int lbl1{};
    int lbl2{};

    switch (node->type) {
        case NUM:
            sm.append({push, node->value});
            return;
        case ID:
            sm.append({rvalue, node->value});
            return;
        case WHILE:
            sm.append({label, lbl1 = lbl++});
            generateStackMachine(node->a0, sm);
            sm.append({gofalse, lbl2 = lbl++});
            generateStackMachine(node->a1, sm);
            sm.append({jump, lbl1});
            sm.append({label, lbl2});
            return;
        case IF:
            generateStackMachine(node->a0, sm);
            if(node->a2 != nullptr){ // If there is an else-clause
                generateStackMachine(node->a0, sm); // there must be a better way to do this, than running the if(x) again?
                sm.append({gofalse, lbl1 = lbl++});
                sm.append({gotrue, lbl2 = lbl++});
                sm.append({label, lbl1});
                generateStackMachine(node->a2,sm);
                sm.append({jump, lbl1 = lbl++});
                sm.append({label, lbl2});
                generateStackMachine(node->a1, sm);
                sm.append({label, lbl1});

            } else { // Regular if
                sm.append({gofalse, lbl1 = lbl++});
                generateStackMachine(node->a1, sm);
                sm.append({label, lbl1});
            }
            return;
        case PRINT:
            generateStackMachine(node->a0, sm);
            sm.append({stackop_write});
            return;
        case READ:
            sm.append({lvalue, node->a0->value});
            generateStackMachine(node->a1, sm);
            sm.append({stackop_read});
            sm.append({assign});
        case ';':
            generateStackMachine(node->a0, sm);
            generateStackMachine(node->a1, sm);
            return;
        case '=':
            sm.append({lvalue, node->a0->value});
            generateStackMachine(node->a1, sm);
            sm.append({assign});
            return;
        case '+':
            generateStackMachine(node->a0, sm);
            generateStackMachine(node->a1, sm);
            sm.append(plus);
            return;
        case '-':
            generateStackMachine(node->a0, sm);
            generateStackMachine(node->a1, sm);
            sm.append(minus);
            return;
        case '*':
            generateStackMachine(node->a0, sm);
            generateStackMachine(node->a1, sm);
            sm.append(times);
            return;
        case '/':
            generateStackMachine(node->a0, sm);
            generateStackMachine(node->a1, sm);
            sm.append(divide);
            return;
        case '<':
            generateStackMachine(node->a0, sm);
            generateStackMachine(node->a1, sm);
            sm.append(lt);
            return;
        case '>':
            generateStackMachine(node->a0, sm);
            generateStackMachine(node->a1, sm);
            sm.append(gt);
            return;
        case '%':
            generateStackMachine(node->a0, sm);
            generateStackMachine(node->a1, sm);
            sm.append(modulo);
            return;
        default:
            printf("ERROR: UNKNOWN NODE TYPE : %c", node->type); exit(0);
    }
}

TreeNode *TreeNode::optimizeTree(TreeNode *node) {
    auto rootNode = new TreeNode;
    optimizeTreeNode(node, rootNode);
    printf("\nOptimized tree:\n\n");
    printTree(rootNode);
    printf("\n");
    return rootNode;
}

void TreeNode::optimizeTreeNode(TreeNode *originalNode, TreeNode *newNode) {

    switch (originalNode->type) {
        case '+':
            // Remove ID + NUM like x + 0, reduce to leaf with only x as value
            if(originalNode->a0->type == ID && originalNode->a1->type == NUM){
                if(originalNode->a1->value == 0){
                    newNode->type = ID;
                    newNode->value = originalNode->a0->value;
                    return;
                }
            }
            // If both are numbers, then reduce to their sum
            if(originalNode->a0->type == NUM && originalNode->a1->type == NUM){
                newNode->type = NUM;
                newNode->value = originalNode->a0->value + originalNode->a1->value;
                return;
            }
            break;
        case '*': // Remove ID * NUM like x * 1, reduce to leaf with only x as value
            if(originalNode->a0->type == ID && originalNode->a1->type == NUM){
                if(originalNode->a1->value == 1){
                    newNode->type = ID;
                    newNode->value = originalNode->a0->value;
                    return;
                }
            }
            // If both are numbers, then reduce to their product
            if(originalNode->a0->type == NUM && originalNode->a1->type == NUM){
                newNode->type = NUM;
                newNode->value = originalNode->a0->value * originalNode->a1->value;
                return;
            }
            break;
        case IF:
            // Pre-evaluate if expressions with constant conditions
            if(!exprContainsVariable(originalNode->a0)){ // Make sure that there is no variable in the IF( xx )
                if(executeTree(originalNode->a0)){ // Execute whatever is inside IF( xx )
                    *newNode = *originalNode->a1; // deep copy
                }else{
                    if(originalNode->a2){
                        *newNode = *originalNode->a2; // deep copy
                    }
                }
                return;
            }

        default:
            break;
    }

    newNode->value = originalNode->value;
    newNode->type = originalNode->type;

    if(originalNode->a0){
        auto new_a0 = new TreeNode;
        newNode->a0 = new_a0;
        optimizeTreeNode(originalNode->a0, new_a0);
    }

    if(originalNode->a1){
        auto new_a1 = new TreeNode;
        newNode->a1 = new_a1;
        optimizeTreeNode(originalNode->a1, new_a1);
    }

    if(originalNode->a2){
        auto new_a2 = new TreeNode;
        newNode->a2 = new_a2;
        optimizeTreeNode(originalNode->a2, new_a2);
    }
}

bool TreeNode::exprContainsVariable(TreeNode *expr) {

    if(!expr){
        return false;
    }

    if(expr->type == ID){
        return true;
    }

    if(exprContainsVariable(expr->a0)){
        return true;
    }

    if(exprContainsVariable(expr->a1)){
        return true;
    }

    return false;

}
