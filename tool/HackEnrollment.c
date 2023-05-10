#include "HackEnrollment.h"
#define RIVALRY_TRESHOLD 0
#define FRIENDSHIP_TRESHOLD 20
#define BUFFER 1000
#define MAXID 999999999
#define MINID 100000000
#define MAX_LINE_LENGTH 1000
#include <stdlib.h>
#include "../Node.h"

/////////////////////////////////////friendshipFunctions//////////////////////////////////////////////////////////
int nameDistance(void* stu1, void* stu2){
    int sum = 0;
    int i;
    char* name1 = ((Student*)(stu1))->firstName;
    char* name2 = ((Student*)(stu2))->firstName;
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

int IdDiff (void* id1, void* id2){
    return abs(*((int*)(id1))-*((int*)(id2)));
}

int hackerFriendshipVal(void* h, void* s) {
    int i = 0;
    Hacker* hacker = (Hacker*) h;
    Student* student = (Student*) s;
    while (hacker->friendsId[i]) {
        if (hacker->friendsId[i] == student->id) {
            return 20;
        } else if (hacker->enemiesId[i] == student->id) {
            return -20;
        }
        i++;
    }
    return 0;
}

int (*functionTab[])(void*, void*) ={(int (*)(void *, void *)) IdDiff, (int (*)(void *, void *)) nameDistance,
                                     (int (*)(void *, void *)) hackerFriendshipVal} ;

//////////////////////////////////////////////////////////////////////////////////////////////////

int stringToInt(char *str) {
    if (str == NULL) {
        return 0;
    }
    int sign = 1;
    int result = 0;
    char *ptr = str;
    if (*ptr == '-') {
        sign = -1;
        ptr++;
    }
    while (*ptr != '\0') {
        if (*ptr >= '0' && *ptr <= '9') {
            result = result * 10 + (*ptr - '0');
            ptr++;
        } else {
            printf("La chaîne contient des caractères non-numériques.\n");
            exit(1);
        }
    }
    return result * sign;
}



Student* findStudent(Student** studentList, int ID){
    if(ID == 0 || studentList == NULL){
        return NULL;
    }
    int i =0;
    while (studentList[i]){
        if(ID == (studentList[i]->id)) {
            return studentList[i];
        }
        i++;
    }
    return -1;
}





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
        currIndex--;
    }
    free(arr);
}

int nbOfLinesInFile(FILE* f){
    if(!f){
        return -1;
    }
    int counter = 0;
    char c ;
    while((c = fgetc(f)) != EOF){
        if(c == '\n'){
            counter++;
        }
    }
    fseek(f, 0, SEEK_SET);
    return counter;
}

void destroyHacker(void* hacker){
    if(hacker == NULL) {
        return;
    }
    //destroy lists of friend et enemy
    free(hacker);
}

void destroyStudent(Student * student){
    if(student == NULL) {
        return;
    }
    destroyHacker(student->hacker);
    free(student);
}

void deleteStudentArray(Student** studentArr, int index){
    int i=0;
    while(i<index){
        free(studentArr[i]->firstName);
        free(studentArr[i]->lastName);
        free(studentArr[i]->city);
        free(studentArr[i]->department);
        free(studentArr[i]);
        i++;
    }
    free(studentArr);
}

//reads a string and returns the first word before a space or the end of the string
char* getWord(char* line) {
    if(line == NULL || line[0] == '\0'){
        return NULL;
    }
    int i = 0;
    while(line[i] != '\0' && line[i] != ' ' && line[i] != '\n') {
        i++;
    }
    if(i == 0) {
        return NULL;
    }
    line[i] = '\0';
    char* newWord = (char*)malloc((i + 1) * sizeof(char));
    if(newWord == NULL)
    {
        return NULL;
    }
    for(int j = 0 ; j <= i ; j++) {
        newWord[j] = line[j];
    }
    int j = 0;
    while(line[j + i + 1] != '\0'){
        line[j] = line[j + i + 1];
        j++;
    }
    while(i >= 0){
        line[j + i] = '\0';
        i--;
    }
    return newWord;
}



