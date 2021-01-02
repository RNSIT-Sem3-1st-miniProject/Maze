
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
    if ((COMPILE_MECHINE == WINDOWS) and false){
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
    if(themeIndex == defaultTheme){
        theme.wall = jstr(BGBlack, FGRed, STRBUFFER, '\0');
        theme.player = jstr(BGTeal, FGBlack, STRBUFFER, '\0');
        theme.block = jstr(BGBlack, FGBlue, STRBUFFER, '\0');
        theme.path = jstr(BGLGreen, FGBlack, STRBUFFER, '\0');
        theme.air = jstr(BGWhite, FGBlack, STRBUFFER, '\0');
        theme.screen = jstr(BGLGray, FGBlue, STRBUFFER, '\0');
    }
    return theme;
}

char* jstr(char* str1, char* str2, int strBuffer, char endChar){
    int len1 = strlen(str1), len2 = strlen(str2);
    int i, strIndex = 0;
    if (strBuffer <= (len1 + len2)){
        return NULL;
    }
    char* str = (char*) malloc(sizeof(strBuffer));
    for (i = 0; i < len1; (i++, strIndex++)){
        str[strIndex] = str1[i];
    }
    for (i = 0; i < len2; (i++, strIndex++)){
        str[strIndex] = str2[i];
    }
    str[strIndex] = endChar;
    return str;
}

void disloveTheme(Theme theme){
    free(theme.wall);
    free(theme.player);
    free(theme.block);
    free(theme.block);
    free(theme.path);
    free(theme.air);
    free(theme.screen);
}
