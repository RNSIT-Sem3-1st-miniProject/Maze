
#include "../headders/main.h"

Point* createPoint(int x, int y){
    Point* point = (Point*) malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    return point;
}

void printPoint(Point* point){
    printf("(%d, %d), ", point->x, point->y);
}

void setSeed(unsigned int seed){
    srand(seed);
}

int getRandomNumber(int max){
    return (rand() % (max + 1));
}

Point nxtPointInDir(Point point, Point dir){
    Point nxtPoint;
    nxtPoint.x = point.x + dir.x;
    nxtPoint.y = point.y + dir.y;
    return nxtPoint;
}

int get1dIndex(Maze* maze, Point point){
    if ((point.x < 0) || (point.x > maze->width) || (point.y < 0) || (point.y > maze->height)){
        return -1;
    }
    return ((point.y * maze->width)+point.x); // y * (number of columns) + x
}

bool isEqualPoints(Point this, Point other){
    if ((this.x == other.x) && (this.y == other.y)){
        return true;
    }
    return false;
}


// testing files

char* readFile(char* fileName){
    FILE *file = fopen(fileName, "r");
    char* data = NULL;
    char* buffer = NULL;
    do{
        // reset buffer
        if (buffer != NULL){
            free(buffer);
            buffer = NULL;
        }
        // set buffer mem
        buffer = (char*) malloc(sizeof(char) * (readBuffer));
        fgets(buffer, readBuffer, file);
        if (strlen(buffer) != 0){
            if (data != NULL){
                data = (char*) realloc(data, sizeof(char) * (strlen(data) + strlen(buffer)) );
            }else{
                data = (char*) malloc(sizeof(char) * strlen(buffer) );
            }
            strcat(data, buffer);
        }
    }while(strlen(buffer)!= 0);
    if (data[strlen(data)] != '\0'){
        data = (char*) realloc(data, sizeof(char) * (strlen(data) + 1) );
        data[strlen(data)+1] = '\0';
    }
    fclose(file);
    return data;
}

void writeFile(char* fileName, char* data){
    FILE *file = fopen(fileName, "w");
    fprintf(file, data);
    fclose(file);
}
