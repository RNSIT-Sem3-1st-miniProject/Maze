
#include "../headders/main.h"

int main(){
    Point* point = createPoint(777, 444);
    printf("Maze\n");
    printPoint(point);
    free(point);
    return 0;
}
