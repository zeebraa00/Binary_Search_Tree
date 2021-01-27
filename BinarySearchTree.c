#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
}Node;

Node* root = NULL;

Node* insertNode(Node *root, int value) {
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        root->left = NULL;
        root->right = NULL;
        root->value = value;
        return root;
    } else {
        if (root->value > value) {
            root->left = insertNode(root->left, value);
        } else {
            root->right = insertNode(root->right, value);
        }
    }
    return root;
}

Node* findMinNode(Node* root) {
    Node* tmp = root;
    while (tmp->left != NULL) {
        tmp = tmp->left;
    }
    return tmp;
}

Node* findMaxNode(Node* root) {
    Node* tmp = root;
    while (tmp->right != NULL) {
        tmp = tmp->right;
    }
    return tmp;
}

Node* deleteNode(Node* root, int value) {
    Node* tmp = NULL;
    if (root == NULL) {
        return NULL;
    }

    if (root->value > value) {
        root->left = deleteNode(root->left, value);
    } else if (root->value < value) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->right != NULL && root->left != NULL) { // 자식 노드가 둘 다 있을 때
            // 현재 노드를 지우면 다른 노드로 대체해야함
            // 현재 노드 기준으로 오른쪽에 있는 노드 중 가장 작은 노드로 대체하면 됨
            
            tmp = findMinNode(root->right);
            root->value = tmp->value;
            root->right = deleteNode(root->right, tmp->value); // 대체한 노드를 또 삭제해줌 (재귀)
        } else {
            tmp = (root->left == NULL) ? root->right : root->left;
            free(root);
            return tmp;
        }
    }
    return root;
}

Node* searchNode(Node* root, int value) {
    if (root == NULL) {
        return NULL;
    }

    if(root->value == value) {
        return root;
    } else if (root->value > value) {
        searchNode(root->left, value);
    } else {
        searchNode(root->right, value);
    }
}

void printBST(Node* root) { // preorder traversal
    if (root == NULL) {
        return;
    }

    printf("%d ", root->value);
    printBST(root->left);
    printBST(root->right);
}

int main() {
    root = insertNode(root, 8);
    root = insertNode(root, 10);
    root = insertNode(root, 3);
    root = insertNode(root, 6);
    root = insertNode(root, 1);
    root = insertNode(root, 7);
    root = insertNode(root, 4);
    root = insertNode(root, 14);
    root = insertNode(root, 13);

    printBST(root);
    puts("");

    deleteNode(root, 3);

    printBST(root);
    puts("");

    return 0;
}