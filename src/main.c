
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
    int result = movement(maze,maze->start);
    printf("%d\n",result);
    if(result == 1)
    {
        LL* ll = createLL();
        printf("\n%d\n",Solution(maze,maze->start,ll));
        printf("%d\n",getLLsize(ll));
        deleteLL(ll);
    }
    deleteMaze(maze);
    if(COMPILE_MECHINE == WINDOWS){
        system("color");
    }
    return 0;
}

bool isDebugOn(){
    return state.DEBUG;
}
