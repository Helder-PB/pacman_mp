/**
 * This file header contains the defeniutions necessary for 
 * house keeping of the players
 * 
*/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "data.h"
#include "net.h"

/**
 * Information that characterizes a client
 * TODO: all
*/
typedef struct Player{
    Entity character[2]; //A mosnter and a pacmans
    int score;
    int on;
    int sockID;
    Color color;
    pthread_t* client_t;
    int id;
    int fruit;
    int eat;
} Player;



void reset_player(Player* client);
Player* allocate_MAX_PLAYERS();
int available_player_position(Player* list_of_clients, int *position);
void *player_thread(void *arg);
void copy_game(Map* _game);


#endif