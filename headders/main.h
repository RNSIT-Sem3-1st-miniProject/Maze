
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h> // comment while compiling for windows
//#include <windows.h> // comment while compiling for LINUX

#define WINDOWS "windows"
#define LINUX "linux"
#define COMPILE_MECHINE LINUX

#define AIR ' '
#define WALL '#'
#define BLOCK 'X'
#define START '{'
#define END '}'
#define PATH '.'
#define PLAYER 'O'

#define GAME_QUIT 1
#define END_GAME 2
#define PLAY_NXT_GAME 0

// writen by vasu

typedef struct Project{
    bool DEBUG;
}PROJECT_STATE;

bool isDebugOn();

void setSeed(unsigned int seed);
int getRandomNumber(int max);

void PAUSE(float sec);
void CLS();
void SETCOLOR();
void RESETCOLOR();

typedef struct Point{
    int x, y;
}Point;

Point* createPoint(int x, int y);
void printPoint(Point* point);
Point nxtPointInDir(Point point, Point dir);
bool isEqualPoints(Point this, Point other);

Point getDirPoint(char dir);
char getDirChar(Point dir);

typedef struct Maze{
    char* board; // warraped into row-major 2d array
    int width, height;
    Point start, end;
    unsigned int seed;
    int keystrokeCount;
}Maze;

Maze* createMaze(int height, int width, Point start, Point end, unsigned int seed);
void printMaze(Maze* maze);
int get1dIndex(Maze* maze, Point point);
Point get2dPoint(Maze* maze, int index);
int digMaze(Maze* maze);
void deleteMaze(Maze* maze);

//functions written by suprith

int movement(Maze * , Point);

typedef struct PNode
{
    Point point;
    struct PNode* next;
}PNode;

PNode* createPNode(Point);
void deletePNode(PNode *);

typedef struct LL
{
    PNode* start,* end;
    int size;
}LL;

LL* createLL();
void deleteLL(LL* );
int getLLsize(LL* );
void append(LL* ,PNode* );
Point pop(LL* ,char);
Point peep(LL* ,char);
bool isVisited(LL* ,Point );

#define NOT_A_VALID_POINT (Point){-1, -1}

int Solution(Maze* ,Point ,LL* );
char* possibleMoves(Maze* ,Point );

// functions writen by Vasu

#define MAX_LEVEL 7
#define MAX_LEN_PLAYER_NAME 64

typedef struct Player{
    char Name[MAX_LEN_PLAYER_NAME];
    int pointsScored;
    int maxReachedLevel;
}Player;

Player* createPlayer();
void deletePlayer(Player* player);
char* getPlayerName(Player* player);
int getTotalPoints(Player* player);
void setPoints(Player* player, int points);

typedef struct Level{
    int levelNumber;
    int pointsScored;
    Maze* maze;
    LL* solution;
    int minKeystrokesToReachEnd;
    bool didQuitTheGame;
    Player* player;
}Level;

Level createLevel(int levelNumber, Player* player);
void deleteLevel(Level* level);
int countPointsScored(Level* level);

typedef struct game{
    Level levels[MAX_LEVEL];
    Player* player;
    int currentLevel, maxPlayedLevel;
}Game;

#define LEVEL_LOCKED 1
#define ERROR -1
#define PASS 0

Game gameInit();
void disolveGame(Game* game);
void setPlayer(Game* game, Player* player);
int resetLevel(Game* game, int levelNumber);
int generateLevel(Game* game, int levelNumber);
int generateNxtLevel(Game* game);
Level* playLevel(Game* game, int levelNumber);

void reflectSolution(Maze* maze, LL* ll);
