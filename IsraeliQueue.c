#include "IsraeliQueue.h"
#include <stdlib.h>


IsraeliQueue IsraeliQueueCreate(FriendshipFunction * friendshipFunction, ComparisonFunction comparisonFunction, int friendship_th, int rivalry_th){
    IsraeliQueue q = malloc(sizeof (*q));
    q->size = NULL;
    q->friendshipThreshold = friendship_th;
    q->rivalryThreshold = rivalry_th;
    q->item_tail = NULL;
    q->friendshipFunc_list =friendshipFunction;
    q->comparaisonFunc_list = comparisonFunction;

}

IsraeliQueue IsraeliQueueClone(IsraeliQueue q){
    IsraeliQueue new_q = malloc(sizeof (*q));
    new_q->size = q->size;
    new_q->friendshipThreshold = q->friendshipThreshold;
    new_q->rivalryThreshold = q->rivalryThreshold;
    new_q->item_tail = q->item_tail;
    new_q->friendshipFunc_list = q->friendshipFunc_list;
    new_q->comparaisonFunc_list = q->comparaisonFunc_list;

    return new_q;
}

void IsraeliQueueDestroy(IsraeliQueue q){
    Node to_delete = q->item_tail;
    while(to_delete != NULL){
        Node temp = to_delete;
        to_delete = to_delete->next;
        free(to_delete);
    }
    free(q->friendshipFunc_list);
    free(q->comparaisonFunc_list);
    free(q);
}

IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue q, void* item){
    Node new_node;
    new_node->data= item;
    new_node->next= q->item_tail;
    q->item_tail= &new_node;
}


IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction
friendships_function){


}

IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int n_thresh){
    // TODO bdika
    q->friendshipThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int n_thresh){
    // TODO bdika
    q->rivalryThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

int IsraeliQueueSize(IsraeliQueue q){
    return q->size;
}



void* IsraeliQueueDequeue(IsraeliQueue){

}
