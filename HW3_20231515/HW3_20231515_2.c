#include <stdio.h>
typedef enum {lparen, rparen, plus, min, times, divide, mod, eos, operand} precedence;

int isp[] = {19,0,12,12,13,13,13,0,0}; // in-stack
int icp[] = {19,20,12,12,13,13,13,0,0}; //incoming-precedense
// isp[st[top]] > icp[token]

precedence pop(precedence st[], int *top) {
    return st[(*top)--];
}

void push(precedence st[], int *top, precedence value) {
    st[++(*top)] = value;
}

precedence getToken(char symbol) {
    switch(symbol) {
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return min;
        case '*': return times;
        case '/': return divide;
        case '%': return mod;
        case '\0': return eos;    // EOF
        default: return operand; // 숫자
    }
}

void printToken(precedence token) {
    switch(token) {
        case lparen: printf("%c", '('); return;
        case rparen: printf("%c", ')'); return;
        case plus: printf("%c", '+'); return;
        case min: printf("%c", '-'); return;
        case times: printf("%c", '*'); return;
        case divide: printf("%c", '/'); return;
        case mod: printf("%c", '%'); return;
        // case eos: printf("%c", ' '); return;    // EOF
    }
}

char trans_token_to_char(precedence token) {
    switch(token) {
        case lparen: return '(';
        case rparen: return ')';
        case plus: return '+';
        case min: return '-';
        case times: return '*';
        case divide: return '/';
        case mod: return '%';
        // case eos: return '';    // EOF
    }
}

int string_length(char *str) {
    int i = 0;
    while(str[i]!='\0') {i++;}
    return i;
}

char* infix_to_prefix(char prefix[]) {
    char input[21];
    int len, i;
    int index;
    precedence st[21];
    int top = 0;
    st[0] = eos;
    precedence token;

    printf("Input: ");
    scanf("%s", input);
    len = string_length(input);
    i = len-1; index = len-1;

    for(token = getToken(input[i]); token!=eos; token = getToken(input[--i])) {
        if(token == operand) { // 숫자인 경우
            prefix[index--] = input[i];
            // printf("%c", input[i]);
        }  
        else if(token == lparen) { // 왼쪽 괄호인 경우
            while(st[top]!=rparen) {
                prefix[index--] = trans_token_to_char(pop(st, &top));
                // printToken(pop(st, &top));
            }
            pop(st, &top);
        }
        else {
            while(isp[st[top]]>icp[token]) 
                prefix[index--] = trans_token_to_char(pop(st, &top));
                // printToken(pop(st, &top));
            push(st, &top, token);
        }
    }
    while((token=pop(st, &top))!=eos) {
        // printToken(token);
        prefix[index--] = trans_token_to_char(token);
    }
    prefix[len] = '\0';
    return &prefix[index+1];
}

int main() {
    char prefix[21];
    printf("Prefix: %s\n", infix_to_prefix(prefix));
}