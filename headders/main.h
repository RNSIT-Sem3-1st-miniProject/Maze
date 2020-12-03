
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define AIR ' '
#define WALL '#'
#define BLOCK '*'
#define START '{'
#define END '}'
#define PATH '.'

void setSeed(unsigned int seed);
int getRandonNumber(int max);

typedef struct Point{
    int x, y;
}Point;

Point* createPoint(int x, int y);
void printPoint(Point* point);
Point nxtPointInDir(Point point, Point dir);
bool isEqualPoints(Point this, Point other);

typedef struct Maze{
    char* board; // warraped into row-major 2d array
    int width, height;
    Point start, end;
}Maze;

Maze* createMaze(int width, int height, Point start, Point end);
void printMaze(Maze* maze);
int get1dIndex(Maze* maze, Point point);
Point get2dPoint(Maze* maze, int index);
void digMaze(Maze* maze);

/*typedef struct Player{
}Player;
*/


