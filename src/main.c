
#include "../headders/main.h"

PROJECT_STATE state = {false};

int main(){
    CLS();
    SETCOLOR();
    Game game = gameInit();
    Player* player = createPlayer();
    setPlayer(&game, player);
    int levelNumber = 1;
    int gameResult = PLAY_NXT_GAME;
    Level* level = NULL;
    while(
        (levelNumber <= MAX_LEVEL) &&
        (gameResult != GAME_QUIT)
    ){
        if (isDebugOn()){
            printf("While\n");
        }
        generateNxtLevel(&game);
        level = playLevel(&game);
        if (level != NULL){
            printMaze(level->maze);
            gameResult = movement(level->maze, level->maze->start);
        }else{
            disolveGame(&game);
            return 1;
        }
        levelNumber+= 1;
        gameResult = PLAY_NXT_GAME;
    }
    disolveGame(&game);
    RESETCOLOR();
    return 0;
}

bool isDebugOn(){
    return state.DEBUG;
}
