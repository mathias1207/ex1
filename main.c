#include 
#include 
#include 





void HackEnrollment(bool case_sensitive, char* students_file, char* courses_file, char* hackers_file, char* queues_file, char* out_file) {
    // Ouvrir les fichiers d'entrée
    FILE* students = fopen(students_file, "r");
    FILE* courses = fopen(courses_file, "r");
    FILE* hackers = fopen(hackers_file, "r");
    FILE* queues = fopen(queues_file, "r");

    // Vérifier si les fichiers ont été ouverts avec succès
    if (students == NULL || courses == NULL || hackers == NULL || queues == NULL) {
        printf("Erreur : impossible d'ouvrir un fichier d'entrée\n");
        exit(EXIT_FAILURE);
    }

    // Créer le système d'inscription
    EnrollmentSystem sys = createEnrollment(students, courses, hackers);

    // Lire la file d'attente d'inscription
    sys = readEnrollment(sys, queues);

    // Fermer le fichier de file d'attente
    fclose(queues);

    // Hacker l'ordre d'inscription
    hackEnrollment(sys, out_file);

    // Fermer les fichiers d'entrée et de sortie
    fclose(students);
    fclose(courses);
    fclose(hackers);
    fclose(out_file);
}



int main(int argc, char* argv[]) {
    bool case_sensitive = true;
    char* students_file;
    char* courses_file;
    char* hackers_file;
    char* queues_file;
    char* out_file;

    // Vérifier le nombre d'arguments
    if (argc < 6 || argc > 7) {
        printf("Erreur : nombre d'arguments invalide\n");
        exit(EXIT_FAILURE);
    }

    // Vérifier si le premier argument est présent
    if (argc == 7) {
        // Analyser les arguments
        case_sensitive = strcmp(argv[1], "i") != 0;
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
    HackEnrollment(case_sensitive, students_file, courses_file, hackers_file, queues_file, out_file);

    return 0;
}
Dans cette implémentation, le main vérifie si le nombre d'arguments est valide (soit 6 ou 7), puis vérifie si le premier argument est présent en vérifiant le nombre d'arguments. Si le premier argument est présent, les arguments sont analysés à partir de l'indice 1. Sinon, les arguments sont analysés à partir de l'indice 0.

La variable case_sensitive est initialisée à true par défaut, et est mise à false si le premier argument est égal à "i". Les noms de fichiers sont ensuite analysés à partir des indices appropriés, puis la fonction HackEnrollment est appelée avec les paramètres correspondants.






