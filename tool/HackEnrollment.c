#include "HackEnrollment.h"
#define RIVALRY_TRESHOLD 0
#define FRIENDSHIP_TRESHOLD 20
#define BUFFER 1000
#define MAXID 999999999
#define MINID 100000000
#define MAX_LINE_LENGTH 1000
#define HACKERLINE 4
#define COURSE_SUCCESS_TH 2
#include <stdlib.h>
#include "../Node.h"

struct IsraeliQueue_t {
    int size;
    FriendshipFunction *friendshipFunction;
    ComparisonFunction comparisonFunction;
    Node tail;
    int friendshipThreshold;
    int rivalryThreshold;
};

void fillhackerInfo(Student *enroll, Hacker *ptr);

/////////////////////////////////////friendshipFunctions//////////////////////////////////////////////////////////
int nameDistanceCapital(void* stu1, void* stu2){
    Student* student1 = (Student*) stu1;
    Student* student2 = (Student*) stu2;
    char* name1 = student1->firstName;
    char* name2 = student2->firstName;
    char* surname1 = student1->lastName;
    char* surname2 = student2->lastName;
    int total = 0;

    while (*name1 != '\0' && *name2 != '\0') {
        if (*name1 != *name2) {
            total++;
        }
        name1++;
        name2++;
    }
    while (*surname1 != '\0' && *surname2 != '\0') {
        if (*surname1 != *surname2) {
            total++;
        }
        surname1++;
        surname2++;
    }
    while (*name1 != '\0') {
        total += *name1;
        name1++;
    }
    while (*name2 != '\0') {
        total += *name2;
        name2++;
    }
    while (*surname1 != '\0') {
        total += *surname1;
        surname1++;
    }
    while (*surname2 != '\0') {
        total += *surname2;
        surname2++;
    }
    return total;
}

int tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    } else {
        return c;
    }
}

int nameDistanceNoCapital(void* stu1, void* stu2) {
    Student* student1 = (Student*) stu1;
    Student* student2 = (Student*) stu2;
    char* name1 = student1->firstName;
    char* name2 = student2->firstName;
    char* surname1 = student1->lastName;
    char* surname2 = student2->lastName;
    int total = 0;

    while (*name1 != '\0' && *name2 != '\0') {
        char letter1 = tolower(*name1);
        char letter2 = tolower(*name2);
        if (letter1 != letter2) {
            total++;
        }
        name1++;
        name2++;
    }

    while (*surname1 != '\0' && *surname2 != '\0') {
        char letter1 = tolower(*surname1);
        char letter2 = tolower(*surname2);

        if (letter1 != letter2) {
            total++;
        }

        surname1++;
        surname2++;
    }

    while (*name1 != '\0') {
        total += *name1;
        name1++;
    }

    while (*name2 != '\0') {
        total += *name2;
        name2++;
    }

    while (*surname1 != '\0') {
        total += *surname1;
        surname1++;
    }

    while (*surname2 != '\0') {
        total += *surname2;
        surname2++;
    }

    return total;
}


int IdDiff (void* id1, void* id2){
    return abs(*((int*)(id1))-*((int*)(id2)));
}

int hackerFriendshipVal(void* h, void* s) {
    int i = 0;
    Student* hacker = (Student *) h;
    Student* student = (Student*) s;
    if (hacker->hacker->friendsId){
    while (hacker->hacker->friendsId[i]) {
        if (hacker->hacker->friendsId[i] == student->id) {
            return 20;
        }
        i++;
    }}
    i=0;
    if (hacker->hacker->enemiesId) {
        while (hacker->hacker->enemiesId[i]) {
            if (hacker->hacker->enemiesId[i] == student->id) {
                return -20;
            }
            i++;
        }
    }
    return 0;
}



bool hackerSatisfied(int countSuccessCourses, Hacker* hacker){
    if (countSuccessCourses == COURSE_SUCCESS_TH - 1 && hacker->desiredCourses[0] != 0 && hacker->desiredCourses[1] == 0){
        return true;
    }
    else if (countSuccessCourses >= COURSE_SUCCESS_TH){
        return true;
    }
    else if(hacker->desiredCourses[0] == 0){
        return true;
    }
    return false;
}


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
    return NULL;
}



