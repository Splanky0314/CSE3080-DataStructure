#include <stdio.h>
#include <stdlib.h>

typedef struct poly* poly_pointer;

typedef struct poly {
    int exp;
    int coef;
    poly_pointer link;
} poly;


int pinsert(poly_pointer* head, poly_pointer newpoly) {
    if(newpoly->coef == 0) {
        free(newpoly);
        return -1;
    }

    poly_pointer ptr = *head;
    poly_pointer pre = NULL;
    if(*head == NULL) { // 첫 노드!
        *head = newpoly;
        return 0;
    }
    for(; ptr!=NULL; pre=ptr, ptr=ptr->link) {
        // 해당 exp인 항이 이미 존재하는 경우
        if(ptr->exp == newpoly->exp) {
            if(ptr->coef + newpoly->coef == 0) {
                free(newpoly);
                // delnode;
                poly_pointer delnode = ptr;
                pre->link = ptr->link;
                ptr = pre;
                free(delnode);
                return -2;
            }
            ptr->coef += newpoly->coef;
            free(newpoly);
            return -1;
        }
        else if(ptr->exp < newpoly->exp) {
            if(pre == NULL) { // 맨 앞 노드로 삽입
                newpoly->link = (*head)->link;
                *head = newpoly; 
            }
            else {
                newpoly->link = pre->link;
                pre->link = newpoly;
            }
            return 0;
        }
    }
    // 맨 마지막 노드로 삽입
    pre->link = newpoly;
    return 0;
} 

int pmult(poly_pointer* head, poly_pointer a, poly_pointer b) {
    int exp, coef;
    int elem = 0;
    for(poly_pointer ptra = a; ptra!=NULL; ptra=ptra->link) {
        for(poly_pointer ptrb = b; ptrb!=NULL; ptrb=ptrb->link) {
            poly_pointer newpoly = (poly_pointer)malloc(sizeof(poly));
            newpoly->exp = (ptra->exp)+(ptrb->exp);
            newpoly->coef = (ptra->coef)*(ptrb->coef);
            newpoly->link = NULL;
            elem += pinsert(head, newpoly);
        }
    }
    // printf("elemd: %d\n", elem);
    return elem;
}

int pread(char* filename, poly_pointer* head, poly_pointer* tail) {
    FILE* fin = fopen(filename, "r");
    int elem;
    int coef, exp;
    fscanf(fin, "%d", &elem);
    for(int i=0; i<elem; i++) {
        poly_pointer newnode = (poly_pointer)malloc(sizeof(poly));
        fscanf(fin, "%d %d", &coef, &exp);
        newnode->coef = coef;
        newnode->exp = exp;
        newnode->link = NULL;
        if(*head == NULL) {
            *head = newnode;
            *tail = newnode;
        }
        else {
            (*tail)->link = newnode;
            *tail = newnode;
        }
    }
    fclose(fin);
    return elem;
}

void pwrite(poly_pointer head, int elem) {
    FILE* fout = fopen("d.txt", "w");

    poly_pointer ptr = head;
    fprintf(fout, "%d\n", elem);
    // printf("%d\n", elem);
    for(; ptr!=NULL; ptr=ptr->link) {
        // printf("%d %d\n", ptr->coef, ptr->exp); // for test
        fprintf(fout, "%d %d\n", ptr->coef, ptr->exp);
    }

    fclose(fout);
}

void freepoly(poly_pointer head) {
    poly_pointer ptr = head->link;
    poly_pointer delnode = head;
    while(ptr != NULL) {
        delnode = ptr;
        ptr = ptr->link;
        free(delnode);
    }
}

int main() {
    int aelem, belem, delem;
    poly_pointer ahead = NULL;
    poly_pointer atail = NULL;
    poly_pointer bhead = NULL;
    poly_pointer btail = NULL;
    poly_pointer dhead = NULL;

    aelem = pread("a.txt", &ahead, &atail);
    belem = pread("b.txt", &bhead, &btail);
    
    delem = aelem*belem+pmult(&dhead, ahead, bhead);

    pwrite(dhead, delem);
    
    freepoly(ahead);
    freepoly(bhead);
    freepoly(dhead);
}