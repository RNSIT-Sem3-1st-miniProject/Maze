# Maze

# about the project

This is the MAZE project written by 3 RNSIT collage students, it runs in terminal/command prompt
it is a single player game, to win the game you have to solve 9 randomly generated maze,
the player can travel in the maze using WASD keys to go up : W, right : A, down : S, and left : D. 

HAVE FUN PLAYING THE MAZE GAME...!

# src files information

This project is written using on C language,
This program is divided into many sub programs :- 
    1> creating maze                                                    : maze.c
    2> handeling the player input                                       : playerIN.c
    3> finding solution for the generated maze                          : solution.c
    4> handeling the player data, and ordered generation of the maze    : Game.c
    5> other small functionalities (handeling points, CLS, PAUSE)       : utilites.c
    6> linkedlist datatype used as stack and queue, used by solution    : LinkedList.c

The src folder containes all the sorce files, and the compiled binary is present in the main project folder
The headders folder contains the "main.h" in which all declaritions for all the functions has been done

# compiling the code

This code can be compiled for windows and linux computers but the src files has to changed a little bit

for compiling for linux the #define COMPILE_MECHINE is set to LINUX, and the line number 9 in main.h file is uncomented
and for compiling this is how you do it : 
    "gcc gcc main.c maze.c utilities.c LinkedList.c Game.c solution.c playerIN.c -o .././maze"

for compiling for windows the #define COMPILE_MECHINE is set to WINDOWS, and the line number 9 in main.h file is comented
and for compiling this is how you do it : 
    "gcc gcc main.c maze.c utilities.c LinkedList.c Game.c solution.c playerIN.c -o ..\\maze.exe"

# Contributers

Vasu.Subbannavar    1RN19IS173
Suprith.S   1RN19IS
Yesh.S  1RN19IS
