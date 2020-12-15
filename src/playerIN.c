#include "../headders/main.h"

int movement(Maze *maze , Point startPoint)
{   
    Point curpoint,nextpoint;
    curpoint = startPoint;
    char input;
    int index;
    printf("w-up\t d-right\t s-down\t a-left\t q-quit\n");
    while(1)
    {
        if(get1dIndex(maze,curpoint) == -1)
        {
            printf("Sorry something went wrong!\n");
            return -1;
        }
        maze->board[get1dIndex(maze,curpoint)] = PLAYER;
        input = getc(stdin);
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
                        ch = getc(stdin);
                        switch(ch)
                        {
                            case 'y':{
                                        //solution function
                                        return 1;
                                    }
                            case 'n':{
                                        continue;
                                    }

                        }
                    } 
        }
        index = get1dIndex(maze,nextpoint);
        if(
            (index != -1) && 
            (maze->board[index] == AIR)
        )
        {
            if(isEqualPoints(curpoint,startPoint))
            {
                maze->board[get1dIndex(maze,curpoint)] = START;   
            }
            else
            {
            maze->board[get1dIndex(maze,curpoint)] = AIR;
            }
            maze->board[index] = PLAYER;
            curpoint = nextpoint;
            //printMaze(maze);
        }
        system("cls");
        printMaze(maze);
    }
}
    