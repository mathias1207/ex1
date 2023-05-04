#include "IsraeliQueue.h"
#include <stdlib.h>

IsraeliQueue ImproveNode(IsraeliQueue q, Node toImprove);
//done
IsraeliQueue IsraeliQueueCreate(FriendshipFunction* friendshipFunction, ComparisonFunction comparisonFunction, int friendship_th, int rivalry_th){
    IsraeliQueue q = malloc(sizeof (*q));
    if(!q) {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    q->size = 0;
    q->friendshipThreshold = friendship_th;
    q->rivalryThreshold = rivalry_th;
    q->tail = NULL;
    q->friendshipFunction = friendshipFunction;
    q->comparisonFunction = comparisonFunction;
    return q;
}

//done
IsraeliQueue IsraeliQueueClone(IsraeliQueue q){
    if (!q) return ISRAELIQUEUE_BAD_PARAM;
    IsraeliQueue new_q = IsraeliQueueCreate(q->friendshipFunction, q->comparisonFunction, q->friendshipThreshold, q->rivalryThreshold);
    if (new_q == NULL) {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    for (Node node = q->tail; node != NULL; node = node->next) {
        IsraeliQueueEnqueue(new_q, node->data);
    }
    return new_q;
}

//done
void IsraeliQueueDestroy(IsraeliQueue q){
    if (!q) return;
    Node to_delete = q->tail;

    while(to_delete->next){
        Node temp = to_delete;
        to_delete = to_delete->next;
        free(temp);
    }
    free(q->friendshipFunction);
    free(q->comparisonFunction);
    free(to_delete);
    free(q);
}

//done
bool IsraeliQueueContains(IsraeliQueue q, void *item) {
    if (!q || !item) return false;

    Node current = q->tail;
    while (current->next) {
        if (current->data == item) return true;
        current = current->next;
    }
    return false;
}

IsraeliQueueError IsraeliQueueEnqueue(IsraeliQueue q, void* item){
    if(q==NULL||item==NULL){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    Node new_node = malloc(sizeof(*new_node));
    if (!new_node){
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    new_node->data = item;
    new_node->friend_count = 0;
    new_node->rival_count = 0;
    new_node->next = q->tail;
    q->tail = new_node;
    q->size++;
    ImproveNode(q, new_node);
    return ISRAELIQUEUE_SUCCESS;
}


IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction friendships_function){
    if (!q || !friendships_function){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    int count = 0;
    while(q->friendshipFunction[count]){
        count++;
    }
    FriendshipFunction *new_friendship_functions = (FriendshipFunction*)realloc(q->friendshipFunction, (count+1) * sizeof(FriendshipFunction));
    if (new_friendship_functions == NULL) {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    q->friendshipFunction = new_friendship_functions;
    q->friendshipFunction[q->size] = friendships_function;
    q->size++;
    return ISRAELIQUEUE_SUCCESS;
}


//done
IsraeliQueueError IsraeliQueueUpdateFriendshipThreshold(IsraeliQueue q, int n_thresh){
    if (!q){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->friendshipThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

//done
IsraeliQueueError IsraeliQueueUpdateRivalryThreshold(IsraeliQueue q, int n_thresh){
    if (!q){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    q->rivalryThreshold = n_thresh;
    return ISRAELIQUEUE_SUCCESS;
}

//done
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
    Node node = queue->tail;
    Node previous = node;
    while (node->next){
        previous = node;
        node= node->next;
    }
    previous->next = NULL;
    queue->size--;
    void* toReturn = node->data;
    free(node);
    return toReturn;
}

void IsraeliQueueInsertNode(IsraeliQueue q, Node obj_node, void* item) {
    if (q == NULL || item == NULL) {
        return;
    }
    if(q->size == 1){
        Node newNode = malloc(sizeof (*newNode));
        newNode->data = item;
        newNode->next = q->tail;
        q->tail = item;
        return;
    }

    Node previous = q->tail ;
    Node current = previous->next;

    while(current != obj_node) {
        previous = current;
        current = current->next;
    }
    Node newNode = malloc(sizeof (*newNode));
    newNode->data = item;
    newNode->next = previous->next;
    previous->next = item;
}

void IsraeliQueueRemoveNode(IsraeliQueue q, Node item) {
    if (q == NULL || q->tail == NULL || item == NULL) {
        return;
    }
    // If node is the tail, update accordingly
    if (item == q->tail) {
        q->tail = item->next;
        free(item);
        return;
    } else {
        Node prev = q->tail;
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
    int i, friendshipThresholdAverage;
    for (i = 0; friend_func_arr[i] != NULL; i++) {
        friendshipThresholdAverage += friend_func_arr[i](item1, item2);
        if (is_friends(item1, item2, q)) {
            return false;
        }
    }
    if  (friendshipThresholdAverage/i<enemy_threshold){
        return true;
    }
    return false;
}

IsraeliQueue ImproveNode(IsraeliQueue q, Node toImprove){
    //find the enemy
    Node potential_enemy = toImprove->next;
    while (potential_enemy->next) {
            if (is_enemy(toImprove->data, potential_enemy->data,q) && potential_enemy->rival_count <= RIVAL_QUOTA) {
                potential_enemy->rival_count++;
                break;
        }
    }
    // find the friend
    Node last_friend = toImprove;
    Node curr = toImprove->next;
    while (curr->next != potential_enemy || curr->next != NULL) {
        if (is_friends(toImprove->data, curr->data, q) && curr->friend_count <= FRIEND_QUOTA) {
            last_friend = curr->next;
        }
        curr=curr->next;
    }
    last_friend->friend_count++;
    IsraeliQueueRemoveNode(q, toImprove);
    IsraeliQueueInsertNode(q, last_friend, toImprove);
}

IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue q){
    Node curr = q->tail;
    while(curr->next){
        ImproveNode(q, curr);
        curr = curr->next;
    }
    return ISRAELIQUEUE_SUCCESS;
}

// a reflechir et terminer
IsraeliQueue IsraeliQueueMerge(IsraeliQueue *qarr, ComparisonFunction compare_function) {
    if (qarr == NULL) return NULL; // Return NULL if qarr is NULL
    int num_queues = 0;
    // Calculate the number of queues in qarr
    int merged_friendship_threshold = 0;
    int merged_rivalry_threshold_sum = 0;
    for (int i; qarr[num_queues] != NULL; i++) {
        merged_friendship_threshold += qarr[i]->friendshipThreshold;
        merged_rivalry_threshold_sum += abs(qarr[i]->rivalryThreshold);
        num_queues++;
    }
    // Return NULL if there are no queues in qarr
    if (num_queues == 0) return NULL;

    // Calculate the "membership dimensions" of the merged queues
    merged_friendship_threshold /= num_queues;
    int merged_rivalry_threshold = merged_rivalry_threshold_sum / num_queues;
    if (merged_rivalry_threshold_sum % num_queues != 0) {
        merged_rivalry_threshold++; // Round up if necessary
    }

    // Create a new queue with the calculated membership dimensions and comparison function
    IsraeliQueue merged_queue = IsraeliQueueCreate(qarr[0]->friendshipFunction, compare_function, merged_friendship_threshold, merged_rivalry_threshold);
    if (merged_queue == NULL) return NULL; // Return NULL if failed to create new queue
    // Enqueue items from each queue in round-robin order
    bool all_queues_empty = false;
    while (!all_queues_empty) {
        all_queues_empty = true;
        for (int i = 0; i < num_queues; i++) {
            if (qarr[i]->size > 0) {
                all_queues_empty = false;
                void* person = IsraeliQueueDequeue(qarr[i]);
                IsraeliQueueEnqueue(merged_queue, person);
            }
        }
    }
    return merged_queue;
}