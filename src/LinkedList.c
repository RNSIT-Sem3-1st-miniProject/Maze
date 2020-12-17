
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
