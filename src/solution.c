
#include "../headders/main.h"

char* possibleMoves(Maze* maze,Point point)
{
    printf("Entering : ");
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
    printf("calculated moves : ");
    return result;
}

int Solution(Maze* maze,Point point,LL* ll)
{
    printf("Solution : ");
    append(ll,createPNode(point));
    printf("unidentified error!!!!!");
    if(isEqualPoints(point,maze->end))
    {
        return 0;
    }
    printf(" : ");
    char* moves = possibleMoves(maze,point);
    printf("%d : %s\n",strlen(moves),moves);
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
            //return 1;
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