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

}

void IsraeliQueueDestroy(IsraeliQueue){

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
