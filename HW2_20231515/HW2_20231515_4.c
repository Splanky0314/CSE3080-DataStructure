#include <stdio.h>
#include <stdlib.h>

typedef struct array {
    char* lastname;
    char* firstname;
    struct array* link;
} array;

// 문자열 a와 b의 정렬 우선순위를 리턴한다.
// lastname를 먼저 비교한 후 firstname를 비교한다.
// a가 b보다 우선순위가 높은 경우 return 1
// a와 b의 우선순위가 같은 경우 return 0
// b가 a보다 우선순위가 높은 경우 return -1
int compare(array *a, array *b) {
    // lastname 비교
    char* alast = a->lastname;
    char* blast = b->lastname;
    for(int i=0; ; i++) {
        if(alast[i]=='\0' && blast[i]=='\0') break;
        else if(alast[i]=='\0') return 1; // a가 더 우선순위
        else if(blast[i]=='\0') return -1; // b가 더 우선순위

        if(alast[i]<blast[i]) return 1;
        else if(alast[i]>blast[i]) return -1;
    }

    // firstname 비교(lastname이 동일한 경우)
    char* afirst = a->firstname;
    char* bfirst = b->firstname;
    for(int i=0; ; i++) {
        if(afirst[i]=='\0' && bfirst[i]=='\0') break;
        else if(afirst[i]=='\0') return 1; // a가 더 우선순위
        else return -1; // b가 더 우선순위

        if(afirst[i]>bfirst[i]) return 1;
        else if(afirst[i]<bfirst[i]) return -1;
    }
    return 0; // 완전 동일
}

// 문자열 s의 길이를 리턴한다.
int length(char* s) {
    int i;
    for(i=0; s[i]!='\0'; i++) {}
    return i;
}

// b의 문자열을 a에 복사한다.
void copy(char* a, char* b) {
    for(int i=0; i<length(b)+1; i++) {
        a[i] = b[i];
    }
}

// 학생의 이름을 argument로 받아 array를 생성하고 메모리 동적 할당을 진행한다.
array* createarray(char *lastname, char *firstname) {
    array *newarray = (array*)malloc(sizeof(array));
    char* newlast = (char*)malloc(sizeof(char)*(length(lastname)+1));
    char* newfirst = (char*)malloc(sizeof(char)*(length(firstname)+1));
    copy(newlast, lastname);
    copy(newfirst, firstname);
    newarray->lastname = newlast;
    newarray->firstname = newfirst;
    newarray->link = NULL;
    return newarray;
}

// 학생명을 입력받아 array를 생성하고 이름순으로 정렬된 위치에 linked list에 추가한다.
void sort_and_insert(array** base, char *lastname, char *firstname) {
    array* newarray = createarray(lastname, firstname);

    if(*base == NULL) { // 아예 0
        *base = newarray;
        return;
    }
    array* tmp = *base;
    array* pre = NULL;
    for(; tmp; pre = tmp, tmp=tmp->link) {
        if(compare(newarray, tmp)>=0) { 
            if(pre==NULL) { // 맨 앞 삽입
                *base = newarray;
                newarray->link = tmp;
            }
            else { // 중간에 삽입
                pre->link = newarray;
                newarray->link = tmp;
            }
            
            return;
        }
    }
    // 맨 마지막 삽입
    pre->link = newarray;
}

void printarray(array* base) {
    array* tmp = base;
    for(; tmp; tmp=tmp->link) {
        printf("%s %s\n", tmp->lastname, tmp->firstname);
    }
}

void freearray(array* base) {
    array* tmp = NULL;
    while(!base) {
        tmp = base->link;
        free(base->firstname);
        free(base->lastname);
        free(base);
        base = tmp;
    }
}

int main() {
    int n;
    array* base = NULL;
    char c;
    char *str;
    int strlen = 0;
    char *lastname;
    char *firstname;
    FILE *fp = fopen("student.txt", "r");

    char test[1000];
    fscanf(fp, "%d", &n);
    for(int i=0; i<n; i++) {
        str = (char*)malloc(sizeof(char));
        strlen = 0;

        fscanf(fp, " %c", &c);
        while(c!=EOF) {
            // printf("%c", c);
            if(c==' ') {
                break;
            }
            else {
                //printf("%c", c);
                str[strlen] = c;
                str = (char*)realloc(str, sizeof(char)*(++strlen));
                fscanf(fp, "%c", &c);
            }
        }
        str[strlen] = '\0';
        lastname = (char*)malloc(sizeof(char)*(strlen+1));
        copy(lastname, str);
        free(str);

        str = (char*)malloc(sizeof(char));
        strlen = 0;
        while(fscanf(fp, "%c", &c)!=EOF) {
            //printf("%c", c);
            if(c=='\n') {
                break;
            }
            else {
                //printf("%c", c);
                str[strlen] = c;
                str = (char*)realloc(str, sizeof(char)*(++strlen));
            }
        }
        str[strlen] = '\0';
        firstname = (char*)malloc(sizeof(char)*(strlen+1));
        copy(firstname, str);
        free(str);

        sort_and_insert(&base, lastname, firstname);
        free(lastname); free(firstname);
    }
    
    printarray(base);
    freearray(base);
    fclose(fp);
}