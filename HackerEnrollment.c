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



Hacker** hackerEnrollment(FILE* hackers,int linesInHackerFile, int numOfStudents){
    Hacker**  hackerArr = malloc(((linesInHackerFile/4)+1)*sizeof(hackerArr));
    if(!hackerArr){
        return NULL;
    }

    int i =0;
    initArray((void**)hackerArr,numOfStudents);

    while(linesInHackerFile>=4){
        hackerArr[i]=malloc(sizeof(Hacker));
        if(hackerArr[i]==NULL){
            freeArray((void**)hackerArr,i);
            return NULL;
        }
        fscanf(hackers,"%s%*c",hackerArr[i]->id);
        if(!readLine(&hackerArr[i]->desiredCourses,hackers)){
            freeArray((void**)hackerArr,i);
            return NULL;
        }
        if(!readLine(&hackerArr[i]->friendsId,hackers)){
            free(hackerArr[i]->desiredCourses);
            freeArray((void**)hackerArr,i);
            return NULL;
        }
        if(!readLine(&hackerArr[i]->enemiesId,hackers)){
            free(hackerArr[i]->friendsId);
            free(hackerArr[i]->desiredCourses);
            freeArray((void**)hackerArr,i);
            return NULL;
        }
        linesInHackerFile = linesInHackerFile-HACKERSLINE;
        i++;
    }
    return hackerArr;
}

Course ** courseEnrollment(FILE* courses,int linesInCourseFile){
    Course ** courseArr = malloc((linesInCourseFile+1)*sizeof(Course*));
    if(!courseArr){
        return NULL;
    }
    initArray((void**)courseArr,linesInCourseFile);
    for (int i = 0; i < linesInCourseFile; i++){
        courseArr[i]=malloc(sizeof(Course));
        if(courseArr[i]==NULL){
            freeArray((void**)courseArr,i);
            return NULL;
        }
        fscanf(courses,"%d %d\n", &courseArr[i]->courseNumber, &courseArr[i]->courseSize);
        courseArr[i]->queue=NULL;
    }
    return courseArr;

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

    system->f_hackers = hackerEnrollment(hackers, nbOfLinesInFile(hackers), nbOfLinesInFile(students));
    if(!system->f_hackers){
        //free students
        freeArray((void**)system->f_courses, nbOfLinesInFile(courses)-1);
        free(system);
        return NULL;
    }


    return system;
}


int numOfCourses(EnrollmentSystem sys){
    int count = 0;
    for (int i = 0; i!=EOF; i++) {
        if (sys->f_courses[i]->courseNumber != NULL) {
            count++;
        }
    }
    return count;
}
int numOfStudents(EnrollmentSystem sys){
    int count = 0;
    for (int i = 0; i!=EOF; i++) {
        if (sys->f_students[i] != NULL) {
            count++;
        }
    }
    return count;
}
int numOfHackerFriends(Hacker *h) {
    int count = 0;
    for (int i = 0; i < MAX_FRIENDS ; i++) { // MAX_FRIENDS 20 ?
        if (h->friendsId[i] != NULL) {
            count++;
        }
    }
    return count;
}


int findCourse(EnrollmentSystem sys, int courseNumber) {
    int numCourses = numOfCourses(sys);
    for (int i = 0; i < numCourses; i++) {
        if (sys->f_courses[i]->courseNumber == courseNumber) {
            return sys->f_courses[i]->courseNumber;
        }
    }
    return -1;
}
Student* findStudentById(int studentId, EnrollmentSystem sys) {
    int numStudents = numOfStudents(sys);
    for (int i = 0; i < numStudents; i++) {
        if (sys->f_students[i]->id == studentId) { // il faut peut etre mettre studentId en int ?
            return sys->f_students[i];
        }
    }
    return NULL;
}
int findCourseIndexById(int courseId, EnrollmentSystem sys) {
    int numCourses = numOfCourses(sys);
    for (int i = 0; i < numCourses; i++) {
        if (sys->f_courses[i]->courseNumber == courseId) {
            return i;
        }
    }
    return -1;
}

bool isEnrolled(EnrollmentSystem sys, int courseId, int studentId, FILE* queues) { // Je sais que c'est faux
    // Recherche du cours correspondant
    int courseIndex = findCourseIndexById(courseId, sys);
    if (courseIndex < 0) {
        return false;
    }

    // Ouverture du fichier contenant les inscriptions des étudiants au cours
    FILE *fp = fopen(queues, "r");
    if (fp == NULL) {
        return 0;
    }

    // Recherche de l'étudiant correspondant
    int studentFound = 0;
    int student;
    while (fscanf(fp, "%d ", &student) == 1) {
        if (student == studentId) {
            studentFound = 1;
            break;
        }
    }
    // Fermeture du fichier
    fclose(fp);
}

void hackerEnrollmentfunctions(IsraeliQueue *queue, const void *hackerId, void *hacker, EnrollmentSystem sys,
                                   FILE *queues) { // il faut qu'on fasse bien cette fonction
        Hacker *h = (Hacker *) hacker;
        int id = *((int *) hackerId);
        int numFriends = numOfHackerFriends(h);

        // Parcours des amis du hacker
        for (int i = 0; i < numFriends; i++) {
            int friendId = h->friendsId[i];
            Student *s = findStudentById(friendId, sys);
            if (s == NULL) continue;

            // Vérification si l'étudiant est inscrit au cours désiré
            if (!isEnrolled(s, h->desiredCourses[0])) continue;

            // Calcul de la distance du nom et de la différence de numéro ID
            int nameDistance = calculateNameDistance(h->name, s->name);
            int idDifference = abs(h->id - friendId);

            // Ajout du hacker à la file d'inscription de l'étudiant
            int priority = nameDistance + idDifference;
            IsraeliQueuePush(queue, hacker, priority);
        }
    }


EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE *queues) {
        int linesInQueue = nbOfLinesInFile(queues);
        if (linesInQueue < 0) {
            return NULL;
        }
        if (linesInQueue == 0) {
            return sys;
        }

        int courseNumber;
        while (fscanf(queues, "%d ", &courseNumber) == 1) {
            int courseIndex = findCourse(sys, courseNumber);
            if (courseIndex == -1) {
                continue;
            }
            Course *course = sys->f_courses[courseIndex];
            course->queue = IsraeliQueueCreate(hackerEnrollmentfunctions, NULL, FRIENDSHIP_TH, ENEMY_TH);
            if (course->queue == NULL) {
                for (int i = 0; i < courseIndex; i++) {
                    IsraeliQueueDestroy(sys->f_courses[i]->queue);
                }
                return NULL;
            }
        }
        return sys;
    }


