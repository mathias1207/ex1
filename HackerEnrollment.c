//
// Created by Ruben on 21/04/2023.
//
#include "HackerEnrollment.h"
#include <stdlib.h>

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers){
    EnrollmentSystem ptr = malloc(sizeof(*ptr));
    if(!ptr) {
        return NULL;
    }
    ptr.f_students = students;
    ptr.f_courses = courses;
    ptr.f_hackers = hackers;
    return ptr;
}