bool isEmpty(FILE* file) {
    return feof(file);
}


char *readLine(FILE *fichier) {
    char temp[MAX_LINE_LENGTH+1];
    char *line = NULL;

    if (fgets(temp, MAX_LINE_LENGTH, fichier) == NULL) {
        return NULL;
    }
    line = malloc(strlen(temp)+1);
    if (line == NULL) {
        return NULL;
    }
    strcpy(line,temp);
    return line;
}


bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isGoodId(const char* str) {
    int i =0;
    while (isDigit(str[i])) {
        i++;
    }
    if (i!=IDLEN){
        return false;
    }
    return true;
}


int cmprStudent(void* stu1, void* stu2){
    return ((Student*)(stu1))->id == ((Student*)(stu2))->id;
}



////////////////////////////studentEnrollement///////////////////////////////////////////////////


Student* createStudentFromLine(char* line) {
    Student* newStudent = malloc(sizeof(Student));
    if (newStudent == NULL) {
        return NULL;
    }
    if(line == NULL){
        return NULL;
    }
    char temp_firstname[MAX_LINE_LENGTH];
    char temp_lastname[MAX_LINE_LENGTH];
    char temp_city[MAX_LINE_LENGTH];
    char temp_department[MAX_LINE_LENGTH];
    sscanf(line, "%d %d %f %s %s %s %s", &(newStudent->id), &(newStudent->totalCredits), &(newStudent->gpa), temp_firstname, temp_lastname, temp_city, temp_department);

    newStudent->firstName = malloc(strlen(temp_firstname) + 1);
    strcpy(newStudent->firstName, temp_firstname);

    newStudent->lastName = malloc(strlen(temp_lastname) + 1);
    strcpy(newStudent->lastName, temp_lastname);

    newStudent->city = malloc(strlen(temp_city) + 1);
    strcpy(newStudent->city, temp_city);

    newStudent->department = malloc(strlen(temp_department) + 1);
    strcpy(newStudent->department, temp_department);

    return newStudent;
}


Student** studentEnrollment(FILE* students,int linesInStudentFile) {
    Student **arrayOfPtrStudent = malloc((linesInStudentFile+1) * sizeof(Student*));
    if (!arrayOfPtrStudent) {
        return NULL;
    }
    initArray((void **) arrayOfPtrStudent, linesInStudentFile);
    int i=0;
    while (!isEmpty(students)) {
        char* line = readLine(students);
        arrayOfPtrStudent[i] = malloc(sizeof(Student));
        initStudent(arrayOfPtrStudent[i]);
        if (!arrayOfPtrStudent[i]) {
            freeArray((void **) arrayOfPtrStudent, i);
            return NULL;
        }
        arrayOfPtrStudent[i]= createStudentFromLine(line);
        i++;
    }
    return arrayOfPtrStudent;
}
////////////////////////////hackerEnrollement///////////////////////////////////////////////////




int countWords(char* str) {
    int count = 0;
    int state = 0;

    // Parcourir la chaîne caractère par caractère
    for (int i = 0; str[i] != '\0'; i++) {
        // Si le caractère courant est un espace, changer l'état en "hors d'un mot"
        if (str[i] == ' ') {
            state = 0;
        }
            // Si le caractère courant est un caractère alphabétique, numérique ou autre, et que nous ne sommes pas dans un mot, changer l'état en "dans un mot" et augmenter le compteur
        else if (state == 0) {
            state = 1;
            count++;
        }
    }
    return count;
}


