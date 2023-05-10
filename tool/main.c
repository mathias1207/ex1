
#include "./HackEnrollment.h"
#include "../IsraeliQueue.h"
#include "../Node.h"



void WrapperHackEnrollment(/*bool case_sensitive,*/ char* students_file, char* courses_file, char* hackers_file, char* queues_file, char* out_file) {
    // Ouvrir les fichiers d'entrée
//    FILE* students = fopen(students_file, "r");
//    FILE* courses = fopen(courses_file, "r");
//    FILE* hackers = fopen(hackers_file, "r");
//    FILE* queues = fopen(queues_file, "r");
//    FILE* out = fopen(out_file, "w");


    FILE* students = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\students.txt", "r");
    FILE* courses = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\courses.txt", "r");
    FILE* hackers = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\hackers.txt", "r");
    FILE* queues = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\queues.txt", "r");
    FILE* out = fopen("C:\\Users\\Ruben\\Desktop\\matam23\\ex1\\ExampleTest\\out.txt", "w");

    // Vérifier si les fichiers ont été ouverts avec succès
    if (students == NULL || courses == NULL || hackers == NULL || queues == NULL) {
        printf("Erreur : impossible d'ouvrir un fichier d'entrée\n");
        exit(EXIT_FAILURE);
    }

    // Créer le système d'inscription
    EnrollmentSystem sys = createEnrollment(students, courses, hackers);

    // Lire la file d'attente d'inscription
    sys = readEnrollment(sys, queues);


    // Hacker l'ordre d'inscription
    hackEnrollment(sys, out);

    // Fermer les fichiers d'entrée et de sortie
    fclose(students);
    fclose(courses);
    fclose(hackers);
    fclose(queues);
    fclose(out);
}



int main(int argc, char* argv[]) {
   // bool case_sensitive = true;
    char* students_file;
    char* courses_file;
    char* hackers_file;
    char* queues_file;
    char* out_file;

//    // Vérifier le nombre d'arguments
//    if (argc < 6 || argc > 7) {
//        printf("Erreur : nombre d'arguments invalide\n");
//        exit(EXIT_FAILURE);
//    }

    // Vérifier si le premier argument est présent
    if (argc == 7) {
        // Analyser les arguments
      //  case_sensitive = strcmp(argv[1], "-i") != 0;
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

    // Lancer la fonction HackEnrollment
    WrapperHackEnrollment(/*case_sensitive,*/ students_file, courses_file, hackers_file, queues_file, out_file);

    return 0;
}


