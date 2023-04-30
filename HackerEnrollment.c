#include "friendShipFunc.h"
#include "HackerEnrollment.h"

int (*functionTab[])(void*, void*) ={IDdiff, nameDistance} ;


EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers){
    EnrollmentSystem system = malloc(sizeof(*system));
    if(!system) {
        return NULL;
    }

    system->f_courses = courseEnrollment(courses,linesIncourseFile);
    if(!system->courseArr){
        free(system);
        return NULL;
    }

    system->f_hackers = hackerEnrollment(hackers,linesInHackerFile,linesInStudentFile,linesInHackerFile);
    if(!system->f_hackers){
        freeArr((void**)system->courseArr,linesIncourseFile-1);
        free(system);
        return NULL;
    }

    system->f_courses = studentEnrollment(students,linesInStudentFile);
    if(!system->studentArr){
        freeHackerStrings(system->hackerArr,linesInHackerFile/4);
        freeArr((void**)system->courseArr,linesIncourseFile-1);
        freeArr((void**)system->hackerArr,linesInHackerFile/4-1);
        free(system);
        return NULL;
    }
    return system;
}


