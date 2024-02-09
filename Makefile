#make para dar make do servidor e do cliente
#make s para dar o make do servidor
#make c para dar make do cliente
#make clean para limpar os .o da pasta

all: s c
CC = gcc -g -O0 -Wall #com debug
COMP_FLAGS = -lpthread -lSDL2 -lSDL2_image

c: client.o UI_library.o regras.o timer.o refresh.o general.o
	$(CC) -o client client.o timer.o UI_library.o regras.o refresh.o general.o $(COMP_FLAGS)

s: server.o UI_library.o regras.o timer.o general.o refresh.o
	$(CC) -o server server.o UI_library.o regras.o timer.o general.o refresh.o $(COMP_FLAGS)

client: client.c general.h timer.h refresh.h
	$(CC) -c client.c $(COMP_FLAGS)

server_i: server.c regras.h general.h
	$(CC) -c server.c $(COMP_FLAGS)

refresh.o: refresh.c refresh.h data.h UI_library.h
	$(CC) -c refresh.c $(COMP_FLAGS)

regras.o: regras.c regras.h refresh.h
	$(CC) -c regras.c $(COMP_FLAGS)

timer.o:timer.c timer.h data.h
	$(CC) -c timer.c $(COMP_FLAGS)

general.o:general.c general.h data.h
	$(CC) -c general.c $(COMP_FLAGS)

UI_library.o:  UI_library.c UI_library.h
	$(CC) -c UI_library.c $(COMP_FLAGS)

clean::
	rm -f *.o && rm -f *.h.gch
