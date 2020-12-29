#include <stdlib.h>

int main(){
    system("gcc main.c maze.c utilities.c LinkedList.c Game.c solution.c playerIN.c -o .././maze"); // for linux
    //system("gcc main.c maze.c utilities.c LinkedList.c Game.c solution.c playerIN.c -o ..\\maze.exe"); // for windows
    return 0;
}
