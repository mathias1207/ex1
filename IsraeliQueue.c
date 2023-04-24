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

void IsraeliQueueInsertNode(IsraeliQueue q, Node obj_node, Node item) {
    if (q == NULL || item == NULL) {
        return;
    }
    if(q->size == 1){
        item->next = q->item_tail;
        q->item_tail = item;
        return;
    }

    Node previous = q->item_tail ;
    Node current = previous->next;

    while(current != obj_node) {
        previous = current;
        current = current->next;
    }
    item->next = previous->next;
    previous->next = item;
}

void IsraeliQueueRemoveNode(IsraeliQueue q, Node item) {
    if (q == NULL || q->item_tail == NULL || item == NULL) {
        return;
    }
    // If node is the tail, update accordingly
    if (item == q->item_tail) {
        q->item_tail = item->next;
        free(item);
        return;
    } else {
        Node prev = q->item_tail;
        Node curr = prev->next;
        while (curr != item) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        free(item);
    }
}

bool is_friends(void* item1, void* item2, IsraeliQueue q){
    FriendshipFunction* friend_func_arr = q->friendshipFunction;
    int friend_threshold = q->friendshipThreshold;
    int i;
    for (i = 0; friend_func_arr[i] != NULL; i++) {
        if (friend_func_arr[i](item1, item2) >= friend_threshold) {
            return true;
        }
    }
    return false;
}


bool is_enemy(void* item1, void* item2, IsraeliQueue q){
    FriendshipFunction* friend_func_arr = q->friendshipFunction;
    int enemy_threshold = q->rivalryThreshold;
    int i;
    for (i = 0; friend_func_arr[i] != NULL; i++) {
        if (friend_func_arr[i](item1, item2) >= enemy_threshold) {
            return false;
        }
    }
    return true;
}

IsraeliQueue ImproveItem(IsraeliQueue q, Node item){
    //find the enemy
    Node potential_enemy = item->next;
    while (potential_enemy->next) {
            if (is_enemy(item, potential_enemy,q) && potential_enemy->rival_count <= RIVAL_QUOTA) {
                potential_enemy->rival_count++;
                break;
        }
    }
    // find the friend
    Node last_friend = item;
    Node curr = item->next;
    while (curr->next != potential_enemy || curr->next != NULL) {
        if (is_friends(item, curr, q) && curr->friend_count <= FRIEND_QUOTA) {
            last_friend = curr->next;
        }
        curr=curr->next;
    }
    last_friend->friend_count++;
    IsraeliQueueRemoveNode(q, item);
    IsraeliQueueInsertNode(q, last_friend, item);
}

IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue q){
    Node curr = q->item_tail;
    while(curr->next){
        ImproveItem(q, curr);
        curr = curr->next;
    }
    return ISRAELIQUEUE_SUCCESS;
}

IsraeliQueue IsraeliQueueMerge(IsraeliQueue*,ComparisonFunction){
    //TODO

}
