#include <stdlib.h>

int main(){
    system("gcc main.c maze.c utilities.c LinkedList.c Game.c solution.c playerIN.c -o .././maze");
    system(".././maze");
    //system("gcc main.c maze.c utilities.c LinkedList.c Game.c solution.c playerIN.c -o ..\\maze.exe");
    return 0;
}
