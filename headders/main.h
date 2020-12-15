
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
#define PLAYER '$'

typedef struct Project{
    bool DEBUG;
    //ErrorList* errorList;
}PROJECT_STATE;

bool isDebugOn();

// testing this files
#define readBuffer 128
char* readFile(char* fileName);
void writeFile(char* fileName, char* data);

void setSeed(unsigned int seed);
int getRandomNumber(int max);

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
    unsigned int seed;
}Maze;

Maze* createMaze(int height, int width, Point start, Point end, unsigned int seed);
void printMaze(Maze* maze);
int get1dIndex(Maze* maze, Point point);
Point get2dPoint(Maze* maze, int index);
void digMaze(Maze* maze);
void deleteMaze(Maze* maze);


//functions written by suprith

int movement(Maze * , Point);

/*typedef struct Player{
}Player;
*/


