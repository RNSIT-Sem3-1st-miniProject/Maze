
#include "../headders/main.h"

int main(){
    char* data = readFile("../database/test.json");
    printf("\ntesting : %s\n", data);
    writeFile("../database/wtest.json", data);
    free(data);
    return 0;
}

bool isDebugOn(){
    return false;
}
