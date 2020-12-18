
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
            ((maze->board[index] == AIR) ||
            (maze->board[index] == END))
        )
        {
            result[strIndex] = dir[dirIndex];
            strIndex+=1;
        }
    }
    result[strIndex] = '\0';
    return result;
}

int Solution(Maze* maze,Point point,LL* ll)
{
    append(ll,createPNode(point));
    if(isEqualPoints(point,maze->end))
    {
        return 0;
    }
    char* moves = possibleMoves(maze,point);
    int count = 0;
    Point nextPoint ;
    for(int moveIndex =0;moveIndex < strlen(moves);moveIndex++)
    {
        nextPoint = nxtPointInDir(point,getDirPoint(moves[moveIndex]));
        if(!isVisited(ll,nextPoint))
        {
            if(Solution(maze,nextPoint,ll) == 0)
            {
                free(moves);
                return 0;
            }
        }
        count += 1;
    }
    if(count == strlen(moves))
    {
        pop(ll,'L');
    }
    free(moves);
    return 1;
}