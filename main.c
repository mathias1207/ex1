
#include "HackerEnrollment.h"



//
//
//void HackEnrollment(bool case_sensitive, char* students_file, char* courses_file, char* hackers_file, char* queues_file, char* out_file) {
//    // Ouvrir les fichiers d'entrée
//    FILE* students = fopen(students_file, "r");
//    FILE* courses = fopen(courses_file, "r");
//    FILE* hackers = fopen(hackers_file, "r");
//    FILE* queues = fopen(queues_file, "r");
//    FILE* out = fopen(out_file, "r");
//
//
//    // Vérifier si les fichiers ont été ouverts avec succès
//    if (students == NULL || courses == NULL || hackers == NULL || queues == NULL) {
//        printf("Erreur : impossible d'ouvrir un fichier d'entrée\n");
//        exit(EXIT_FAILURE);
//    }
//
//    // Créer le système d'inscription
//    EnrollmentSystem sys = createEnrollment(students, courses, hackers);
//
//    // Lire la file d'attente d'inscription
//    sys = readEnrollment(sys, queues);
//
//    // Fermer le fichier de file d'attente
//    fclose(queues);
//
//    // Hacker l'ordre d'inscription
//    hackEnrollment(sys, out);
//
//    // Fermer les fichiers d'entrée et de sortie
//    fclose(students);
//    fclose(courses);
//    fclose(hackers);
//    fclose(out);
//}
//
//
//
//int main(int argc, char* argv[]) {
//    bool case_sensitive = true;
//    char* students_file;
//    char* courses_file;
//    char* hackers_file;
//    char* queues_file;
//    char* out_file;
//
//    // Vérifier le nombre d'arguments
//    if (argc < 6 || argc > 7) {
//        printf("Erreur : nombre d'arguments invalide\n");
//        exit(EXIT_FAILURE);
//    }
//
//    // Vérifier si le premier argument est présent
//    if (argc == 7) {
//        // Analyser les arguments
//        case_sensitive = strcmp(argv[1], "i") != 0;
//        students_file = argv[2];
//        courses_file = argv[3];
//        hackers_file = argv[4];
//        queues_file = argv[5];
//        out_file = argv[6];
//    } else {
//        // Analyser les arguments
//        students_file = argv[1];
//        courses_file = argv[2];
//        hackers_file = argv[3];
//        queues_file = argv[4];
//        out_file = argv[5];
//    }
//
//    // Lancer la fonction HackEnrollment
//    HackEnrollment(case_sensitive, students_file, courses_file, hackers_file, queues_file, out_file);
//
//    return 0;
//}
//
//
//
//
//
//
//


int comparison_function_mock(void *obj1, void *obj2) {
    int id1 = *(int *)obj1;
    int id2 = *(int *)obj2;

    return id1 - id2;
}

int mockfriendshipfunction(void* firstObject, void* secondObject){
    int temp = (*(int*)firstObject)+(*(int*)firstObject)+5;
    return temp;
}


//
//int main(){
//    int arr[]={1,2,3,4};
//    FriendshipFunction functions[]={mockfriendshipfunction, NULL};
//    IsraeliQueue queue=IsraeliQueueCreate(functions, comparison_function_mock, 100, 0);
//    for (int i=0; i<4; i++){
//        IsraeliQueueEnqueue(queue, &arr[i]);
//    }
//    IsraeliQueueAddFriendshipMeasure(queue, mockfriendshipfunction);
//    IsraeliQueue p=IsraeliQueueClone(queue);
//    IsraeliQueue j=IsraeliQueueClone(queue);
//    IsraeliQueue m=IsraeliQueueClone(queue);
//    IsraeliQueue s=IsraeliQueueClone(queue);
//    IsraeliQueueDequeue(p);
//    IsraeliQueueDequeue(p);
//    IsraeliQueueDequeue(j);
//    IsraeliQueueDequeue(j);
//    IsraeliQueueDequeue(j);
//    IsraeliQueueDequeue(m);
//
//    IsraeliQueueImprovePositions(queue);
//
//    IsraeliQueue f[]={queue, p, j, m, s , NULL};
//    IsraeliQueue g = IsraeliQueueMerge(f, comparison_function_mock);
//    IsraeliQueueDestroy(queue);
//
//    Node toPrint= g->tail;
//    for (int i=0; i< g->size;i++){
//        printf("%d->", *(int*)(toPrint->data));
//        toPrint= toPrint->next;
//    }
//    return 0;
//}
//
///* Check your IsraeliQueue g. It's supposed to be: start->4->3->4->2->1->3->4->3->2->2->4->3->1->4->end
//*/







