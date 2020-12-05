
#include "../headders/main.h"

Point* createPoint(int x, int y){
    Point* point = (Point*) malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    return point;
}

void printPoint(Point* point){
    printf("(%d, %d)\n", point->x, point->y);
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
