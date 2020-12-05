
#include "../headders/main.h"

int dig(Maze* maze, Point point);
bool checkIfPossibleToDig(Maze* maze, Point point);
char* possiblePossitionsToDig(Maze* maze, Point point);

Maze* createMaze(int height, int width, Point start, Point end, unsigned int seed){
    Maze* maze = (Maze*) malloc(sizeof(Maze));
    maze->height = height;
    maze->width = width;
    maze->start = start;
    maze->end = end;
    maze->board = (char*)malloc(maze->height * maze->width * sizeof(char*));
    maze->seed = seed;
    digMaze(maze);
    return maze;
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
    setSeed(maze->seed);
    dig(maze, maze->start);
}

int dig(Maze* maze, Point point){
    if (
        (maze->board[get1dIndex(maze, point)] != AIR) &&
        (maze->board[get1dIndex(maze, point)] != START)
        ){
        return 1;
    }
    char* possibleDir = NULL;
    int sizeOfpossibleDir = 0;
    possibleDir = possiblePossitionsToDig(maze, point);
    sizeOfpossibleDir = strlen(possibleDir);
    if (sizeOfpossibleDir != 0){
        char dir = possibleDir[getRandomNumber(sizeOfpossibleDir)];
        Point dirPoint;
        switch (dir){
            case 'E':
                dirPoint.x = 1;
                dirPoint.y = 0;
                break;
            case 'S':
                dirPoint.x = 0;
                dirPoint.y = -1;
                break;
            case 'W':
                dirPoint.x = -1;
                dirPoint.y = 0;
                break;
            case 'N':
                dirPoint.x = 0;
                dirPoint.y = 1;
                break;
            case '\0':
                break;
        }
        maze->board[get1dIndex(maze, point)] = AIR;
        return dig(maze, nxtPointInDir(point, dirPoint));
    }
    free(possibleDir);
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
        if (
            (maze->board[index] != WALL) &&
            (maze->board[index] != AIR)
            ){
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
            }
        }
    }
    possiblePoints[strIndex] = '\0';
    return possiblePoints;
}

void printMaze(Maze* maze){
    int x, y;
    Point point;
    for (x = 0; x < maze->width; x++){
        point.x = x;
        for (y = 0; y < maze->height; y++){
            point.y = y;
            printf("%c", maze->board[get1dIndex(maze, point)]);
        }
        printf("\n");
    }
}

void deleteMaze(Maze* maze){
    free(maze->board);
    free(maze);
    maze = NULL;
}
