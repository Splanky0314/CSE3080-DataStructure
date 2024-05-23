#include <stdio.h>

void printSet(int s, int num, int result) {
    printf("{");
    for(int i=0; i<s; i++) {
        if((result>>i)%2) { // 해당 원소가 존재한다면
            printf("%c", 'a'+i);
            if(--num>0) printf(" ");
        }
    }
    printf("} ");
}

// s: 집합의 원소 수
// num: 계산하고 싶은 부분집합의 원소 수
// cur: 현재 부분집합의 원소 수
// idx: 현재 계산중인 원소의 인덱스(a가 1, b가 2 ...)
// result: 부분집합
// flag: PowerSet함수의 첫 호출을 구분하기 위한 수
void PowerSet(int s, int num, int cur, int idx, int result, int flag) {
    if(flag) { // PowerSet의 첫 호출에서
        for(int i=0; i<=s; i++) {
            PowerSet(s, i, 0, 0, result, 0);
        }
    }
    else { 
        if(cur==num) {
            printSet(s, num, result);
            return;
        }
        for(int i=idx; i<s; i++) {
            result += 1 << i; // c[i] = 1;
            PowerSet(s, num, cur+1, i+1, result, 0);
            result -= 1 << i; // c[i] = 0; 
        }
    }
    
}

int main() {
    int s; // 집합 S의 원소 수를 저장
    scanf("%d", &s);
    PowerSet(s, 0, 0, 0, 0, 1);
    printf("\n");
}