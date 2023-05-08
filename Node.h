//
// Created by Ruben on 08/05/2023.
//

#ifndef EX1_NODE_H
#define EX1_NODE_H
typedef struct node{
    void* data;
    struct node* next;
    int friend_count;
    int rival_count;
}*Node;
#endif //EX1_NODE_H
