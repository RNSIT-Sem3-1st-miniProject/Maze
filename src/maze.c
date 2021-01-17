
#include "../headders/main.h"

int dig(Maze* maze, Point point);
bool checkIfPossibleToDig(Maze* maze, Point point);
char* possiblePossitionsToDig(Maze* maze, Point point);

Maze* createMaze(int height, int width, Point start, Point end, unsigned int seed){
    if(isDebugOn()){
        printf("maze\n");
    }
    Maze* maze = (Maze*) malloc(sizeof(Maze));
    maze->height = height;
    maze->width = width;
    maze->start = start;
    maze->end = end;
    maze->board = (char*)malloc(maze->height * maze->width * sizeof(char*));
    maze->seed = seed;
    if(digMaze(maze) != 0){
        printf("Unknown ERROR!!!!\n");
    }
    return maze;
}

int digMaze(Maze* maze){
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
    int digResult = dig(maze, maze->start);
    maze->board[get1dIndex(maze, nxtPointInDir(maze->end,getDirPoint('W')))] = AIR;
    return digResult;
}

int dig(Maze* maze, Point point){
    int index = get1dIndex(maze, point);
    if (index == -1){
        printf("sorry something went wrong!!");
        return 1;
    }
    if(
        (maze->board[index] != AIR) &&
        (maze->board[index] != START) &&
        (maze->board[index] != END)
    ){
        return 2;
    }

    char* possibleDirToDig = NULL, dir;
    int sizeOfPossibleDir = 0;
    Point nxtPoint;
    possibleDirToDig = possiblePossitionsToDig(maze, point);
    sizeOfPossibleDir = strlen(possibleDirToDig);
    while (sizeOfPossibleDir != 0){
        dir = possibleDirToDig[getRandomNumber(sizeOfPossibleDir -1)];
        free(possibleDirToDig);
        nxtPoint = nxtPointInDir(point, getDirPoint(dir));
        maze->board[get1dIndex(maze, nxtPoint)] = AIR;
        int result = dig(maze, nxtPoint);
        if (result == 1){
            return 1;
        }else if(result == 2){
            return 2;
        }
        possibleDirToDig = possiblePossitionsToDig(maze, point);
        sizeOfPossibleDir = strlen(possibleDirToDig);
    }
    free(possibleDirToDig);
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
                set[adjLoop] = true;
            }
        }
        if (
            (set[0] == true) &&
            (set[1] == true) &&
            (set[2] == true) &&
            (index != -1) &&
            (maze->board[index] != WALL) &&
            (maze->board[index] != START) &&
            (maze->board[index] != END)
        ){
            possiblePoints[strIndex] = dirToCheck[dirIndex];
            ++strIndex;
        }
    }
    possiblePoints[strIndex] = '\0';
    return possiblePoints;
}

void printMaze(Maze* maze){
    int x, y;
    Point point;
    int index = 0;
    for (y = 0; y < maze->height; y++){
        point.y = y;
        for (x = 0; x < maze->width; x++){
            point.x = x;
            index = get1dIndex(maze, point);
            if(COMPILE_MECHINE == LINUX){
                SETCOLOR(maze->board[index]);
            }
            printf("%c", maze->board[index]);
        }
        if(COMPILE_MECHINE == LINUX){
            SETCOLOR(BACKGROUND);
        }
        printf("\n");
    }
    if (isDebugOn()){
        printf("%s\n", maze->board);
    }
}

void deleteMaze(Maze* maze){
    free(maze->board);
    free(maze);
    maze = NULL;
}
