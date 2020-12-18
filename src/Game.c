
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

Level createLevel(int levelNumber, Player* player){
    Level level;
    int height, width;
    unsigned int seed = time(NULL);
    level.levelNumber = levelNumber;
    switch (level.levelNumber){
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
    level.maze = createMaze(height, width, (Point){0, 1}, (Point){width-1, height-2}, seed);
    level.minPointsToReachEnd = 0;
    level.pointsScored = 0;
    level.player = player;
    level.didQuitTheGame = false;
    return level;
}

void deleteLevel(Level* level){
    deleteMaze(level->maze);
}

// Game

Game gameInit(){
    Game game;
    game.player = NULL;
    game.currentLevel = 0;
    game.maxPlayedLevel = 0;
    return game;
}

void disloveGame(Game* game){
    for (int lvl = 0; lvl < game->maxPlayedLevel; lvl++){
        deleteLevel(&(game->levels[lvl]));
    }
    game->player = NULL;
    game->currentLevel = 0;
    game->maxPlayedLevel = 0;
}

void setPlayer(Game* game, Player* player){
    if(game->player != NULL){
        disloveGame(game);
    }
    game->player = player;
}

Level* getLevel(Game* game, int levelNumber){
    if((levelNumber > game->maxPlayedLevel) || (levelNumber >= MAX_LEVEL)){
       return NULL;
    }
    return &(game->levels[levelNumber]);
}

Level* resetLevel(Game* game, int levelNumber){
    if((levelNumber > game->maxPlayedLevel) || (levelNumber >= MAX_LEVEL)){
       return NULL;
    }
    deleteLevel(&(game->levels[levelNumber]));
    game->levels[levelNumber] = createLevel(levelNumber, game->player);
    return &(game->levels[levelNumber]);
}

Level* generateLevel(Game* game, int levelNumber){
    if((game->maxPlayedLevel +1 > levelNumber) || (levelNumber >= MAX_LEVEL)){
        return NULL;
    }
    game->levels[levelNumber] = createLevel(levelNumber, game->player);
    return &(game->levels[levelNumber]);
}

Level* generateNxtLevel(Game* game){
    if(game->maxPlayedLevel + 1 == MAX_LEVEL){
        return NULL;
    }
    return generateLevel(game, game->maxPlayedLevel + 1);
}

Level* playLevel(Game* game, int levelNumber){
    if(levelNumber <= game->maxPlayedLevel){
        return resetLevel(game, levelNumber);
    }
    if(levelNumber = game->maxPlayedLevel +1){
        return generateNxtLevel(game);
    }
}
