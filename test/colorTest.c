#include "../headders/main.h"

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


int main(){
    //printf("%s%s :: BG : %d, FG : %d", BGWhite, FGRed, strlen(BGBlue), strlen(FGRed));
    char* colourTheme = jstr(BGWhite, FGRed, 12, '\0');
    if(colourTheme == NULL){
        printf("ERROR!!\n");
        return 1;
    }
    printf("%s : %d :: ", colourTheme, strlen(colourTheme));
    printf("HII\n");
    free(colourTheme);
    sleep(5);
    printf("\n%s%s\n", BGReset, FGReset);
    return 0;
}
