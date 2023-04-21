#include "IsraeliQueue.h"
#include <stdlib.h>


IsraeliQueue IsraeliQueueCreate(FriendshipFunction * friendshipFunction, ComparisonFunction comparisonFunction, int friendship_th, int rivalry_th){
    IsraeliQueue q = malloc(sizeof (*q));
    if(!q) {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    q->size = NULL;
    q->friendshipThreshold = friendship_th;
    q->rivalryThreshold = rivalry_th;
    q->item_tail = NULL;
    q->friendshipFunc_list = friendshipFunction;
    q->comparaisonFunc_list = comparisonFunction;
}

IsraeliQueue IsraeliQueueClone(IsraeliQueue q){
    if (!q) return ISRAELIQUEUE_BAD_PARAM;

    IsraeliQueue new_q = malloc(sizeof (*q));
    if(!new_q) {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    new_q->size = q->size;
    new_q->friendshipThreshold = q->friendshipThreshold;
    new_q->rivalryThreshold = q->rivalryThreshold;
    new_q->item_tail = q->item_tail;
    new_q->friendshipFunc_list = q->friendshipFunc_list;
    new_q->comparaisonFunc_list = q->comparaisonFunc_list;

    return new_q;
}

void IsraeliQueueDestroy(IsraeliQueue q){
    if (!q) return;

    Node to_delete = q->item_tail;
    while(to_delete){
        Node temp = to_delete;
        to_delete = to_delete->next;
        free(to_delete);
    }
    free(q->friendshipFunc_list);
    free(q->comparaisonFunc_list);
    free(q);
}

bool IsraeliQueueContains(IsraeliQueue q, void *item) {
    if (!q || !item) return false;

    Node current = q->item_tail;
    while (current->next) {
        if (current->data=item) return true;
        current = current->next;
    }
    return false;
}

IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue q, void* item){
    Node new_node = malloc(sizeof(*new_node));
    if (!new_node) {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    new_node->data= item;
    new_node->next= q->item_tail;
    q->item_tail= &new_node;
    q->size++; // increase the size of the queue
    return ISRAELIQUEUE_SUCCESS;
}


IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction friendships_function){
    if (!q || !friendships_function) return ISRAELIQUEUE_BAD_PARAM;


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



void* IsraeliQueueDequeue(IsraeliQueue queue){
    if (queue->size == 0) {
        return NULL;
    }
    Node node = *(queue->item_tail);
    Node previous = node;
    while (node->next){
        previous = node;
        node= node->next;
    }
    previous->next = NULL;
    free(node);
    queue->size--;  // decrease the size of the queue
}
