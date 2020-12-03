
#include "../headders/main.h"

int dig(Maze* maze, Point point);
bool checkIfPossibleToDig(Maze* maze, Point point);
char* possiblePossitionsToDig(Maze* maze, Point point);

Maze* createMaze(int height, int width, Point start, Point end){
    Maze* maze = (Maze*) malloc(sizeof(Maze));
    maze->height = height;
    maze->width = width;
    maze->start = start;
    maze->end = end;
    maze->board = (char*)malloc(maze->height * maze->width * sizeof(char*));
    digmaze(maze);
    return maze;
}

int get1dIndex(Maze* maze, Point point){
    if ((point.x < 0) || (point.x > maze->width) || (point.y < 0) || (point.y > maze->height)){
        return -1;
    }
    return ((point.y * maze->width)+point.x); // y * (number of columns) + x
}

void digMaze(Maze* maze){
    int x, y, index;
    Point point;
    for (x = 0; x < maze->width; x++){
        for (y = 0; y < maze->height; y++){
            point.x = x;
            point.y = y;
            index = get1dIndex(maze, point);
            if (
                (x == 0) || (y == 0) ||
                (x == maze->width) || (y == maze->height)
            ){
                maze->board[index] = WALL;
            }else{
                maze->board[index] = BLOCK;
            }
        }
    }
    dig(maze, maze->start);
}

int dig(Maze* maze, Point point){
    return 0;
}

char* possiblePossitionsToDig(Maze* maze, Point point){
    char* possiblePoints = (char*)malloc(5 * sizeof(char));
    Point adjecentPoints[] = {
        {point.x + 1, point.y},
        {point.x, point.y - 1},
        {point.x - 1, point.y},
        {point.x, point.y + 1}
    };
    Point dir[] = {
        {1, 0},
        {0, -1},
        {-1, 0},
        {0, 1}
    };
    int i, index, strIndex = 0;
    for (i = 0; i < 4; i++){
        index = get1dIndex(maze, adjecentPoints[i]);
        if (maze->board[index] != WALL){
            index = get1dIndex(maze, nxtPointInDir(adjecentPoints[i], dir[i]));
            if (maze->board[index] != AIR){
                switch (i){
                    case 0:
                        possiblePoints[strIndex] = 'E';
                        break;
                    case 1:
                        possiblePoints[strIndex] = 'S';
                        break;
                    case 2:
                        possiblePoints[strIndex] = 'W';
                        break;
                    case 3:
                        possiblePoints[strIndex] = 'N';
                        break;
                }
                strIndex++;
                //if (
                //    !isEqualPoints(nxtPointInDir(adjecentPoints[i], dir[i]), maze->start) &&
                //    !isEqualPoints(nxtPointInDir(adjecentPoints[i], dir[i]), maze->end)
                //){
                //
                //}
            }
        }
    }
    possiblePoints[strIndex] = '\0';
    return possiblePoints;
}
