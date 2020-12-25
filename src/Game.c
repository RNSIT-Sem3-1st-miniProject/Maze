
#include "../headders/main.h"

// Player

Player* createPlayer(){
    Player* player = (Player*) malloc(sizeof(Player));
    printf("Enter the player name : ");
    getchar();
    fgets(player->Name, MAX_LEN_PLAYER_NAME, stdin);
    player->Name[strlen(player->Name) + 1] = '\0';
    player->pointsScored = 0;
    player->maxReachedLevel = 0;
    return player;
}

void deletePlayer(Player* player){
    free(player);
}

char* getPlayerName(Player* player){
    return player->Name;
}

int getTotalPoints(Player* player){
    return player->pointsScored;
}

void setPoints(Player* player, int points){
    player->pointsScored += points;
}

// Level

Level* createLevel(int levelNumber, Player* player){
    if (isDebugOn()){
        printf("create\n");
    }
    Level* level = (Level*) malloc(sizeof(Level));
    int height, width;
    unsigned int seed = time(NULL);
    level->levelNumber = levelNumber;
    level->solution = createLL();
    switch (level->levelNumber){
        case 1:{
            height = 20;
            width = 20;
            break;
        }
        case 2:{
            height = 20;
            width = 35;
            break;
        }
        case 3:{
            height = 25;
            width = 50;
            break;
        }
        case 4:{
            height = 25;
            width = 55;
            break;
        }
        case 5:{
            height = 30;
            width = 60;
            break;
        }
        case 6:{
            height = 35;
            width = 70;
            break;
        }
        case 7:{
            height = 35;
            width = 80;
            break;
        }
    }
    level->maze = createMaze(height, width, (Point){0, 1}, (Point){width-1, height-2}, seed);
    if(isDebugOn()){
        printMaze(level->maze);
    }
    Solution(level->maze, level->maze->start, level->solution);
    level->minKeystrokesToReachEnd = getLLsize(level->solution);
    level->pointsScored = 0;
    level->player = player;
    level->didQuitTheGame = false;
    return level;
}

void deleteLevel(Level* level){
    deleteMaze(level->maze);
    deleteLL(level->solution);
}

// Game

Game gameInit(){
    Game game;
    game.level = NULL;
    game.levelNumber = 0;
    game.player = NULL;
    return game;
}

void disolveGame(Game* game){
    deleteLevel(game->level);
    if(game->level != NULL){
        free(game->level);
        game->level = NULL;
    }
    deletePlayer(game->player);
    game->player = NULL;
}

void setPlayer(Game* game, Player* player){
    if(game->player != NULL){
        disolveGame(game);
    }
    game->player = player;
}

int resetLevel(Game* game, int levelNumber){
    if((levelNumber > MAX_LEVEL) || (levelNumber < 1)){
        return ERROR;
    }
    deleteLevel(game->level);
    free(game->level);
    return generateLevel(game, levelNumber);
}

int generateLevel(Game* game, int levelNumber){
    printf("%d\n", levelNumber);
    if (isDebugOn()){
        printf("gen\n");
    }
    if((levelNumber > MAX_LEVEL) || (levelNumber < 1)){
        return ERROR;
    }
    if(game->level != NULL){
        free(game->level);
        game->level = NULL;
    }
    game->level = createLevel(levelNumber, game->player);
    return PASS;
}

int generateNxtLevel(Game* game){
    if (isDebugOn()){
        printf("genN\n");
    }
    if (game->levelNumber + 1 == MAX_LEVEL){
        return ERROR;
    }
    if(game->level != NULL){
        free(game->level);
        game->level = NULL;
    }
    game->levelNumber += 1;
    return generateLevel(game, game->levelNumber);
}

Level* playLevel(Game* game){
    return game->level;
}
