#include "IsraeliQueue.h"
#include "Node.h"
#include <stdlib.h>
#include <stdbool.h>

#define FRIEND_QUOTA 5
#define RIVAL_QUOTA 3



struct IsraeliQueue_t {
    int size;
    FriendshipFunction *friendshipFunction;
    ComparisonFunction comparisonFunction;
    Node tail;
    int friendshipThreshold;
    int rivalryThreshold;
};


//why do you update the Friendship function with a for loop and not just do assignement?
void ImproveNode(IsraeliQueue q, Node toImprove);
//done
IsraeliQueue IsraeliQueueCreate(FriendshipFunction* friendshipFunction, ComparisonFunction comparisonFunction, int friendship_th, int rivalry_th){
    IsraeliQueue q = malloc(sizeof (*q));
    if(!q) {
        return NULL;
    }
    q->size = 0;
    q->friendshipThreshold = friendship_th;
    q->rivalryThreshold = rivalry_th;
    q->tail = NULL;
    int nbOfFriendshipFunc = 0;
    while(friendshipFunction[nbOfFriendshipFunc]){
        nbOfFriendshipFunc++;
    }
    FriendshipFunction* new_tab_friendshipFunction = malloc ((nbOfFriendshipFunc+1) * sizeof(FriendshipFunction));
    for (int i=0 ; i<nbOfFriendshipFunc;i++){
        new_tab_friendshipFunction[i]=friendshipFunction[i];
    }
    new_tab_friendshipFunction[nbOfFriendshipFunc]=NULL;
    q->friendshipFunction = new_tab_friendshipFunction;
    q->comparisonFunction = comparisonFunction;
    return q;
}

//done
IsraeliQueue IsraeliQueueClone(IsraeliQueue q){
    if (!q) return NULL;
    IsraeliQueue new_q = IsraeliQueueCreate(q->friendshipFunction, q->comparisonFunction, q->friendshipThreshold, q->rivalryThreshold);
    if (new_q == NULL) {
        return NULL;
    }
    Node before= new_q->tail;
    for (Node node = q->tail; node != NULL; node = node->next) {
        Node new_node= malloc(sizeof (*new_node));
        new_node->data= node->data;
        new_node->next=NULL;
        new_node->rival_count= node->rival_count;
        new_node->friend_count= node->friend_count;
        if (!new_q->tail){
            new_q->tail=new_node;
            before= new_node;
        }
        else{
            before->next=new_node;
            before = before->next;
        }
        new_q->size++;
    }
    return new_q;
}

//done
void IsraeliQueueDestroy(IsraeliQueue q){
    if (!q) return;
    Node to_delete = q->tail;

    while(to_delete){
        Node temp = to_delete;
        to_delete = to_delete->next;
        free(temp);
    }
    free(q->friendshipFunction);
    free(q);
}

