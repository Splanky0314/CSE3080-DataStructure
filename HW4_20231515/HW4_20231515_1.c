#include <stdio.h>
#include <stdlib.h>

typedef struct matrix* matrix_pointer;

typedef struct matrix {
    int row;
    int col;
    int value;
    matrix_pointer link;
} matrix;

matrix_pointer hdnode = NULL;
matrix_pointer hdnode_t = NULL;

void insert_matrix(matrix_pointer node) {
    // printf("insert 호출: %d %d %d\n", node->row, node->col, node->value);
    matrix_pointer ptr = hdnode_t;
    matrix_pointer pre = NULL;
    if(hdnode_t == NULL) { // linked list의 첫 노드로 삽입되는 경우
        hdnode_t = node;
        return;
    }
    for(; ptr!=NULL; pre=ptr, ptr=ptr->link) {
        if(ptr->row > node->row) {
            if(pre == NULL) { // 맨 앞의 노드로 삽입되는 경우
                node->link = ptr;
                hdnode_t = node;
                return;
            }
            node->link = pre->link;
            pre->link = node;
            return;
        }
        else if(ptr->row == node->row) {
            if(ptr->col > node->col) {
                if(pre == NULL) { // 맨 앞의 노드로 삽입되는 경우
                    node->link = ptr;
                    hdnode_t = node;
                    return;
                }
                node->link = pre->link;
                pre->link = node;
                return;
            }
        }
    }
    if(ptr == NULL) { // linked list의 맨 마지막 노드로 삽입되는 경우
        pre->link = node;
    }
}

matrix_pointer mtranspose(matrix_pointer node) {
    matrix_pointer ptr = node;
    for(; ptr!=NULL; ptr=ptr->link) {
        matrix_pointer newmat = (matrix_pointer)malloc(sizeof(matrix));
        // row와 col 바꾸기
        newmat->row = ptr->col;
        newmat->col = ptr->row;
        newmat->value = ptr->value;
        newmat->link = NULL;
        insert_matrix(newmat);
    }

    return hdnode_t;
}

// 동적 할당된 메모리 해제
void freenode(matrix_pointer head) {
    matrix_pointer ptr = head;
    matrix_pointer del = NULL;
    while(ptr != NULL) {
        del = ptr;
        ptr = ptr->link;
        free(del);
    }
    hdnode_t = NULL;
}

void readfile(char* filename, int *row, int *col, int *elem) {
    FILE* fin = fopen("input.txt", "r");
    matrix_pointer ptr = hdnode;
    int a, b, c;

    if(fin == NULL) printf("Error");

    fscanf(fin, "%d %d %d", row, col, elem);
    for(int i=0; i<*elem; i++) {
        matrix_pointer newnode = (matrix_pointer)malloc(sizeof(matrix));
        fscanf(fin, "%d %d %d", &a, &b, &c);
        newnode->row = a;
        newnode->col = b;
        newnode->value = c;
        newnode->link = NULL;
        if(hdnode == NULL) { // 맨 첫 노드인 경우
            // printf("fir: %d %d %d\n", a,b,c);
            hdnode = newnode;
            ptr = hdnode;
        }
        else { // 맨 뒤에 newnode 삽입
            // printf("add: %d %d %d\n", a,b,c);
            ptr->link = newnode;
            ptr = ptr->link;
        }
    }

    fclose(fin);
}

void writefile(char* filename, int row, int col, int elem) {
    FILE* fout = fopen(filename, "w");

    fprintf(fout, "%d %d %d\n", col, row, elem);
    for(matrix_pointer ptr = hdnode_t; ptr!=NULL; ptr=ptr->link) {
        fprintf(fout, "%d %d %d\n", ptr->row, ptr->col, ptr->value);
    }

    fclose(fout);
}

int main() {
    int row, col, elem;
    readfile("input.txt", &row, &col, &elem);

    // printf("hdnode 출력\n");
    // for(matrix_pointer ptr = hdnode; ptr!=NULL; ptr=ptr->link) {
    //     printf("%d %d %d\n", ptr->row, ptr->col, ptr->value);
    // }

    mtranspose(hdnode);

    writefile("output.txt", row, col, elem);

    // 동적할당된 메모리 해제
    freenode(hdnode);
    freenode(hdnode_t);
}