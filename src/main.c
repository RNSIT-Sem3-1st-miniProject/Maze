
#include "../headders/main.h"

PROJECT_STATE state = {false};

int main(){
    system("clear");
    system("cls");
    system("color 71"); // comment while compiling for linux
    int width, height;
    printf("Enter the width and height values : ");
    scanf("%d%d", &width, &height);
    Point start = {0, 1};
    Point end = {width-1, height-2};
    Maze* maze = createMaze(height, width, start, end, time(NULL));
    printMaze(maze);
    movement(maze,maze->start);
    deleteMaze(maze);    
    return 0;
}

bool isDebugOn(){
    return state.DEBUG;
}
