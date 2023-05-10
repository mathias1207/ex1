//
// Created by Ruben on 21/04/2023.
//

#ifndef EX1_HACKENROLLMENT_H
#define EX1_HACKENROLLMENT_H
#include "../IsraeliQueue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define IDLEN 9
#define MAX_FRIENDS 20




typedef struct {
    int id;
    int* desiredCourses;
    int* friendsId;
    int* enemiesId;
} Hacker;


typedef struct{
    int id ;
    int totalCredits;
    float gpa;
    char* firstName;
    char* lastName;
    char* city;
    char* department;
    Hacker* hacker;
} Student;


typedef struct Course_t{
    int courseSize;
    int courseNumber;
    IsraeliQueue queue;
} Course;


typedef struct enrollmentSystem{
    Student** f_students;
    Course** f_courses;
    Hacker** f_hackers;
    bool not_case_sensitive;
} *EnrollmentSystem;


/**recieves an EnrollmentSystem that contains the students given in the students  file
 * the courses given in the courses file and the hackers given in the hackers file
 * @param students -the students file
 * @param courses- the courses file
 * @param hackers the hackers file
 * @return
 */
EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers);


/**reads the queue given as a parameter and returns an israeli queue
 * contains EnrollmentSystem structure
 *
 * @param sys the enrolment system structure paramter
 * @param queues the queues file
 * @return
 */
EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues);


/**prints to out file all a new queue in which every hacker is in  the courses he demanded
 * or he will get the massage "Cannot satisfy constraints for <Student ID>"
 *
 * @param sys the enrolment system structure paramter
 * @param out the file we print into the corrected queues for each course
 */

void hackEnrollment(EnrollmentSystem sys, FILE* out);

void DestroyEnrollment(EnrollmentSystem sys);


#endif //EX1_HACKENROLLMENT_H
