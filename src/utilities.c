
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
    if ((point.x < 0) || (point.x >= maze->width) || (point.y < 0) || (point.y >= maze->height)){
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

Point getDirPoint(char dir){
    switch (dir){
        case 'N': return (Point){0, -1};
        case 'S': return (Point){0, 1};
        case 'E': return (Point){1, 0};
        case 'W': return (Point){-1, 0};
    }
}

char getDirChar(Point point){
    if (isEqualPoints(point, (Point){0, -1})){
        return 'N';
    }
    if (isEqualPoints(point, (Point){0, 1})){
        return 'S';
    }
    if (isEqualPoints(point, (Point){1, 0})){
        return 'E';
    }
    if (isEqualPoints(point, (Point){-1, 0})){
        return 'W';
    }
}

void PAUSE(float sec){
    if(isDebugOn()){
        printf("pause\n");
    }
    if (COMPILE_MECHINE == WINDOWS){
        float milisec = 1000 * sec;
        clock_t start = clock();
        while(clock() < (start + milisec));
    }else{
        sleep(sec);
    }
}

void CLS(){
    if (COMPILE_MECHINE == WINDOWS){
        system("cls");
    }else{
        system("clear");
    }
}

void reflectSolution(Maze* maze, LL* ll){
    PNode* temp = ll->start;
    while(temp != NULL){
        maze->board[get1dIndex(maze, temp->point)] = PATH;
        temp = temp->next;
    }
}

void SETCOLOR(char preSetColor){
    Theme theme = getTheme(getSelectedThemeIndex());
    if (COMPILE_MECHINE == WINDOWS){
        system("color 71");
    }else{
        if(preSetColor == WALL){
            printf("%s", theme.wall);
        }else if(preSetColor == AIR){
            printf("%s", theme.air);
        }else if(preSetColor == PATH){
            printf("%s", theme.path);
        }else if(preSetColor == PLAYER){
            printf("%s", theme.player);
        }else if(preSetColor == BLOCK){
            printf("%s", theme.block);
        }else{
            printf("%s", theme.screen);
        }
    }
}

void RESETCOLOR(){
    if(COMPILE_MECHINE == WINDOWS){
        system("color");
    }else{
        printf("\033[94m\033[49m");
    }
}

Theme constructTheme(int themeIndex){
    Theme theme;
    theme.wall[0] = ' ';
    theme.player[0] = ' ';
    theme.block[0] = ' ';
    theme.path[0] = ' ';
    theme.air[0] = ' ';
    theme.screen[0] = ' ';
    if(themeIndex == defaultTheme){
        strcat(theme.wall, BGBlack);
        strcat(theme.wall, FGRed);

        strcat(theme.player, BGTeal);
        strcat(theme.player, FGBlack);

        strcat(theme.block, BGBlack);
        strcat(theme.block, FGBlue);

        strcat(theme.path, BGLGreen);
        strcat(theme.path, FGBlack);

        strcat(theme.air, BGWhite);
        strcat(theme.air, FGBlack);

        strcat(theme.screen, BGLGray);
        strcat(theme.screen, FGBlue);
    }
    theme.wall[strlen(theme.wall)] = '\0';
    theme.player[strlen(theme.player)] = '\0';
    theme.block[strlen(theme.block)] = '\0';
    theme.path[strlen(theme.path)] = '\0';
    theme.air[strlen(theme.air)] = '\0';
    theme.screen[strlen(theme.screen)] = '\0';
    return theme;
}
