#include "IsraeliQueue.h"


IsraeliQueue IsraeliQueueCreate(FriendshipFunction *, ComparisonFunction, int, int){

}

IsraeliQueue IsraeliQueueClone(IsraeliQueue q){

}

void IsraeliQueueDestroy(IsraeliQueue){

}

IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue q, void* item){
    Node new_node;
    new_node->data= item;
    new_node->next= q.item_tail;
    q.tail= &new_node;
}


IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction
friendships_function){


}

IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int n_thresh){
    // TODO bdika
    q.friendshipThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int n_thresh){
    // TODO bdika
    q.rivalryThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

int IsraeliQueueSize(IsraeliQueue q){
    return q.size;
}



void* IsraeliQueueDequeue(IsraeliQueue){

}
