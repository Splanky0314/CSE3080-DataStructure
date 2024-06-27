#include <stdio.h>
#include <stdlib.h>

typedef struct node *treePointer;
typedef struct node {
    int key;
    treePointer parent;
    treePointer leftChild, rightChild;
} node;

treePointer makenode(int key) {
    treePointer newnode = (treePointer)malloc(sizeof(node));
    newnode->key = key;
    newnode->parent = NULL;
    newnode->leftChild = NULL;
    newnode->rightChild = NULL;
    return newnode;
} 

int insert(treePointer* head, int key) {
    treePointer newnode = makenode(key);
    treePointer ptr = *head;
    // 맨 첫 노드로 삽입하는 경우
    if(*head == NULL) {
        *head = newnode;
        return 1;
    }
    treePointer left = ptr->leftChild, right = ptr->rightChild;
    while(ptr) {
        if(ptr->key == key) {
            printf("cannot construct BST\n");
            return 0;
        }
        // ptr의 오른쪽으로
        else if(ptr->key < key) {
            if(right == NULL) {
                // 삽입
                ptr->rightChild = newnode;
                newnode->parent = ptr;
                break;
            }
            ptr = ptr->rightChild;
        }
        // ptr의 왼쪽으로
        else {
            if(left == NULL) {
                // 삽입
                ptr->leftChild = newnode;
                newnode->parent = ptr;
                break;
            }
            ptr = ptr->leftChild;
        }
        left = ptr->leftChild;
        right = ptr->rightChild;
    }
    return 1;
}

void inorder(treePointer head) {
    if(head) {
        // int i = head->leftChild ? head->leftChild->key : 0;
        // int j = head->rightChild ? head->rightChild->key : 0;
        // printf("\n| %d: %d %d\n", head->key, i, j);
        inorder(head->leftChild);
        printf("%d ", head->key);
        inorder(head->rightChild);
    }
}

void postorder(treePointer head) {
    if(head) {
        postorder(head->leftChild);
        postorder(head->rightChild);
        printf("%d ", head->key);
    }
}

int main() {
    FILE* fin = fopen("input2.txt", "r");
    int n, key;
    treePointer head = NULL;

    fscanf(fin, "%d", &n);
    for(int i=0; i<n; i++) {
        fscanf(fin, "%d", &key);
        if(insert(&head, key) == 0) {
            return 0;
        }
    }

    // Inorder traversal
    printf("Inorder: ");
    inorder(head);
    printf("\n");

    // Postorder traversal
    printf("Postorder: ");
    postorder(head);
    printf("\n");

    fclose(fin);
}