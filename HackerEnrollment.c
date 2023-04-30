#include "friendShipFunc.h"
#include "HackerEnrollment.h"

int (*functionTab[])(void*, void*) ={IDdiff, nameDistance} ;

void initArray(void** arr,int length){
    int i = 0;
    while(i < length+1){
        arr[i] = NULL;
        i++;
    }
}

void initStudent(Student* s){
    s->firstName=0;
    s->lastName=0;
    s->city=0;
    s->department=0;
}

void freeArray(void** arr,int currIndex){
    while(currIndex >= 0){
        free(arr[currIndex]);
    }
    free(arr);
}


int nbOfLinesInFile(FILE* f){
    if(!f){
        return -1;
    }
    int counter = 0;
    char c ;
    while((c=fgetc(f)) != EOF){
        if(c == '\n'){
            counter++;
        }
    }
    return counter;
}

void deleteStudentArray(Student** studentArr, int index){
    int i=0;
    while(studentArr[i]<index){
        free(studentArr[i]->firstName);
        free(studentArr[i]->lastName);
        free(studentArr[i]->city);
        free(studentArr[i]->department);
        free(studentArr[i]);
        i++;
    }
    free(studentArr);
}

bool getCharacter(char** param, FILE* inputFile) {
    char temp;
    int charCounter = 0;
    *param = malloc(1 * sizeof(char));
    if (*param == NULL) {
        return false;
    }
    while ((temp = fgetc(inputFile)) != EOF && temp != '\n' && temp != ' ') {
        charCounter++;
        *param = realloc(*param, (charCounter + 1) * sizeof(char));
        if (*param == NULL) {
            return false;
        }
        (*param)[charCounter - 1] = temp;
    }
    (*param)[charCounter] = '\0';
    return true;
}

bool readLine(char** buffer, FILE* inputFile) {
    int bufferSize = 100;
    int charCounter = 0;
    *buffer = (char*) malloc(bufferSize * sizeof(char));
    if (*buffer == NULL) {
        return false;
    }
    char c = fgetc(inputFile);
    while (c != EOF && c != '\n') {
        (*buffer)[charCounter++] = c;
        if (charCounter == bufferSize) {
            bufferSize *= 2;
            *buffer = (char*) realloc(*buffer, bufferSize * sizeof(char));
            if (*buffer == NULL) {
                return false;
            }
        }
        c = fgetc(inputFile);
    }
    (*buffer)[charCounter] = '\0';
    return true;
}

Student** studentEnrollment(FILE* students,int linesInStudentFile){
    Student** arrayOfPtrStudent = malloc((linesInStudentFile+1) * sizeof(arrayOfPtrStudent));
    if(!arrayOfPtrStudent){
        return NULL;
    }
    initArray((void**)arrayOfPtrStudent,linesInStudentFile);
    for(int i=0;i<linesInStudentFile;i++){
        arrayOfPtrStudent[i] = malloc(sizeof(Student));
        initStudent(arrayOfPtrStudent[i]);
        if(!arrayOfPtrStudent[i]){
            freeArray((void**)arrayOfPtrStudent,i);
            return NULL;
        }

        fscanf(students, "%s %d %lf", arrayOfPtrStudent[i]->id, &arrayOfPtrStudent[i]->totalCredits, &arrayOfPtrStudent[i]->gpa);
        arrayOfPtrStudent[i] -> id[IDLEN] = '\0';
        if(!getCharacter(&arrayOfPtrStudent[i]->firstName,students)||!getCharacter(&arrayOfPtrStudent[i]->lastName,students)
        ||!getCharacter(&arrayOfPtrStudent[i]->city,students)||!getCharacter(&arrayOfPtrStudent[i]->department,students)){
            deleteStudentArray(arrayOfPtrStudent, i);
            return NULL;
        }
    }
    return arrayOfPtrStudent;
}



Hacker ** hackerEnrollment(FILE* hackers,int linesInHackerFile, int numOfStudents){
    Hacker **  hackerArr = malloc(((linesInHackerFile/4)+1)*sizeof(hackerArr));
    int i =0;
    if(!hackerArr){
        return NULL;
    }
    initArray((void**)hackerArr,numOfStudents);

    while(linesInHackerFile>=4){
        hackerArr[i]=malloc(sizeof(Hacker));
        if(hackerArr[i]==NULL){
            freeArray((void**)hackerArr,i);
            return NULL;
        }
        fscanf(hackers,"%d",hackerArr[i]->id);

        if(!readLine(&hackerArr[i]->desiredCourses,hackers)){
            freeHackerStrings(hackerArr,i);
            freeArr((void**)hackerArr,i);
            rewind(hackers);
            return NULL;
        }
        if(!readLine(&hackerArr[i]->friendsId,hackers)){
            free(hackerArr[i]->desiredCourses);
            freeHackerStrings(hackerArr,i);
            freeArr((void**)hackerArr,i);
            rewind(hackers);
            return NULL;
        }
        if(!readLine(&hackerArr[i]->enemiesId,hackers)){
            free(hackerArr[i]->friendsId);
            free(hackerArr[i]->desiredCourses);
            freeHackerStrings(hackerArr,i);
            freeArr((void**)hackerArr,i);
            rewind(hackers);
            return NULL;
        }
        linesInHackerFile=linesInHackerFile-4;
        i++;
    }
    return hackerArr;
}

EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers){
    EnrollmentSystem system = malloc(sizeof(*system));
    if(!system) {
        return NULL;
    }

    system->f_students = studentEnrollment(students, nbOfLinesInFile(students));
    if(!system->f_students){
        free(system);
        return NULL;
    }

    system->f_courses = courseEnrollment(courses, nbOfLinesInFile(courses));
    if(!system->f_courses){
        // free student
        free(system);
        return NULL;
    }

    system->f_hackers = hackerEnrollment(hackers, nbOfLinesInFile(hackers));
    if(!system->f_hackers){
        //free students
        freeArray((void**)system->courseArr,linesIncourseFile-1);
        free(system);
        return NULL;
    }


    return system;
}


