
#include "../headders/main.h"

PROJECT_STATE state = {false};

Theme theme;
int themeIndex = defaultTheme;

int main(){
    CLS();

    theme = constructTheme(defaultTheme);

    SETCOLOR(BACKGROUND);
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
            }else if(gameResult == LEVEL_PASS){
                if(game.player->maxReachedLevel < game.levelNumber){
                    game.player->maxReachedLevel = game.levelNumber;
                }
                setPoints(game.player, calculatePointsScored(game.level));
            }
            if(levelNumber == MAX_LEVEL)
            {   
                printf("You have finished the game!\n");
                disolveGame(&game);
                return 1;
            }
            printf("Do you wish to continue(y or n)?");
            getchar();
            ch = getchar();
            printf("choice : \"%c\"\n",ch);
            choice = PLAY_NXT_GAME;
            if(ch == 'n')
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
    CLS();
    printf("Player name : %s\n", game.player->Name);
    printf("Level reached : %d\n", game.player->maxReachedLevel);
    printf("Points scored : %d\n", game.player->pointsScored);
    disolveGame(&game);
    RESETCOLOR();
    return 0;
}

bool isDebugOn(){
    return state.DEBUG;
}

Theme getTheme(int tIndex){
    if (themeIndex != tIndex){
        themeIndex = tIndex;
        disloveTheme(theme);
        theme = constructTheme(themeIndex);
    }
    return theme;
}

int getSelectedThemeIndex(){
    return themeIndex;
}
