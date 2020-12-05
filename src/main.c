
#include "../headders/main.h"

int main(){
    int width, height;
    printf("Enter the width and height values : ");
    scanf("%d%d", &width, &height);
    Point start = {2, height-1};
    Point end = {width, 1};
    Maze* maze = createMaze(height, width, start, end, time(NULL));
    printMaze(maze);
    deleteMaze(maze);    
    return 0;
}
