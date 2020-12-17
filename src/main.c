
#include "../headders/main.h"

PROJECT_STATE state = {false};

int main(){
    CLS();
    if(COMPILE_MECHINE == WINDOWS){
        system("color 71");
    }
    int width, height;
    printf("Enter the width and height values : ");
    scanf("%d%d", &width, &height);
    Point start = {0, 1};
    Point end = {width-1, height-2};
    Maze* maze = createMaze(height, width, start, end, time(NULL));
    printMaze(maze);
    movement(maze,maze->start);
    deleteMaze(maze);
    if(COMPILE_MECHINE == WINDOWS){
        system("color");
    }
    return 0;
}

bool isDebugOn(){
    return state.DEBUG;
}