Hacker* createHackerFromLine(char line[4][BUFFER]) {

    // Créer l'objet Hacker
    Hacker* hacker = malloc(sizeof(Hacker));
    sscanf(line[0], "%d", &(hacker->id));

    int number_courses = countWords(line[1]);
    int number_friends = countWords(line[2]);
    int number_enemies = countWords(line[3]);
    int* courses = malloc((number_courses+1) * sizeof(int));
    int* friends = malloc((number_friends+1) * sizeof(int));
    int* enemies = malloc((number_enemies+1) * sizeof(int));

    int offset = 0;
    int off = 0;
    for (int i = 0; i < number_courses; i++){
        sscanf(line[1] + offset, "%d %n", &courses[i], &off);
        offset+= off;
    }
    courses[number_courses] = 0;

    offset = 0;
    off = 0;
    for (int i = 0; i < number_friends; i++){
        sscanf(line[2] + offset, "%d %n", &friends[i], &off);
        offset+= off;
    }
    friends[number_friends] = 0;

    offset = 0;
    off= 0;
    for (int i = 0; i < number_enemies; i++){
        sscanf(line[3] + offset, "%d %n", &enemies[i], &off);
        offset+= off;
    }
    enemies[number_enemies] = 0;

    hacker->desiredCourses = courses;
    hacker->friendsId = friends;
    hacker->enemiesId = enemies;

    return hacker;
}

Hacker** hackerEnrollment(FILE* hackers, int numOfStudents) {
    // Créer le tableau de pointeurs de Hacker
    Hacker** hackerArray = malloc((numOfStudents+1) * sizeof(Hacker*));

    // Lire chaque ligne du fichier et créer un objet Hacker correspondant
    char line[4][BUFFER] = {0};
    int i = 0;
    int numHacker = 0;
    while (fgets(line[i], BUFFER, hackers)) {
        if (i==3){
            Hacker* hacker = createHackerFromLine( line);
            i = 0;
            hackerArray[numHacker] = hacker;
            numHacker++;
        }
        else{
            i++;
        }
    }
    return hackerArray;
}

//////////////////////////////courseEnrollement///////////////////////////////////////


Course* createCourseFromLine(char* line) {
    Course* course = malloc(sizeof(Course));
    sscanf(line, "%d %d", &(course->courseNumber), &(course->courseSize));
    course->queue = IsraeliQueueCreate(NULL, cmprStudent, FRIENDSHIP_TRESHOLD,RIVALRY_TRESHOLD);
    return course;
}

Course** courseEnrollment(FILE* courses, int linesInCourseFile) {
    Course** courseArray = malloc((linesInCourseFile+1) * sizeof(Course*));
    if(!courseArray){
        return NULL;
    }
    initArray((void**)courseArray,linesInCourseFile);
    int i = 0;
    char line[BUFFER];
    while (fgets(line, BUFFER, courses)) {
        Course* course = createCourseFromLine(line);
        if (course != NULL) {
            courseArray[i] = course;
            i++;
        }
    }

    return courseArray;
}

////////////////////////////////createEnrollement///////////////////////////////////////



EnrollmentSystem createEnrollment(FILE* students, FILE* courses, FILE* hackers){
    if(students == NULL || courses == NULL || hackers == NULL){
        return NULL;
    }
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
        freeArray((void**)system->f_courses, nbOfLinesInFile(courses)-1);
        free(system);
        return NULL;
    }
    return system;
}


/////////////////////////////////////////readEnrollment////////////////////////////////////////////////////////


