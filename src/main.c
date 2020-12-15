
#include "../headders/main.h"

PROJECT_STATE state = {false};

int main(){
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


