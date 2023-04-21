#include "friendShipFunc.h"
#include "HackerEnrollment.h"

int (*functionTab[])(void*, void*) ={IDdiff, nameDistance} ;


EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers){
    EnrollmentSystem ptr = malloc(sizeof(*ptr));
    if(!ptr) {
        return NULL;
    }
    ptr->f_students = students;
    ptr->f_courses = courses;
    ptr->f_hackers = hackers;
    IsraeliQueue enrollment = IsraeliQueueCreate(functionTab, );
    return ptr;
}