void initArray(void** arr,int length){
    int i = 0;
    while(i < length){
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


void freeStudentArray(Student ** stuArr){
    int i=0;
    while(stuArr[i]){
        free(stuArr[i]->lastName);
        free(stuArr[i]->firstName);
        free(stuArr[i]->department);
        free(stuArr[i]->city);
//        if (stuArr[i]->hacker){
//            free(stuArr[i]->hacker);
//        }
        free(stuArr[i]);
        i++;
    }
    free(stuArr);
}

void freeCoursesArray(Course ** courseArr){
    int i=0;
    while(courseArr[i]){
        IsraeliQueueDestroy(courseArr[i]->queue);
        i++;
    }
    free(courseArr);
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

    //newStudent->hacker=NULL;
    return newStudent;
}


Student** studentEnrollment(FILE* students,int linesInStudentFile) {
    Student **arrayOfPtrStudent = malloc((linesInStudentFile+1) * sizeof(Student*));
    if (!arrayOfPtrStudent) {
        return NULL;
    }
    // je sais pas si ce init array marche
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
    if (*str == '\n') return 0;
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

        // Traiter la liste des cours
        if (number_courses > 0) {
            int* courses = malloc((number_courses+1) * sizeof(int));
            int offset = 0;
            int off = 0;
            for (int i = 0; i < number_courses; i++){
                sscanf(line[1] + offset, "%d %n", &courses[i], &off);
                offset+= off;
            }
            courses[number_courses] = 0;
            hacker->desiredCourses = courses;
        } else {
            hacker->desiredCourses = malloc(sizeof(int));
            hacker->desiredCourses[0] = 0;
        }

        // Traiter la liste des amis
        if (number_friends > 0) {
            int* friends = malloc((number_friends+1) * sizeof(int));
            int offset = 0;
            int off = 0;
            for (int i = 0; i < number_friends; i++){
                sscanf(line[2] + offset, "%d %n", &friends[i], &off);
                offset+= off;
            }
            friends[number_friends] = 0;
            hacker->friendsId = friends;
        } else {
            hacker->friendsId = malloc(sizeof (int ));
            hacker->friendsId[0] = 0;
        }

        // Traiter la liste des ennemis
        if (number_enemies > 0) {
            int* enemies = malloc((number_enemies+1) * sizeof(int));
            int offset = 0;
            int off= 0;
            for (int i = 0; i < number_enemies; i++){
                sscanf(line[3] + offset, "%d %n", &enemies[i], &off);
                offset+= off;
            }
            enemies[number_enemies] = 0;
            hacker->enemiesId = enemies;
        } else {
            hacker->enemiesId = malloc(sizeof (int));
            hacker->enemiesId[0] = 0;
        }

        return hacker;

}

Hacker** hackerEnrollment(FILE* hackers, int numOfStudents) {
    // Créer le tableau de pointeurs de Hacker
    Hacker** hackerArray = malloc((numOfStudents+1) * sizeof(Hacker*));

    // Lire chaque ligne du fichier et créer un objet Hacker correspondant
    char line[HACKERLINE][BUFFER];
    int i = 0;
    int numHacker = 0;
    int lineCount = 0;
    while (fgets(line[i], BUFFER, hackers)) {
        lineCount++;
        i++;
        if (i == HACKERLINE){
            Hacker* hacker = createHackerFromLine(line);
            hackerArray[numHacker] = hacker;
            numHacker++;
            i = 0;
            lineCount = 0;
        }
    }
    if (lineCount > 0) {
        if (lineCount==3){
            line[3][0]='\0';
        } else if (lineCount==2){
            line[2][0]='\0';
            line[3][0]='\0';

        }
        else if (lineCount==1){
            line[1][0]='\0';
            line[2][0]='\0';
            line[3][0]='\0';
        }
        Hacker* hacker = createHackerFromLine(line);
        hackerArray[numHacker] = hacker;
        numHacker++;
    }
    hackerArray[numHacker] = NULL;
    return hackerArray;
}

//////////////////////////////courseEnrollement///////////////////////////////////////


Course* createCourseFromLine(char* line) {
    Course* course = malloc(sizeof(Course));
    if (*line=='0'||*line=='\n') return NULL;
    sscanf(line, "%d %d", &(course->courseNumber), &(course->courseSize));
    course->queue = IsraeliQueueCreate(NULL, cmprStudent, FRIENDSHIP_TRESHOLD,RIVALRY_TRESHOLD);
    return course;
}

Course** courseEnrollment(FILE* courses, int linesInCourseFile) {
    Course** courseArray = malloc((linesInCourseFile+1) * sizeof(Course*));
    if(!courseArray){
        return NULL;
    }
    initArray((void**)courseArray,linesInCourseFile+1);
    int i = 0;
    char line[BUFFER];
    while (fgets(line, BUFFER, courses)) {
        Course* course = createCourseFromLine(line);
        if (course != NULL) {
            courseArray[i] = course;
            i++;
        }
        //else courseArray[linesInCourseFile]=NULL;
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
    system->not_case_sensitive=false;

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

    system->f_hackers = hackerEnrollment(hackers, nbOfLinesInFile(hackers) / HACKERLINE);
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
    for (int i = 0; sys->f_students[i] != NULL; i++) {
            count++;
    }
    return count;
}

int numOfHackers(EnrollmentSystem sys){
    int count = 0;
    for (int i = 0; sys->f_hackers[i] != NULL; i++) {
            count++;
    }
    return count;
}

int findCourse(EnrollmentSystem sys, long courseNumber) {
    Course** course= sys->f_courses;
    for (int i = 0; i < numOfCourses(sys); i++) {
        if (course[i]->courseNumber == courseNumber) {
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
            continue;
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
    Course** course= sys->f_courses;
    for(int i =0; course[i]!=NULL; i++){
        if (sys->not_case_sensitive){
        IsraeliQueueAddFriendshipMeasure(course[i]->queue, &nameDistanceNoCapital);
        } else {
            IsraeliQueueAddFriendshipMeasure(course[i]->queue, &nameDistanceCapital);
        }
        IsraeliQueueAddFriendshipMeasure(course[i]->queue, &IdDiff);
        IsraeliQueueAddFriendshipMeasure(course[i]->queue, &hackerFriendshipVal);
    }
    return sys;
}




/////////////////////////////////////////hackEnrollement////////////////////////////////////////////////////////


int numOfDesiredCoursesByHacker(EnrollmentSystem sys, int hackerId) {
    int numHackers = numOfHackers(sys); // nombre de hackers
    for (int i = 0; i < numHackers; i++) {
        if (sys->f_hackers[i]->id == hackerId) {
            int numDesiredCourses = 0;
            for (int j = 0; sys->f_hackers[i]->desiredCourses[j] != 0; j++) {
                    numDesiredCourses++;
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

//bool isInQueue(Course* course, Hacker* student, int sizeOfCourse) {
//    Node curr= course->queue->tail;
//    for (int i = 0; i <= sizeOfCourse; i++) {
//        if (((Student*)(curr->data))->id == student->id) {
//            return true;
//        }
//        curr= curr->next;
//    }
//    return false;
//}

bool isInCourse(Course* course, Hacker* student){
    IsraeliQueue clonedQueue = IsraeliQueueClone(course->queue);
    for (int i = 0; i < IsraeliQueueSize(course->queue); i++){
        Student* curr = IsraeliQueueDequeue(clonedQueue);
        if (curr->id == student->id && i < course->courseSize){
            IsraeliQueueDestroy(clonedQueue);
            return true;
        }
    }
    IsraeliQueueDestroy(clonedQueue);
    return false;
}


void hackEnrollment(EnrollmentSystem sys, FILE *out) {
    for (int i = 0; i < numOfHackers(sys); i++) {
        int numDesiredCourses = numOfDesiredCoursesByHacker(sys, sys->f_hackers[i]->id);
        int countCoursesNo = 0;
        Student* hackerToEnroll= findStudent(sys->f_students, sys->f_hackers[i]->id);
        fillhackerInfo(hackerToEnroll,sys->f_hackers[i]);
        for (int j = 0; j < numDesiredCourses; j++) {
            int courseNumber = sys->f_hackers[i]->desiredCourses[j];
            int courseIndex = findCourse(sys, courseNumber);
            if (courseIndex == -1) {
                continue;
            }
            Course *course = sys->f_courses[courseIndex];
            IsraeliQueueEnqueue(course->queue, hackerToEnroll);
             if (isInCourse(course, sys->f_hackers[i])) {
                countCoursesNo++;
            }
        }
        if (!hackerSatisfied(countCoursesNo, sys->f_hackers[i])) {
            fprintf(out, "Cannot satisfy constraints for %d\n", sys->f_hackers[i]->id);
            return;
        }

    }
        for (int k = 0; k < numOfCourses(sys); k++) {
            writeEnrollmentQueue(out, sys->f_courses[k]);
        }
}

void fillhackerInfo(Student *student, Hacker *ptr) {
    student->hacker= malloc(sizeof (Hacker*));
    student->hacker->desiredCourses= ptr->desiredCourses;
    student->hacker->id= ptr->id;
    student->hacker->enemiesId = ptr->enemiesId;
    student->hacker->friendsId = ptr->friendsId;
}

/////////////////////////////////////////freeEnrollmentSystem////////////////////////////////////////////////////////

void DestroyEnrollment(EnrollmentSystem sys){
    if(sys == NULL){
        return;
    }
    freeCoursesArray(sys->f_courses);
    freeStudentArray(sys->f_students);
    freeArray((void**)sys->f_hackers, numOfHackers(sys));
    free(sys);
}