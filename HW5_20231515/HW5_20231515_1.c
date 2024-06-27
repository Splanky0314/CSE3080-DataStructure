#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
    int key;
    treePointer parent;
    treePointer leftChild, rightChild;
} node;

// 같은 key를 가지는 노드가 존재하는지 search
int search(treePointer head, int target) {
    if(head) {
        // int i = head->leftChild ? head->leftChild->key : 0;
        // int j = head->rightChild ? head->rightChild->key : 0;
        // printf("\n| %d: %d %d\n", head->key, i, j);
        if(head->key == target) return 1;
        else {
            return search(head->leftChild, target) || search(head->rightChild, target);
        }
    }
    return 0;
}

treePointer createNode(int key) {
    treePointer newNode = (treePointer)malloc(sizeof(node));
    newNode->key = key;
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

void insert(treePointer** root, int key, int *n) {
    treePointer *heap = *root;
    // 해당 key를 가진 노드가 이미 존재하는지 확인
    if(search(heap[1], key)) {
        printf("Exist number\n");
        return;
    }
    
    treePointer newnode = createNode(key);
    int i = ++(*n);
    heap[i] = newnode;
    if(i != 1) {
        newnode->parent = heap[i/2];
        if(heap[i/2]->leftChild == NULL) {
            heap[i/2]->leftChild = newnode;
        }
        else {
            heap[i/2]->rightChild = newnode;
        }
    }

    // root로 올라가면서 swap
    while((i!=1) && (key > heap[i/2]->key)) {
        heap[i]->key = heap[i/2]->key;
        i /= 2;
    }
    heap[i]->key = key;
    printf("Insert %d\n", key);
}

void delete(treePointer** root, int *n) {
    treePointer *heap = *root;
    if(*n == 0) {
        printf("The heap is empty\n");
        return;
    }

    int parent = 1, child = 2;
    int delkey = heap[1]->key;
    int tarkey = heap[(*n)]->key;
    // swap
    heap[1]->key = heap[(*n)]->key;

    if(*n != 1) {
        if((*n)%2 == 0) {
            heap[(*n)/2]->leftChild = NULL;
        }
        else heap[(*n)/2]->rightChild = NULL;
    }
    
    free(heap[(*n)]);
    heap[(*n)--] = NULL;

    if(*n == 0) {
        printf("Delete %d\n", delkey);
        return;
    }
    
    // root에서부터 내려가면서 swap
    while(child <= *n) {
        // left, right중 키 값이 큰 것으로 child 선택
        if(child < *n && heap[child]->key < heap[child+1]->key) {
            child++;
        }
        // child보다 key가 큰 경우
        if(tarkey >= heap[child]->key) break;
        // child보다 key가 작은 경우
        heap[parent]->key = heap[child]->key;
        parent = child;
        child *=2;
    }
    heap[parent]->key = tarkey;
    printf("Delete %d\n", delkey);
}

int main() {
    char c;
    int key, n = 0;
    treePointer *heap = (treePointer*)malloc(sizeof(treePointer)*1000);
    FILE* fin = fopen("input1.txt", "r");
    fscanf(fin, "%c", &c);
    while(c != 'q') {
        if(c == 'i') {
            fscanf(fin, "%d", &key);
            insert(&heap, key, &n);
        }
        else if(c == 'd') {
            delete(&heap, &n);
        }
        fscanf(fin, "%c", &c);

        // printf("_------\n");
        // search(heap[1], n);
        // printf("--------\n");
    }
    free(heap);
    fclose(fin);
}