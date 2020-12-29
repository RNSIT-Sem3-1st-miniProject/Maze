#include "../headders/main.h"

int movement(Maze *maze , Point startPoint)
{   
    bool end = false;
    Point curpoint,nextpoint;
    curpoint = startPoint;
    char input;
    int index;
    getchar();
    printf("w-up\t d-right\t s-down\t a-left\t q-quit\n");
    while(!end)
    {
        if(get1dIndex(maze,curpoint) == -1)
        {
            printf("Sorry something went wrong!\n");
            return ERROR;
        }
        maze->board[get1dIndex(maze,curpoint)] = PLAYER;
        input = getchar();
        switch(input)
        {
            case 'w': {
                        nextpoint.x = curpoint.x + 0;
                        nextpoint.y = curpoint.y - 1;
                       break;
                    }
            case 'd':{
                        nextpoint.x = curpoint.x + 1;
                        nextpoint.y = curpoint.y + 0;
                       break;
                    }         
            case 's':{
                        nextpoint.x = curpoint.x + 0;
                        nextpoint.y = curpoint.y + 1;
                       break;
                    } 
            case 'a':{
                        nextpoint.x = curpoint.x - 1;
                        nextpoint.y = curpoint.y + 0;
                       break;       
                    }  
            case 'q':{
                        char ch;
                        printf("Do you really want to quit and get the solution(y or n)?");
                        getchar();
                        ch = getchar();
                        switch(ch)
                        {
                            case 'y':{
                                        maze->board[get1dIndex(maze, curpoint)] = AIR;
                                        return GAME_QUIT;
                                    }
                            case 'n':{
                                        continue;
                                    }

                        }
                    } 
        }
        index = get1dIndex(maze,nextpoint);
        if(index == -1){
            if(isDebugOn())
            {
                printf("%d\n",ERROR);
            }
            return ERROR;
        }
        if(
            (maze->board[index] == AIR) ||
            (maze->board[index] == END) 
        )
        {
            if(isDebugOn())
            {
                printf("%c\n",maze->board[index]);
            }
            if(isEqualPoints(curpoint,startPoint))
            {
                maze->board[get1dIndex(maze,curpoint)] = START;   
            }
            else
            {
                maze->board[get1dIndex(maze,curpoint)] = AIR;
            }
            maze->keystrokeCount += 1;
            if (maze->board[index] == END){
                end = true;
            }
            maze->board[index] = PLAYER;
            curpoint = nextpoint;
        }
        CLS();
        printMaze(maze);
    }
    return LEVEL_PASS;
}
