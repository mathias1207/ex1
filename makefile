# Variables pour les noms des fichiers sources et objets
SOURCES = tool/HackEnrollment.c IsraeliQueue.c tool/main.c
HEADERS = tool/HackEnrollment.h IsraeliQueue.h Node.h
OBJECTS = HackEnrollment.o IsraeliQueue.o main.o
# Variables pour les options du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
PROGRAM = HackEnrollment

program: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

HackEnrollment.o: tool/HackEnrollment.c tool/HackEnrollment.h IsraeliQueue.h
	$(CC) $(CFLAGS) -c tool/HackEnrollment.c

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h Node.h
	$(CC) $(CFLAGS) -c IsraeliQueue.c

main.o: tool/main.c tool/HackEnrollment.h IsraeliQueue.h Node.h
	$(CC) $(CFLAGS) -c tool/main.c

clean:
	rm -f $(OBJECTS) $(PROGRAM)
