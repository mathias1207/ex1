# Variables pour les noms des fichiers sources et objets
SOURCES = HackEnrollment.c IsraeliQueue.c main.c
HEADERS = HackEnrollment.h IsraeliQueue.h
OBJECTS = $(SOURCES:.c=.o)
# Variables pour les options du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
# Nom du programme généré
PROGRAM = HackEnrollment

# Règle pour construire le programme
program: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS)
  
  # Règles pour les fichiers objets
HackEnrollment.o: HackEnrollment.c HackEnrollment.h IsraeliQueue.h
	$(CC) $(CFLAGS) -c HackEnrollment.c

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h
	$(CC) $(CFLAGS) -c IsraeliQueue.c

main.o: main.c HackEnrollment.h IsraeliQueue.h
	$(CC) $(CFLAGS) -c main.c

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJECTS) $(PROGRAM)

