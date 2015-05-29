CC=gcc
CFLAGS=-std=c99 -pedantic -Wall
SOURCES=find_in_file.c  finderBM.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=find_in_file
HEADERS=finderBM.h

all: $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

.c:$(OBJECTS)
	$(CC) $(CFLAGS) -c
	
$(OBJECTS):$(HEADERS)

clear:
	rm -rf  $(EXECUTABLE) $(OBJECTS) 
distclear:
	rm -rf $(OBJECTS) 