//done
bool IsraeliQueueContains(IsraeliQueue q, void *item) {
    if (!q || !item) return false;

    Node current = q->tail;
    while (current) {
        if (q->comparisonFunction(current->data , item)) return true;
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

//done
IsraeliQueueError IsraeliQueueAddFriendshipMeasure(IsraeliQueue q, FriendshipFunction friendships_function){
    if (!q || !friendships_function){
        return ISRAELIQUEUE_BAD_PARAM;
    }
    int count = 0;
    while(q->friendshipFunction[count]){
        count++;
    }
    FriendshipFunction* new_friendship_functions = (FriendshipFunction*)realloc(q->friendshipFunction, (count+2) * sizeof(FriendshipFunction));
    if (new_friendship_functions == NULL) {
        return ISRAELIQUEUE_ALLOC_FAILED;
    }
    q->friendshipFunction = new_friendship_functions;
    q->friendshipFunction[count] = friendships_function;
    q->friendshipFunction[count+1]=NULL;
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

//
void* IsraeliQueueDequeue(IsraeliQueue q){
    if (q == NULL || q->size == 0) {
        return NULL;
    }

    Node previous = NULL;
    Node current = q->tail;
    // on avance jusqua la fin
    while (current->next) {
        previous = current;
        current = current->next;
    }

    void* data = current->data;
    if (previous) {
        previous->next = NULL;
    } else {
        q->tail = NULL;
    }
    free(current);
    q->size--;
    return data;
}


//done

void IsraeliQueueInsertNode(IsraeliQueue q, Node friend, Node item) {
    // on part du principe que friend nest pas nul et existe dans la queue
    if (q == NULL || item == NULL) {
        return;
    }
// verifier que le friend est bien dans la queue
    if(q->tail == friend){ // si le friend est la tail
        item->next = q->tail;
        q->tail = item;
        return;
    }

    Node previous = q->tail ;
    Node current = q->tail->next;
    while(current && current != friend){
        previous = current;
        current = current->next;
    }
    item->next = current;
    previous->next = item;

}


void IsraeliQueueRemoveNode(IsraeliQueue q, Node item) {
    if (q == NULL || q->tail == NULL) {
        return;
    }
    // If node is the tail, update accordingly
    if (item == q->tail) {// si on eneleve le dernier
        q->tail = item->next;
        return;
    } else {
        Node prev = q->tail;
        Node curr = q->tail->next;
        while (item != curr) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
    }
}



bool is_friends(void* item1, void* item2, IsraeliQueue q){
    if (!q) return false;
    int i;
    for (i = 0; q->friendshipFunction[i] != NULL; i++) {
        if (q->friendshipFunction[i](item1, item2) > q->friendshipThreshold) {
            return true;
        }
    }
    return false;
}



bool is_enemy(void* item1, void* item2, IsraeliQueue q){
    if (!q || !*(q->friendshipFunction)) return false;
    int i, friendshipThresholdAverage=0;
    for (i=0; q->friendshipFunction[i] != NULL; i++) {
        friendshipThresholdAverage += q->friendshipFunction[i](item1, item2);
        if (is_friends(item1, item2, q)) {
            return false;
        }
    }
    if  ( friendshipThresholdAverage / i < q->rivalryThreshold){
        return true;
    }
    return false;
}



// trouve l,ennemi le plus loin juste avant un ami
Node FindFarthestEnemyBeforeFriend(IsraeliQueue q, Node toImprove,Node friend){
    Node curr = toImprove->next;
    if (!curr) return NULL;
    Node farthestEnemyBeforeFriend= NULL;

    while (curr->next && curr!=friend) {
        if (is_enemy(toImprove->data, curr->data, q) && curr->rival_count < RIVAL_QUOTA) {
            farthestEnemyBeforeFriend = curr;
        }
        curr = curr->next;
    }
    return farthestEnemyBeforeFriend;
}



// trouve l'ami le plus loin avant un ennemi
Node FindFarthestFriendBeforeEnemy(IsraeliQueue q, Node toImprove, Node enemy){
    Node lastFriendBeforeEnemy = q->tail;
    Node curr = lastFriendBeforeEnemy->next;
    while (curr  && curr != enemy) {// while current->next!= Null and current is not the enemy
        if ((is_friends(toImprove->data, curr->data, q)) && (curr->friend_count < FRIEND_QUOTA)) {
            lastFriendBeforeEnemy = curr;
        }
        curr = curr->next;
    }
    return lastFriendBeforeEnemy;
}


//check si l,ennemi qu,omn a trouve est derriere un ami
bool enemyIsBeforeFriend(Node enemy,Node friend){
    Node curr = enemy;
    while (curr){
        if (curr==friend) return true;
        curr = curr->next;
    }
    return false;
}



void ImproveNode(IsraeliQueue q, Node toImprove){
    Node enemy = NULL;
    Node friend;
    //recherche de la place
    while(1) {
        friend = FindFarthestFriendBeforeEnemy(q, toImprove, enemy);
        enemy = FindFarthestEnemyBeforeFriend(q, toImprove, friend);// le pb est la, il sort tjr que l'ennemi est null!!
        if(enemyIsBeforeFriend(enemy, friend)){
            enemy->rival_count++;
            continue;
        }
        else{
            if (friend == toImprove|| !friend) return;
            friend->friend_count++;
            IsraeliQueueRemoveNode(q, toImprove);
            IsraeliQueueInsertNode(q, friend, toImprove);
            break;
        }
    }

}



IsraeliQueueError IsraeliQueueImprovePositions(IsraeliQueue q){
    // if there is no queue, bad param
    if(!q) return ISRAELIQUEUE_BAD_PARAM;
    Node curr = q->tail;
    //if the tail is null, success
    if (curr==NULL) return ISRAELIQUEUE_SUCCESS;
    //create a new queue
    IsraeliQueue clonedQueue = IsraeliQueueClone(q);
    Node to_improve = clonedQueue->tail;

    while(to_improve){
        Node nodeInRealQ = q->tail;
        //search the node in the real queue
        while (q->comparisonFunction(to_improve->data,nodeInRealQ->data)){
            nodeInRealQ = nodeInRealQ->next;
        }
        ImproveNode(q, nodeInRealQ);
        to_improve = to_improve->next;
    }

    IsraeliQueueDestroy(clonedQueue);
    return ISRAELIQUEUE_SUCCESS;
}






IsraeliQueue IsraeliQueueMerge(IsraeliQueue* qarr, ComparisonFunction compare_function) {
    if (qarr == NULL) return NULL; // Return NULL if qarr is NULL
    int num_queues = 0;
    // Calculate the number of queues in qarr
    int merged_friendship_threshold_sum= 0;
    int merged_rivalry_threshold_sum = 0;
    for (; qarr[num_queues] != NULL; num_queues++) {
        merged_friendship_threshold_sum += qarr[num_queues]->friendshipThreshold;
        merged_rivalry_threshold_sum += abs(qarr[num_queues]->rivalryThreshold);
    }
    // Return NULL if there are no queues in qarr
    if (num_queues == 0) return NULL;

    // Calculate the "membership dimensions" of the merged queues
    int merged_friendship_threshold = merged_friendship_threshold_sum / num_queues;
    int merged_rivalry_threshold = merged_rivalry_threshold_sum / num_queues;
    if (merged_rivalry_threshold_sum % num_queues != 0) {
        merged_rivalry_threshold++; // Round up if necessary
    }

    // Create a new merged array of frienshipFunction
    int newNumberOfFriendshipFunc=0;
    for(int i=0,j=0;i<num_queues;i++){
        while (qarr[i]->friendshipFunction[j]){
            newNumberOfFriendshipFunc++;
            j++;
        }
    }
    FriendshipFunction *newTab= malloc((newNumberOfFriendshipFunc+1)*sizeof (*newTab));
    int idx = 0;
    for(int i=0;i<num_queues;i++){
        FriendshipFunction* cur = qarr[i]->friendshipFunction;
        while (*cur){
            newTab[idx] = *cur;
            idx++;
            cur++;
        }
    }
    newTab[newNumberOfFriendshipFunc]=NULL;


    IsraeliQueue merged_queue = IsraeliQueueCreate(newTab, compare_function, merged_friendship_threshold, merged_rivalry_threshold);
    if (merged_queue == NULL) return NULL; // Return NULL if failed to create new queue
    // Enqueue items from each queue in round-robin order
    bool all_queues_empty = false;
    while (!all_queues_empty) {
        all_queues_empty = true;
        for (int i = 0; i < num_queues; i++) {
            if (qarr[i]->size > 0) {
                all_queues_empty = false;
                void* person = IsraeliQueueDequeue(qarr[i]);
                if (person != NULL) {
                    IsraeliQueueEnqueue(merged_queue,person);// ne pas remettre les comteurs a 0!!
                }
                //IsraeliQueueImprovePositions(merged_queue);
            }
        }
    }
    return merged_queue;
}