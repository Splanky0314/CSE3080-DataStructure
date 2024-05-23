#include <stdio.h>

// stack이 비었다면 return 1
int isEmpty(int st[], int top) {
    if(top==-1) return 1;
    return 0;
}

int topval(int st[], int top) {
    return st[top];
}

int pop(int st[], int *top) {
    int tmp = st[*top];
    (*top)--;
    return *top;
}

void push(int st[], int *top, int x) {
    (*top)++;
    st[*top] = x;
}

void printStackReverse(int st[], int top) {
    if(isEmpty(st, top)) {
        printf("0\n");
        return;
    }
    int flag = 1;
    for(int i=0; i<=top; i++) {
        if(flag && st[i]==0) continue;
        flag = 0;
        printf("%d", st[i]);
    }
    printf("\n");
}

int main() {
    int num, k;
    int st[100];
    int top = -1, exp, tmp;

    scanf("%d %d", &num, &k);

    for(exp=1; num/exp!=0; exp*=10) {};
    exp/=10;

    while(exp!=0 && k!=0) {
        tmp = (num/exp)%10;
        // printf("<%d> ", tmp);
        if(!isEmpty(st, top)) {
            while(k>0 && topval(st, top) > tmp) {
                // printf("pop %d\n", topval(st, top));
                pop(st, &top);
                k--;
            }
        }
        // printf("push %d\n", tmp);
        push(st, &top, tmp);
        exp/=10;
    }
    while(exp!=0) { 
        tmp = (num/exp)%10;
        push(st, &top, tmp);
        // printf("push %d\n", tmp);
        exp/=10;
    }
    while(k!=0) {
        // printf("pop %d\n", topval(st, top));
        pop(st, &top);
        k--;
    }
    printStackReverse(st, top);
}