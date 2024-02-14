/**
 * functions related to board reading
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

#include "configs.h"
#include "data.h"
/**
 * Read board file.
 * writes the read map into @param jogo and checks it's integrity for playing
*/
void load_file_board(map *jogo);


#endif