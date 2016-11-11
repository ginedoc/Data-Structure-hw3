#include <stdio.h>
#include <stdlib.h>
#define SIZE 9

typedef struct {
    int x; 
    int y;
} Point;

Point pt(int, int);
void visit(int[][SIZE], Point, Point, void (*)(int[][SIZE]));
void print(int[][SIZE]);

int main(void) { 
    int maze[SIZE][SIZE] = {{2, 2, 2, 2, 2, 2, 2, 2, 2},
                            {2, 0, 0, 0, 0, 0, 0, 0, 2},
                            {2, 2, 2, 0, 2, 2, 2, 0, 2},
                            {2, 0, 2, 0, 2, 0, 2, 0, 2},
                            {2, 0, 2, 0, 2, 2, 2, 2, 2},
                            {2, 0, 0, 0, 0, 2, 2, 0, 2},
                            {2, 2, 2, 2, 0, 2, 2, 0, 2},
                            {2, 0, 0, 2, 0, 0, 0, 0, 2},
                            {2, 2, 2, 2, 2, 2, 2, 2, 2}}; 

    visit(maze, pt(1, 1), pt(7, 7), print);

    return 0; 
}

Point pt(int x, int y) {
    Point p = {x, y};
    return p;
}

void visit(int maze[][SIZE], Point start, 
           Point end, void (*take)(int[][SIZE])) {
    if(!maze[start.x][start.y]) {
         maze[start.x][start.y] = 1;
         if(maze[end.x][end.y]) {
             take(maze);
         }
         else {
             visit(maze, pt(start.x, start.y + 1), end, take);
             visit(maze, pt(start.x + 1, start.y), end, take);
             visit(maze, pt(start.x, start.y - 1), end, take);
             visit(maze, pt(start.x - 1, start.y), end, take);
         }
         maze[start.x][start.y] = 0;
    }
}

void print(int maze[][SIZE]) {
    int i, j;
    for(i = 0; i < SIZE; i++) { 
        for(j = 0; j < SIZE; j++) switch(maze[i][j]) {
            case 0 : printf("0"); break;
            case 1 : printf("*"); break;
            case 2 : printf("1"); 
        }
        printf("\n"); 
    }     
    printf("\n");
}