//int comparison_function_mock(void *obj1, void *obj2) {
//    int id1 = *(int *)obj1;
//    int id2 = *(int *)obj2;
//
//    return id1 - id2;
//}
//int mockfriendshipfunction(void* firstObject, void* secondObject){
//    int temp = (*(int*)firstObject)+(*(int*)firstObject)+50;
//    return temp;
//}


int main(){
    // test 1

    /* iterations:
    1 2 3 4 5 6 7 8 9 10 11 12 <-original
    1 12 2 3 4 5 6 7 8 9 10 11
    1 11 12 2 3 4 5 6 7 8 9 10
    1 10 11 12 2 3 4 5 6 7 8 9
    1 9 10 11 12 2 3 4 5 6 7 8
    1 8 9 10 11 12 2 3 4 5 6 7
    1 8 7 9 10 11 12 2 3 4 5 6
    1 8 6 7 9 10 11 12 2 3 4 5
    1 8 5 6 7 9 10 11 12 2 3 4
    1 8 4 5 6 7 9 10 11 12 2 3
    1 8 3 4 5 6 7 9 10 11 12 2
    1 8 3 2 4 5 6 7 9 10 11 12
    8 3 1 2 4 5 6 7 9 10 11 12

     */
    int arr[]={1,2,3,4,5,6,7,8,9,10,11,12};
    FriendshipFunction functions[]={NULL};
    IsraeliQueue queue=IsraeliQueueCreate(functions, comparison_function_mock, 0, 0);

    for (int i=0; i<12; i++){
        IsraeliQueueEnqueue(queue, &arr[i]);

    }
    IsraeliQueueAddFriendshipMeasure(queue, mockfriendshipfunction);
    IsraeliQueueImprovePositions(queue);
    printf("Test1:\nYour output: ");
    for (int i=0; i<12; i++){
        int s=*(int*)IsraeliQueueDequeue(queue);
        printf("%d ", s);
    }
    printf("\nExpected:    8 3 1 2 4 5 6 7 9 10 11 12\n");
    IsraeliQueueDestroy(queue);

    // test 2
    /*iterations:
    1:  *4
    2:  4 *3
    3:  4 *4 3
    4:  4 *1 4 3
    5:  4 *3 1 4 3
    6:  4 *4 3 1 4 3
    7:  4 4 *2 3 1 4 3
    8:  4 4 *2 2 3 1 4 3
    9:  4 4 *3 2 2 3 1 4 3
    10: 4 4 *1 3 2 2 3 1 4 3
    11: 4 4 *4 1 3 2 2 3 1 4 3
    12: 4 4 4 *5 1 3 2 2 3 1 4 3


    */
    queue=IsraeliQueueCreate(functions, comparison_function_mock, 0, 0);
    for (int i=0; i<4; i++){
        IsraeliQueueEnqueue(queue, &arr[i]);
    }
    IsraeliQueue p=IsraeliQueueClone(queue);
    IsraeliQueueImprovePositions(queue);
    int *five=malloc(sizeof(int));
    *five=5;
    IsraeliQueueEnqueue(queue, five);
    IsraeliQueue s=IsraeliQueueClone(p);
    IsraeliQueue f=IsraeliQueueClone(p);
    for (int j=0; j<2; j++){
        IsraeliQueueDequeue(p);
    }
    for (int k=0; k<3; k++){
        IsraeliQueueDequeue(s);
    }
    IsraeliQueueAddFriendshipMeasure(f, mockfriendshipfunction);
    IsraeliQueue q_arr[]={queue, p, s, f, NULL};
    IsraeliQueue result=IsraeliQueueMerge(q_arr, comparison_function_mock);
    printf("Test2:\nYour output: ");
    for (int i=0; i<12; i++){
        int s=*(int*)IsraeliQueueDequeue(result);
        printf("%d ", s);
    }
    printf("\nExpected:    4 4 4 5 1 3 2 2 3 1 4 3\n");



    return 0;
}