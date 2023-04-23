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
    q->friendshipFunction = friendshipFunction;
    q->comparisonFunction = comparisonFunction;
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
    new_q->friendshipFunction = q->friendshipFunction;
    new_q->comparisonFunction = q->comparisonFunction;

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
    free(q->friendshipFunction);
    free(q->comparisonFunction);
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
    if (!q || !friendships_function){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    FriendshipFunction *new_friendship_functions = (FriendshipFunction*)realloc(q->friendshipFunction, (q->size+1) * sizeof(FriendshipFunction));
    if (new_friendship_functions == NULL) {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    q->friendshipFunction = new_friendship_functions;
    q->friendshipFunction[q->size] = friendships_function;
    q->size++;
    return ISRAELIQUEUE_SUCCESS;

}

IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int n_thresh){
    if (!q){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->friendshipThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int n_thresh){
    if (!q){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->rivalryThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

int IsraeliQueueSize(IsraeliQueue q){
    if (!q){
        return ISRAELIQUEUE_BAD_PARAM;
    }
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
void IsraeliQueueInsertNode(IsraeliQueue q, Node ref_node, Node node) {
    if (q == NULL || node == NULL) {
        return;
    }

    if (ref_node != NULL) {
        // Insert after reference node
        node->prev = ref_node->prev->prev;
        ref_node->prev->next = ref_node;
        node->next = ref_node;
        ref_node->prev = node;
        // Update tail if necessary
        if (ref_node == q->item_tail) {
            q->item_tail = node;
        }
    }
    // Update adjacent nodes
    if (node->prev != NULL) {
        node->prev->next = node;
    }
    if (node->next != NULL) {
        node->next->prev = node;
    }
}
void IsraeliQueueRemoveNode(IsraeliQueue q, Node node) {
    if (q == NULL || q->item_tail == NULL || node == NULL) {
        return;
    }

    // If node is the head or tail, update accordingly
    if (node == q->item_tail) {
        q->item_head = node->next;
    }
    if (node == q->item_tail) {
        q->item_tail = node->next;
    }

    // Update adjacent nodes
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    free(node);
}

IsraeliQueue ImproveItem(IsraeliQueue q, void* item, FriendshipFunction friendship){
    Node curr = item;
    //find the enemy
    void* enemy = NULL;
    while (curr != NULL) {
        if (curr->data != item) {
            if (friendship(curr->data, item) <= q->rivalryThreshold) {
                enemy = curr->data;
                break;
            }
        }
        curr = curr->next;
    }
    // find the friend
    void* friend = NULL;
    curr = curr->prev;
    while (curr != NULL) {
        if (curr->data != item && !friendship(curr->data, item)) {
            if (friendship(curr->data, item) >= q->friendshipThreshold ) {
                friend = curr->data;
                break;
            }
        }
        curr = curr->prev;
    }
    IsraeliQueueRemoveNode(q, item);
    IsraeliQueueInsertNode(q, friend, item);
}

IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue q){
    Node curr = q->item_tail;
    while(curr != NULL){
        ImproveItem(q, curr, q->friendshipFunction);
    }
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueue IsraeliQueueMerge(IsraeliQueue*,ComparisonFunction){
    //TODO

}
