//
// Created by Ruben on 21/04/2023.
//

#ifndef EX1_HACKERENROLLMENT_H
#define EX1_HACKERENROLLMENT_H
#include "../IsraeliQueue.h"
#include <stdio.h>
#include <string.h>
#define IDLEN 9
#define MAX_FRIENDS 20



typedef struct{
    int id ;             //9 digits
    int totalCredits;   //>=0
    float gpa;          //0<=num<=100
    char* firstName;
    char* lastName;
    char* city;
    char* department;
} Student;


typedef struct {
    int id;                     //9 digit num
    int* desiredCourses;       //expectation to be only numbers
    int* friendsId;            //9 digit number array
    int* enemiesId;            //9 digit num
} Hacker;


typedef struct {
    int courseSize;
    int courseNumber;
    IsraeliQueue queue;
} Course;


typedef struct enrollmentSystem{
    Student** f_students;
    Course** f_courses;
    Hacker** f_hackers;
} *EnrollmentSystem;


EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);

void hackEnrollment(EnrollmentSystem sys, FILE* out);




#endif //EX1_HACKERENROLLMENT_H