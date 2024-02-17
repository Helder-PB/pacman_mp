/**
 * This file header contains the defeniutions necessary for 
 * house keeping of the players
 * 
*/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "data.h"
#include "net.h"
#include "board.h"



void reset_player(Player* client);
Player* allocate_MAX_PLAYERS();
int available_player_position(Player* list_of_clients, int *position);
void *player_thread(void *arg);
void copy_game(Map* _game);


#endif