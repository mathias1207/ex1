#include "IsraeliQueue.h"
#include <stdlib.h>


IsraeliQueue IsraeliQueueCreate(FriendshipFunction *, ComparisonFunction, int friendship_th, int rivalry_th){
    IsraeliQueue q = malloc(sizeof (*q));
    q.size = NULL;
    q->friendship_threshold = friendship_th;
    q.rivalry_threnshold = rivalry_th;
    q.item_tail = NULL;
    q.function_list = {FriendshipFunction *, ComparisonFunction };
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
    int size = 0;
    Node* current = tail;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return q.size * sizeof(Node*);

}


void* IsraeliQueueDequeue(IsraeliQueue){

}