int numOfCourses(EnrollmentSystem sys) {
    int count = 0;
    Course** course = sys->f_courses;
    for (int i = 0; course[i] != NULL; i++) {
            count++;
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

int numOfHackers(EnrollmentSystem sys){
    int count = 0;
    for (int i = 0; sys->f_hackers[i] != NULL; i++) {
        if (sys->f_hackers[i] != NULL) {
            count++;
        }
    }
    return count;
}

int findCourse(EnrollmentSystem sys, long courseNumber) {
    Course* course= sys->f_courses[0];
    for (int i = 0; i < numOfCourses(sys); i++) {
        if ((course[i]).courseNumber == courseNumber) {
            return i;
        }
    }
    return -1;
}

Student* findStudentById(int studentId, EnrollmentSystem sys) {
    int numStudents = numOfStudents(sys);
    for (int i = 0; i < numStudents; i++) {
        if (sys->f_students[i]->id == studentId) {
            return sys->f_students[i];
        }
    }
    return NULL;
}


EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE* queues){
    if(sys == NULL || queues == NULL) {
        return NULL;
    }
    int linesInQueue = nbOfLinesInFile(queues);
    if (linesInQueue < 0) {
        return NULL;
    }
    if (linesInQueue == 0) {
        return sys;
    }
    while(!isEmpty(queues)){
        char* line = readLine(queues);
        if(line == NULL){
            return NULL;
        }
        int courseNum = stringToInt(getWord(line));
        int courseId = findCourse(sys, courseNum);
        Course* course = sys->f_courses[courseId];
        int studentID = stringToInt(getWord(line));
        int i= 0;
        while (studentID != 0){
            Student* student = findStudent(sys->f_students, studentID);
            if(student == NULL){
                free(line);
                return NULL;
            }
            if(!IsraeliQueueContains(course->queue, student)){
                IsraeliQueueEnqueue(course->queue, student);
            }
            studentID = stringToInt(getWord(line));
            i++;
        }
        free(line);
    }
    return sys;
}




/////////////////////////////////////////hackEnrollement////////////////////////////////////////////////////////


int numOfDesiredCoursesByHacker(EnrollmentSystem sys, int hackerId) {
    int numHackers = numOfHackers(sys); // nombre de hackers
    for (int i = 0; i < numHackers; i++) {
        if (sys->f_hackers[i]->id == hackerId) {
            int numDesiredCourses = 0;
            for (int j = 0; j < numOfCourses(sys); j++) {
                if (sys->f_hackers[i]->desiredCourses[j] != 0) {
                    numDesiredCourses++;
                }
            }
            return numDesiredCourses;
        }
    }
    return 0;
}


void writeEnrollmentQueue(FILE *out, Course *course) {
    if (!IsraeliQueueSize(course->queue)) {
        return;
    }
    fprintf(out, "%d", course->courseNumber);
    Student* head = IsraeliQueueDequeue(course->queue);
    while (head) {
        fprintf(out, " %d", head->id);
        head =(Student*) IsraeliQueueDequeue(course->queue);
    }
    fprintf(out, "\n");
}


void hackEnrollment(EnrollmentSystem sys, FILE *out) {
    for (int i = 0; i < numOfHackers(sys); i++) {
        int numDesiredCourses = numOfDesiredCoursesByHacker(sys, sys->f_hackers[i]->id);
        int countCoursesRejected = 0;

        for (int j = 0; j < numDesiredCourses; j++) {
            int courseNumber = sys->f_hackers[i]->desiredCourses[j];
            int courseIndex = findCourse(sys, courseNumber);
            if (courseIndex == -1) {
                continue;
            }
            Course *course = sys->f_courses[courseIndex];
            int sizeOfQueue = IsraeliQueueSize(course->queue);

            IsraeliQueueAddFriendshipMeasure(course->queue, &nameDistance);
            IsraeliQueueAddFriendshipMeasure(course->queue, &IdDiff);
            IsraeliQueueAddFriendshipMeasure(course->queue, &hackerFriendshipVal);

            if (IsraeliQueueContains(course->queue, sys->f_hackers[i])) {
                continue;
            } else if (sizeOfQueue == course->courseSize) {
                countCoursesRejected++;
            } else if (IsraeliQueueEnqueue(course->queue, sys->f_hackers[i]) != ISRAELIQUEUE_SUCCESS) {
                countCoursesRejected++;
            }
            if (countCoursesRejected == 2) {
                fprintf(out, "Cannot satisfy constraints for %d\n", sys->f_hackers[i]->id);
                exit(0);
            }
        }

    }
        for (int k = 0; k < numOfCourses(sys); k++) {
            writeEnrollmentQueue(out, sys->f_courses[k]);
        }
}