#include "HackerEnrollment.h"
#define HACKERSLINE 4
#define RIVALRY_TRESHOLD 0
#define FRIENDSHIP_TRESHOLD 20
#define BUFFER 1000
#define MAXID 999999999
#define MINID 100000000


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

int IdDiff (const int* id1, const int* id2){
    return abs(*id1-*id2);
}

int hackerFriendshipVal(Hacker* hacker, Student* student) {
    int i = 0;
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
    while((c=fgetc(f)) != EOF){
        if(c == '\n'){
            counter++;
        }
    }
    return counter;
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



int parseInt(char* str) {
    int result = 0;
    int i = 0;
    while (isDigit(str[i])) {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

float parseFloat(char* str) {
    float result = 0;
    int i = 0;
    while (isDigit(str[i])) {
        result = result * 10 + (float)(str[i] - '0');
        i++;
    }
    if (str[i] == '.') {
        i++;
        float factor = (float) 0.1;
        while (isDigit(str[i])) {
            result += (float)(str[i]-'0') * factor;
            factor /= 10;
            i++;
        }
    }
    return result;
}

char* readString(char* str, int* i) {
    int start = *i;
    while (str[*i] != ' ' && str[*i] != '\n') {
        (*i)++;
    }
    char* result = malloc(*i - start + 1);
    strncpy(result, &str[start], *i - start);
    result[*i - start] = '\0';
    return result;
}

Student* createStudentFromLine(char* line,Student* student) {
    char* id = readString(line, &(int){0});
    if (!isGoodId(id)) {
        return NULL;
    }
    student->id = parseInt(id);
    int i = IDLEN+1;
    student->totalCredits = parseInt(line + i);
    i ++;
    while (line[i] != ' ') {
        i++;
    }
    i++;
   student->gpa = parseFloat(line + i);
    i++;
    while (line[i] != ' ') {
        i++;
    }
    i++;
    student->firstName = readString(line, &i);
    student->lastName = readString(line, &i);
    student->city = readString(line, &i);
    student->department = readString(line, &i);
    return student;
}

Student** studentEnrollment(FILE* students,int linesInStudentFile) {
    Student **arrayOfPtrStudent = malloc((linesInStudentFile) * sizeof(Student *));
    if (!arrayOfPtrStudent) {
        return NULL;
    }
    initArray((void **) arrayOfPtrStudent, linesInStudentFile);
    int i=0;
    char line[BUFFER];
    while (fgets(line, BUFFER, students) != NULL) {
        arrayOfPtrStudent[i] = malloc(sizeof(Student));
        initStudent(arrayOfPtrStudent[i]);
        if (!arrayOfPtrStudent[i]) {
            freeArray((void **) arrayOfPtrStudent, i);
            return NULL;
        }
        createStudentFromLine(line, arrayOfPtrStudent[i]);
        i++;
        }
    return arrayOfPtrStudent;
}
////////////////////////////hackerEnrollement///////////////////////////////////////////////////


int* readIntArray(char* str, int* length) {
    int start = 0;
    int count = 0;
    while (str[start] != '\n') {
        if (isDigit(str[start])) {
            count++;
        }
        start++;
    }
    int* result = malloc(count * sizeof(int));
    int i = 0;
    while (str[*length] != '\n') {
        if (isDigit(str[*length])) {
            result[i] = parseInt(str + *length);
            i++;
            while (isDigit(str[*length])) {
                (*length)++;
            }
        }
        (*length)++;
    }
    *length++; // passer le '\n'
    return result;
}

Hacker* createHackerFromLine(char* line) {

    // Vérifier que l'ID est une chaîne de 9 chiffres
    int id = parseInt(line);
    if (id < MINID || id > MAXID) {
        return NULL;
    }

    // Lire les autres champs
    int i = IDLEN+1; // index après l'ID et le '\n'
    int* desiredCourses = readIntArray(line + i, &i);
    int* friendsId = readIntArray(line + i, &i);
    int* enemiesId = readIntArray(line + i, &i);

    // Créer l'objet Hacker
    Hacker* hacker = malloc(sizeof(Hacker));
    hacker->id = id;
    hacker->desiredCourses = desiredCourses;
    hacker->friendsId = friendsId;
    hacker->enemiesId = enemiesId;

    return hacker;
}

Hacker** hackerEnrollment(FILE* hackers, int numOfStudents) {
    // Créer le tableau de pointeurs de Hacker
    Hacker** hackerArray = malloc(numOfStudents * sizeof(Hacker*));
    int i = 0;

    // Lire chaque ligne du fichier et créer un objet Hacker correspondant
    char line[BUFFER];
    while (fgets(line, BUFFER, hackers)) {
        Hacker* hacker = createHackerFromLine(line);
        //est ce quon passe bien a l'autre
        if (hacker != NULL) {
            hackerArray[i] = hacker;
            i++;
        }
    }
    return hackerArray;
}

//////////////////////////////courseEnrollement///////////////////////////////////////


Course* createCourseFromLine(char* line) {
    if (strlen(line) < 3) {
        return NULL;
    }
    int i = 0;
    Course* course = malloc(sizeof(Course));
    course->courseNumber = parseInt(line + i);
    while (line[i] != ' ') {
        i++;
    }
    i++;
    course->courseSize = parseInt(line + i);
    return course;
}

Course** courseEnrollment(FILE* courses, int linesInCourseFile) {
    Course** courseArray = malloc(linesInCourseFile * sizeof(Course*));
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

int numOfCourses(EnrollmentSystem sys) {
    int count = 0;
    for(int i = 0; i!=EOF; i++) {
        if (sys->f_courses[i] != NULL) {
            count++;
        }
    }
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
    for (int i = 0; i!=EOF; i++) {
        if (sys->f_hackers[i] != NULL) {
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

EnrollmentSystem readEnrollment(EnrollmentSystem sys, FILE *queues) {
        int linesInQueue = nbOfLinesInFile(queues);
        if (linesInQueue < 0) {
            return NULL;
        }
        if (linesInQueue == 0) {
            return sys;
        }

        int (*functionTab[])(void*, void*) ={(int (*)(void *, void *)) IdDiff, (int (*)(void *, void *)) nameDistance,
                                             (int (*)(void *, void *)) hackerFriendshipVal} ;
        int courseNumber;
        while (fscanf(queues, "%d ", &courseNumber)) {
            int courseIndex = findCourse(sys, courseNumber);
            if (courseIndex == -1) {
                continue;
            }
            Course *course = sys->f_courses[courseIndex];
            course->queue = IsraeliQueueCreate(functionTab, NULL, FRIENDSHIP_TRESHOLD, RIVALRY_TRESHOLD);
            if (course->queue == NULL) {
                for (int i = 0; i < courseIndex; i++) {
                    IsraeliQueueDestroy(sys->f_courses[i]->queue);
                }
                return NULL;
            }
            // enter all the people into the queue of the course
            for(int i = 0; i < course->courseSize; i++){
            IsraeliQueueEnqueue(course->queue, sys->f_students[i]);
            }
        }
        return sys;
    }

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
    }

void hackEnrollment(EnrollmentSystem sys, FILE *out) {
    for (int i = 0; i < numOfHackers(sys); i++) {
        int numDesiredCourses = numOfDesiredCoursesByHacker(sys, sys->f_hackers[i]->id);

        for (int j = 0; j < numDesiredCourses; j++) {
            int courseNumber = (int) sys->f_hackers[i]->desiredCourses[j];
            int courseIndex = findCourse(sys, courseNumber);
            if (courseIndex == -1) {
                continue;
            }
            Course *course = sys->f_courses[courseIndex];
            if (IsraeliQueueEnqueue(course->queue, sys->f_hackers[i]) != ISRAELIQUEUE_SUCCESS) {
                fprintf(out, "Cannot satisfy constraints for %s\n", sys->f_hackers[i]->id);
            } else {
                IsraeliQueueEnqueue(course->queue, sys->f_hackers[i]);
            }
        }
        for (int k = 0; k < numOfCourses(sys); k++) {
            fprintf(out, "% //?\n", sys->f_courses[k]->queue);
        }
    }
}
