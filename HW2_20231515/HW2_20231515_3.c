#include <stdio.h>
#include <stdlib.h> // 동적 할당을 위헤 include

// 수가 연속적인지 확인
int check(int n, int *array) {
    // table: 중복되는 값을 판단하기 위한 배열
    int *table = (int*)malloc(100*sizeof(int));
    int minidx = array[0];
    int maxidx = array[0];
    table[array[0]]++;
    for(int i=1; i<n; i++) {
        if(table[array[i]]) {
            free(table);
            return 0; // 중복되는 수 존재
        }
        if(array[i]<minidx) minidx = array[i];
        else if(array[i]>maxidx) maxidx = array[i];
    }
    free(table);
    if(maxidx-minidx==n-1) return 1; // 연속적
    return 0; // minidx와 maxidx 사이에 공백 수 존재
}

int main() {
    int n, *array;
    scanf("%d", &n); // 원소의 개수를 입력받아 n에 저장
    array = (int*)malloc(n*sizeof(int));

    for(int i=0; i<n; i++) {
        scanf("%d", &array[i]); 
    }
    printf("%d\n", check(n, array)); 
    free(array);
}