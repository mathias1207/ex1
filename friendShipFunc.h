//
// Created by Ruben on 21/04/2023.
//

#ifndef EX1_FRIENDSHIPFUNC_H
#define EX1_FRIENDSHIPFUNC_H
#include <stdlib.h>

int nameDistance(char* name1, char* name2){
    int sum = 0;
    int i;
    for (i = 0; name1[i] != '\0' && name2[i] != '\0'; i++) {
        sum += abs(name1[i] - name2[i]);
    }
    while (name1[i] != '\0') {
        sum += name1[i];
        i++;
    }
    while (name2[i] != '\0') {
        sum += name2[i];
        i++;
    }
    return sum;
}

int IDdiff (int* id1, int* id2){
    return abs(*id1-*id2);
}


#endif //EX1_FRIENDSHIPFUNC_H
