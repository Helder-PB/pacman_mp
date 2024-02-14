#make para dar make do servidor e do cliente
#make s para dar o make do servidor
#make c para dar make do cliente
#make clean para limpar os .o da pasta

all: s c
CC = gcc -g -O0 -Wall #com debug
COMP_FLAGS = -lpthread -lSDL2 -lSDL2_image
UI_PATH = UI_library

c: client.o UI_library.o regras.o timer.o refresh.o general.o
	$(CC) -o client client.o timer.o UI_library.o regras.o refresh.o general.o $(COMP_FLAGS)

s: server.o UI_library.o board.o
	$(CC) -o server server.o UI_library.o board.o $(COMP_FLAGS)

client: client.c general.h timer.h refresh.h
	$(CC) -c client.c $(COMP_FLAGS)

server.o: server.c configs.h board.h data.h
	$(CC) -c server.c $(COMP_FLAGS)

board: board.c board.h configs.h data.h
	$(CC) -c board.c $(COMP_FLAGS)

data: data.c data.h
	$(CC) -c data.c $(COMP_FLAGS)

UI_library.o: $(UI_PATH)/UI_library.c $(UI_PATH)/UI_library.h configs.h
	$(CC) -c $(UI_PATH)/UI_library.c $(COMP_FLAGS)

clean::
	rm -f *.o && rm -f *.h.gch
