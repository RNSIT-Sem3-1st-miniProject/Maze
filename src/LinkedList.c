
#include "../headders/main.h"

PNode* createPNode(Point point)
{
    PNode* node = (PNode *)malloc(sizeof(PNode));
    node->point = point;
    node->next = NULL;
    return node; 
} 

void deletePNode(PNode *node)
{
    free(node);
}

LL* createLL()
{
    LL* ll = (LL *)malloc(sizeof(LL));
    ll->start = NULL;
    ll->end = NULL;
    ll->size = 0;
    return ll;
}

int getLLsize(LL* ll)
{
    return ll->size;
}
void deleteLL(LL* ll){
    PNode* del = ll->start;
    while(del != NULL){
        ll->start = del->next;
        deletePNode(del);
        del = ll->start;
        ll->start -= 1;
    }
    free(ll);
}

void append(LL* ll, PNode* point){
    if (ll->start == NULL){
        ll->start = point;
    }
    ll->end->next = point;
    ll->end = point;
    ll->size += 1;
}

Point pop(LL* ll, char pt){
    Point point;
    PNode* del;
    if((ll == NULL) || (ll->start == NULL)){
        return NOT_A_VALID_POINT;
    }
    if(pt == 'L'){
        point = ll->end->point;
        del = ll->start;
        while (del->next != ll->end){
            del = del->next;
        }
        ll->end = del;
        deletePNode(del->next);
    }else if(pt == 'S'){
        point = ll->start->point;
        del = ll->start;
        ll->start = del->next;
        deletePNode(del);
    }
    return point;
}

Point peep(LL* ll, char pt){
    Point point;
    if((ll == NULL) || (ll->start == NULL)){
        return NOT_A_VALID_POINT;
    }
    if(pt == 'L'){
        point = ll->end->point;
    }else if(pt == 'S'){
        point = ll->start->point;
    }
    return point;
}
