# Variables pour les noms des fichiers sources et objets
SOURCES = tool/HackerEnrollment.c IsraeliQueue.c tool/main.c
HEADERS = tool/HackerEnrollment.h IsraeliQueue.h Node.h
OBJECTS = $(SOURCES:.c=.o)
# Variables pour les options du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
PROGRAM = HackEnrollment

program: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS)-o $@ 

tool/HackerEnrollment.o: tool/HackerEnrollment.c tool/HackerEnrollment.h IsraeliQueue.h
	$(CC) $(CFLAGS) -c tool/HackEnrollment.c

IsraeliQueue.o: IsraeliQueue.c IsraeliQueue.h Node.h
	$(CC) $(CFLAGS) -c IsraeliQueue.c

tool/main.o: tool/main.c tool/HackerEnrollment.h IsraeliQueue.h Node.h
	$(CC) $(CFLAGS) -c tool/main.c

clean:
	rm -f $(OBJECTS) $(PROGRAM)
