
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
    for (y = 0; y < maze->height; y++){
        for (x = 0; x < maze->width; x++){
            point.x = x;
            point.y = y;
            index = get1dIndex(maze, point);
            if(isEqualPoints(point, maze->start)){
                maze->board[index] = START;
            }else if(isEqualPoints(point, maze->end)){
                maze->board[index] = END;
            }else if (
                (x == 0) || (y == 0) ||
                (x == maze->width-1) || (y == maze->height-1)
            ){
                maze->board[index] = WALL;
            }else{
                maze->board[index] = BLOCK;
            }
        }
    }
    setSeed(maze->seed);
    //printf("\ncalling dig\n");
    int digResult = dig(maze, maze->start);
    if (isDebugOn()){
        // 
    }
}

int dig(Maze* maze, Point point){
    if (isDebugOn()){
        printf("dig");
        printPoint(&point);
        printf("\n");
    }
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
    if (isDebugOn()){
        printf("%s, %d\n", possibleDir, sizeOfpossibleDir);
    }

    if (sizeOfpossibleDir != 0){
        char dir = possibleDir[getRandomNumber(sizeOfpossibleDir -1)];
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
            default:
                dirPoint.x = -1;
                dirPoint.y = -1;
                break;
        }
        if (isDebugOn()){
            printf("%c : ", dir);
            printPoint(&dirPoint);
            printf("\n");
        }
        Point pt = {-1, -1};
        if (isEqualPoints(dirPoint, pt)){
            return -1;
        }
        Point nxtPoint = nxtPointInDir(point, dirPoint);
        if (get1dIndex(maze, nxtPoint) != -1){
            maze->board[get1dIndex(maze, nxtPoint)] = AIR;
            return dig(maze, nxtPoint);
        }
    }
    free(possibleDir);
    return 0;
}

char* possiblePossitionsToDig(Maze* maze, Point point){
    char* possiblePoints = (char*) malloc(5 * sizeof(char));
    char dirToCheck[] = "NSEW";
    Point adjDigPoints[3];
    Point digPoint;
    int dirIndex, index, strIndex = 0, adjIndex, adjLoop;
    for (dirIndex = 0; dirIndex < 4; dirIndex++){
        digPoint = nxtPointInDir(point, getDirPoint(dirToCheck[dirIndex]) );
        index = get1dIndex(maze, digPoint);
        if(
            (index != -1) &&
            (maze->board[index] != WALL) &&
            (maze->board[index] != AIR) &&
            (maze->board[index] != START) &&
            (maze->board[index] != END)
        ){
            switch (dirToCheck[dirIndex]){
                case 'N':{
                    adjDigPoints[0] = nxtPointInDir(digPoint, getDirPoint('W'));
                    adjDigPoints[1] = nxtPointInDir(digPoint, getDirPoint('N'));
                    adjDigPoints[2] = nxtPointInDir(digPoint, getDirPoint('E'));
                    break;
                }
                case 'S':{
                    adjDigPoints[0] = nxtPointInDir(digPoint, getDirPoint('E'));
                    adjDigPoints[1] = nxtPointInDir(digPoint, getDirPoint('S'));
                    adjDigPoints[2] = nxtPointInDir(digPoint, getDirPoint('W'));
                    break;
                }
                case 'E':{
                    adjDigPoints[0] = nxtPointInDir(digPoint, getDirPoint('N'));
                    adjDigPoints[1] = nxtPointInDir(digPoint, getDirPoint('E'));
                    adjDigPoints[2] = nxtPointInDir(digPoint, getDirPoint('S'));
                    break;
                }
                case 'W':{
                    adjDigPoints[0] = nxtPointInDir(digPoint, getDirPoint('S'));
                    adjDigPoints[1] = nxtPointInDir(digPoint, getDirPoint('W'));
                    adjDigPoints[2] = nxtPointInDir(digPoint, getDirPoint('N'));
                    break;
                }
            }
        }
        bool set[] = {false, false, false};
        for (adjLoop = 0; adjLoop < 3; adjLoop++){
            adjIndex = get1dIndex(maze, adjDigPoints[adjLoop]);
            if (
                (adjIndex != -1) &&
                (maze->board[adjIndex] != AIR)
            ){
                if (isDebugOn()){
                    printf("%c : ", dirToCheck[dirIndex]);
                    printPoint(&adjDigPoints[adjLoop]);
                    printf("\n");
                }
                set[adjIndex] = true;
            }
            printf("%d\n", adjIndex);
        }
        printf("hii\n");
        if (
            (set[0] == true) &&
            (set[1] == true) &&
            (set[2] == true)
        ){
            printf("set %c : \n", dirToCheck[dirIndex]);
            possiblePoints[strIndex] = dirToCheck[dirIndex];
            ++strIndex;
        }
    }
    possiblePoints[strIndex] = '\0';
    printf("%s\n", possiblePoints);
    return possiblePoints;
}

void printMaze(Maze* maze){
    int x, y;
    Point point;
    for (y = 0; y < maze->height; y++){
        point.y = y;
        for (x = 0; x < maze->width; x++){
            point.x = x;
            if(isDebugOn() && false){
                printPoint(&point);
            }
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
