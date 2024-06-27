#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void insert(treePointer* head, int key) {
    treePointer newnode = makenode(key);
    treePointer ptr = *head;
    // 맨 첫 노드로 삽입하는 경우
    if(*head == NULL) {
        *head = newnode;
    }
    else {
        treePointer left = ptr->leftChild, right = ptr->rightChild;
        while(ptr) {
            if(ptr->key == key) {
                printf("Exist number\n");
                return;
            }
            // ptr의 오른쪽으로
            else if(ptr->key < key) {
                if(right == NULL) {
                    ptr->rightChild = newnode;
                    newnode->parent = ptr;
                    break;
                }
                ptr = ptr->rightChild;
            }
            // ptr의 왼쪽으로
            else {
                if(left == NULL) {
                    ptr->leftChild = newnode;
                    newnode->parent = ptr;
                    break;
                }
                ptr = ptr->leftChild;
            }
            left = ptr->leftChild;
            right = ptr->rightChild;
        }
    }
    printf("Push %d\n", key);
}

void printtop(treePointer head) {
    // tree가 비어 있는 경우
    if(head == NULL) {
        printf("The queue is empty\n");
        return;
    }
    while(head->rightChild) {
        head = head->rightChild;
    }
    printf("The top is %d\n", head->key);
}

void popnode(treePointer* head) {
    treePointer pre = NULL;
    treePointer tmp = *head;
    
    if(*head == NULL) {
        printf("The queue is empty\n");
        return;
    }

    while(tmp->rightChild) {
        pre = tmp;
        tmp = tmp->rightChild;
    }
    // head node를 pop해야 하는경우
    if(pre == NULL) {
        *head = tmp->leftChild;
    }
    else pre->rightChild = NULL;
    printf("Pop %d\n", tmp->key);
    free(tmp);
}

int main() {
    char input[10]; int key;
    treePointer head = NULL;
    FILE* fin = fopen("input3.txt", "r");

    fscanf(fin, "%s", input);
    while(strcmp(input, "q") != 0) {
        if(strcmp(input, "push") == 0) {
            fscanf(fin, "%d", &key);
            insert(&head, key);
        }
        else if(strcmp(input, "top") == 0) {
            printtop(head);
        }
        else if(strcmp(input, "pop") == 0) {
            popnode(&head);
        } 
        fscanf(fin, "%s", input);
    }

    fclose(fin);
}