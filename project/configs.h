/**
 * file with configs to activate or deactivate functionalities
*/
#ifndef _CONFIGS_H_
#define _CONFIGS_H_

#define TRUE 1
#define FALSE 0

#define SERVER_GRAPHICS 1
#define CLIENT_GRAPHICS 1

#define IMAGES_PATH "./images/"
#define IMG(MY_IMAGE) IMAGES_PATH MY_IMAGE

#define BOARD_FILE "board.txt"
#define PORT 3000

// this value also depends on the board of the games
// The board should be big enough
#define MAX_PLAYERS 4
// There can't be more players than colors
#define MAX_N_COLORS 8 

// Client messages can't exceed this value
#define MAX_BUFFER_SIZE 50

#endif