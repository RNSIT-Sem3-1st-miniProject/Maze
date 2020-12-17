
#include "../headders/main.h"

char* possibleMoves(Maze* maze,Point point)
{
    char* result =(char *)malloc(sizeof(char)*5);
    int strIndex = 0;
    int dirIndex = 0;
    Point nxtPoint;
    int index;
    char dir[] = "ESWN";
    for(;dirIndex < 4;dirIndex++)
    {
        nxtPoint = nxtPointInDir(point,getDirPoint(dir[dirIndex]));
        index = get1dIndex(maze,nxtPoint);
        if(
            (index != -1) && 
            (maze->board[index] == AIR)
        )
        {
            result[strIndex] = dir[dirIndex];
            strIndex+=1;
        }
    }
    result[strIndex] = '\0';
    return result;
}