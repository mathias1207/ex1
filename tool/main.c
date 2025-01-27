
#include "./HackEnrollment.h"
#include "../IsraeliQueue.h"
#include "../Node.h"




int main(int argc, char* argv[]) {
    bool not_case_sensitive = false;

    char* students_file;
    char* courses_file;
    char* hackers_file;
    char* queues_file;
    char* out_file;

    if (argc < 6 || argc > 7) {
        printf("Erreur : nombre d'arguments invalide\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 7) {
        not_case_sensitive = strcmp(argv[1], "-i") == 0;
        students_file = argv[2];
        courses_file = argv[3];
        hackers_file = argv[4];
        queues_file = argv[5];
        out_file = argv[6];
    } else {
        // Analyser les arguments
        students_file = argv[1];
        courses_file = argv[2];
        hackers_file = argv[3];
        queues_file = argv[4];
        out_file = argv[5];
    }


    FILE* students = fopen(students_file, "r");
    FILE* courses = fopen(courses_file, "r");
    FILE* hackers = fopen(hackers_file, "r");
    FILE* queues = fopen(queues_file, "r");
    FILE* out = fopen(out_file, "w");

    if (students == NULL || courses == NULL || hackers == NULL || queues == NULL) {
        printf("Erreur : impossible d'ouvrir un fichier d'entrée\n");
        exit(EXIT_FAILURE);
    }

//    FILE* students = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\students.txt", "r");
//    FILE* courses = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\courses.txt", "r");
//    FILE* hackers = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\hackers.txt", "r");
//    FILE* queues = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\queues.txt", "r");
//    FILE* out = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\out.txt", "w");
//


    EnrollmentSystem sys = createEnrollment(students, courses, hackers);
    if (not_case_sensitive) sys->not_case_sensitive=true;

    readEnrollment(sys, queues);

    hackEnrollment(sys, out);

    DestroyEnrollment(sys);

    fclose(students);
    fclose(courses);
    fclose(hackers);
    fclose(queues);
    fclose(out);
    return 0;
}


