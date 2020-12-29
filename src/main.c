
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
    int choice = PLAY_NXT_GAME;
    char ch;
    Level* level = NULL;
    while(
        (levelNumber <= MAX_LEVEL) &&
        (choice != END_GAME)
    ){
        if (isDebugOn()){
            printf("While\n");
        }
        generateNxtLevel(&game);
        level = playLevel(&game);
        if (level != NULL)
        {
            printMaze(level->maze);
            gameResult = movement(level->maze, level->maze->start);
            if(gameResult == GAME_QUIT)
            {
                reflectSolution(game.level->maze, game.level->solution);
                printMaze(game.level->maze);
                level->didQuitTheGame = yea_lmao;
            }
            if(levelNumber == MAX_LEVEL)
            {   
                printf("You have finished the game!\n");
                disolveGame(&game);
                return 1;
            }
            printf("Do you wish to continue(y or n)?");
            ch = getchar();
            getchar();
            if(ch == 'y')
            {
                choice = PLAY_NXT_GAME;
            }
            else
            {
                choice = END_GAME;
            }
            printf("%d\n",choice);
        }
        else{
            disolveGame(&game);
            return 1;
        }
        levelNumber+= 1;
    }
    disolveGame(&game);
    RESETCOLOR();
    return 0;
}

bool isDebugOn(){
    return state.DEBUG;
}
