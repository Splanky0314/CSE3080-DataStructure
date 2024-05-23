#include <stdio.h>
#include <string.h> // strlen()을 사용하기 위해 include

void pmatch_all(char str[], char pat[]) {
    int slen = strlen(str);
    int plen = strlen(pat);
    // failure table 만들기
    int failure[40] = {0,}; // 0으로 초기화
    int j=0;
    for(int i=1; i<plen; i++) {
        while(j>0 && pat[i]!=pat[j]) {
            j = failure[j-1];
        }
        if(pat[i]==pat[j]) {
            failure[i] = ++j;
        }
    }

    // KMP 구현
    j = 0;
    for(int i=0; i<slen; i++) {
        while(j>0 && str[i]!=pat[j]) {
            j = failure[j-1];
        }
        if(str[i]==pat[j]) {
            if(j == plen-1) {
                printf("%d\n", i-plen+1);
                j = failure[j];
            }
            else {
                j++;
            }
        }
    }
}

int main() {
    char str[31]; // string을 입력받아 저장
    char pat[31]; // pattern을 입력받아 저장
    scanf("%s %s", str, pat);
    pmatch_all(str, pat);
}