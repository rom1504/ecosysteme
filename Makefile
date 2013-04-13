CC=g++
CFLAGS=-Wall
LDFLAGS=-lSDLmain -lSDL
FILES=main construction dessin divers etrevivant font objet trigonometrie unite
OBJECTS=$(FILES:%=bin/%.o)
EXECUTABLE=ecosysteme
vpath %.cpp .

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)

bin/%.o : %.cpp bin/
	$(CC) -c $(CFLAGS) $< -o $@

bin/:
	mkdir bin

clean:
	rm -f bin/*
	rm ecosysteme