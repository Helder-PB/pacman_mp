/**
 * functions related to board management
*/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <SDL2/SDL.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>

#include "data.h"
#include "net.h"



/**
 * Read board file.
 * writes the read map into @param jogo and checks it's integrity for playing
*/
void load_file_board(Map *jogo);
int send_full_state_game(int soctFd, Map *jogo, Player* players);


#endif