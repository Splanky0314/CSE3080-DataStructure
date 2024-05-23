#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct node {
    int x, y, dir;
    struct node* llink;
    struct node* rlink;
} node;

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

char maze[SIZE][SIZE];
char mark[SIZE][SIZE];
node* head = NULL;
node* tail = NULL;

// stack의 맨 뒤에 node 추가
void stpush(node* node) {
    // printf("head: %p, %p\n", head, tail);
    // printf("push: %p %d %d %d %p %p\n", node, node->x, node->y, node->dir, node->llink, node->rlink);
    
    if(head == NULL) {
        head = node;
        tail = node;
        // printf("test: %p %d %d %d %p %p\n", tail, tail->x, tail->y, tail->dir, tail->llink, tail->rlink);
    }
    else {
        // printf("test: %p\n", tail);
        // printf("test: %p %d %d %d %p %p\n", tail, tail->x, tail->y, tail->dir, tail->llink, tail->rlink);
        node->llink = tail;
        tail->rlink = node;
        tail = node;
    }
}

// stack의 맨 뒤 node 리턴
// 따로 free 해줘야 할 듯
node* stpop() {
    // printf("pop: %p %d %d %d %p %p\n", tail, tail->x, tail->y, tail->dir, tail->llink, tail->rlink);
    node* tmp = tail;
    if(head == tail) head = NULL;
    tail = tail->llink;
    return tmp;
} 

int isempty() {
    if(head == NULL) return 1;
    else return 0;
}

void readfile(char* filename) {
    FILE* fin = fopen(filename, "r");
    int i = 0;
    while(fscanf(fin, "%s", maze[i++]) != EOF) {};
    fclose(fin);
}

void writefile(node* head, char* filename) {
    FILE* fout = fopen(filename, "w");

    while(head != NULL) {
        fprintf(fout, "%d %d\n", head->x, head->y);
        head = head->rlink;
    }
    fclose(fout);
}

node* newnode(int x, int y, int dir) {
    node* new = (node*)malloc(sizeof(node));
    new->x = x; new->y = y; new->dir = dir;
    new->llink = NULL; new->rlink = NULL;
    return new;
}

void searchpath() {
    // 출발지
    node* current = NULL;
    int found = 0;
    int x, y, dir;

    mark[1][1] = '1';
    stpush(newnode(1, 1, 1));
    
    while(!found && !isempty()) {
        // for(int i=0; i<SIZE; i++) {
        //     for(int j=0; j<SIZE; j++) {
        //         printf("%c", mark[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");

        current = stpop();
        x = current->x; y = current->y;
        dir = current->dir;
        while(dir<8 && !found) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            // printf("search %d %d %d\n", nx, ny, dir);

            // 목적지 도달
            if(nx == SIZE-1 && ny == SIZE-1) {
                stpush(newnode(x, y, ++dir));
                found = 1;
            }
            // 이동 가능한 경우
            else if(maze[nx][ny] == '0' && mark[nx][ny] == '0'){
                // printf("cur: %d %d %d\n", nx, ny, dir);
                mark[nx][ny] = '1';
                stpush(newnode(x, y, ++dir));
                x = nx; y = ny; dir = 0;
            }
            // 이동 불가능한 경우
            else dir++;
        }
    }
}

int main() {
    // mark 초기화
    for(int i=0; i<SIZE; i++) {
        for(int j=0; j<SIZE; j++) {
            mark[i][j] = '0';
        }
    }
    readfile("maze.txt");
    searchpath();
    writefile(head, "path.txt");
}