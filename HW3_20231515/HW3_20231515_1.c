#include <stdio.h>
typedef enum {lparen, rparen, plus, min, times, divide, mod, eos, operand, unmin} precedence;

int isp[] = {0,19,12,12,13,13,13,0,0,12}; // in-stack
int icp[] = {20,19,12,12,13,13,13,0,0,12}; //incoming-precedense

int isEmpty(precedence st[], int top) {
    if(top==-1) return 1;
    return 0;
}

precedence topval(precedence st[], int top) {
    return st[top];
}

precedence pop(precedence st[], int *top) {
    return st[(*top)--];
}

int pop2(int st[], int *top) {
    return st[(*top)--];
}

void push(precedence st[], int *top, precedence value) {
    st[++(*top)] = value;
}

void push2(int st[], int *top, int value) {
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
        case '#': return unmin;
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
        case unmin: printf("%c", '#'); return;
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
        case unmin: return '#';
    }
}


char *infix_to_postfix(char postfix[]) {
    char input[21]; // 입력받은 문자열 저장
    precedence st[21]; // 연산자를 저장할 스택
    int top = 0;

    int index = 0;

    printf("Input: ");
    scanf("%s", input);
    
    precedence token;

    st[0] = eos;
    int i = 0; precedence pretoken;
    for(token = getToken(input[i]); token!=eos; token = getToken(input[++i])) {
        // unary operator - 고려
        if((i==0 || pretoken != operand) && token == min && pretoken != rparen) {
            token = unmin;
        }

        if(token == operand) { // 숫자인 경우
            postfix[index++] = input[i];
            // printf("%c", input[i]);
        }  
        else if(token == rparen) { // 오른쪽 괄호인 경우
            while(st[top]!=lparen) {
                postfix[index++] = trans_token_to_char(pop(st, &top));
                // printToken(pop(st, &top));
            }
            pop(st, &top);
        }
        else {
            while(isp[st[top]]>=icp[token]) 
                postfix[index++] = trans_token_to_char(pop(st, &top));
                // printToken(pop(st, &top));
            push(st, &top, token);
        }
        pretoken = token;
    }
    while((token=pop(st, &top))!=eos) {
        // printToken(token);
        postfix[index++] = trans_token_to_char(token);
    }
    postfix[index] = '\0';
    return postfix;
}

int calculate_postfix(char postfix[]) {
    int st[21]; 
    int top = -1;

    precedence token;
    int op1, op2;
    int i=0;

    token = getToken(postfix[i]);
    while(token!=eos) {
        if(token == operand) { 
            push2(st, &top, postfix[i]-'0');
        }
        else {
            op2 = pop2(st, &top);
            op1 = pop2(st, &top); 
            switch(token) {
                case plus: push2(st, &top, op1+op2); break;
                case min: push2(st, &top, op1-op2); break;
                case times: push2(st, &top, op1*op2); break;
                case divide: push2(st, &top, op1/op2); break;
                case mod: push2(st, &top, op1%op2); break;
                case unmin: 
                    push2(st, &top, op1);
                    push2(st, &top, (-1)*op2); 
                    break;
            }
        }
        token = getToken(postfix[++i]);
    }
    return pop2(st, &top);
}

int main() {
    char postfix[21];
    printf("Postfix: %s\n", infix_to_postfix(postfix));
    printf("Result: %d\n", calculate_postfix(postfix));
}