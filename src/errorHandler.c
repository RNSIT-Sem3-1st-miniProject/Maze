
#include "../headders/main.h"

ErrorList* createErrorList(){
    ErrorList* list = (ErrorList*)malloc(sizeof(ErrorList));
    list->size = 0;
    list->start = NULL;
    list->end = NULL;
    return list;
}

void deleteErrorList(ErrorList* list){}

void addNewElement(ErrorList* list, ERROR* error){}

void displayErrorList(ErrorList* list){}

void errorHandel(ErrorList* list, int handelCode){}
