#make para dar make do servidor e do cliente
#make s para dar o make do servidor
#make c para dar make do cliente
#make clean para limpar os .o da pasta

all: s c
CC = gcc -g -O0 -Wall #com debug
COMP_FLAGS = -lpthread -lSDL2 -lSDL2_image
UI_PATH = UI_library


c: client.o UI_library.o arg_handler.o net.o
	@echo "running the c stage"
	$(CC) -o client client.o UI_library.o arg_handler.o net.o $(COMP_FLAGS)

s: server.o UI_library.o board.o player.o net.o
	@echo "running the s stage"
	$(CC) -o server server.o UI_library.o board.o player.o net.o $(COMP_FLAGS)

client: client.c arg_handler.c arg_handler.h net.h
	@echo "running the argument handler stage"
	$(CC) -c client.c $(COMP_FLAGS)

arghandler: arg_handler.c arg_handler.h data.h
	$(CC) -c arg_handler.c $(COMP_FLAGS)

server: server.c board.c player.c board.h player.h
	@echo "running the server stage"
	$(CC) -c server.c $(COMP_FLAGS)

player: player.c player.h data.h net.h
	@echo "running the player stage"
	$(CC) -c player.c $(COMP_FLAGS)

net: net.c net.h data.h
	@echo "running the net stage"
	$(CC) -c net.c $(COMP_FLAGS)

board: board.c board.h data.h
	@echo "running the board stage"
	$(CC) -c board.c $(COMP_FLAGS)

data: data.c data.h
	@echo "running the data stage"
	$(CC) -c data.c $(COMP_FLAGS)

UI_library.o: $(UI_PATH)/UI_library.c $(UI_PATH)/UI_library.h configs.h
	@echo "running the UI_library SDL2s stage"
	$(CC) -c $(UI_PATH)/UI_library.c $(COMP_FLAGS)

clean::
	rm -f *.o && rm -f *.h.gch
