//
// Created by Ruben on 21/04/2023.
//

#ifndef EX1_HACKERENROLLMENT_H
#define EX1_HACKERENROLLMENT_H
#include "IsraeliQueue.h"

typedef struct enrollmentSystem{
    FILE* f_students;
    FILE* f_courses;
    FILE* f_hackers;
    IsraeliQueue queue;

} *EnrollmentSystem;


EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);

void hackEnrollment(EnrollmentSystem sys, FILE* out);


#endif //EX1_HACKERENROLLMENT_H
