/**
 * This file includes information about data structures used
 * 
*/

#ifndef _DATA_H_
#define _DATA_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "configs.h"


/**
 * Enum to store commands into a more readable manner
 * TODO
*/
typedef enum {
    Left = 11,
    Up = 12,
    Right = 13,
    Down = 14
}Movement;

/**
 * enum to store the entities in a more readable manner
*/
typedef enum {
    Pacman = 21,
    SuperPacman = 22,
    Monster = 23,
    Berry = 24,
    Lemon = 25
}Entity_type;

/**
 * enum to store the types of messages in a more readable manner
*/
typedef enum {
    Color_msg = 31,
    Mov_msg = 32,
    Ent_msg = 33,
    Map_dim = 34,
    Text_msg = 35,
    Draw = 36,
    Erase = 37
}MsgType;

/**
 * color
*/
typedef struct Color{
    int r;
    int g;
    int b;
}Color;


/**
 * Structure to store 2D dimentions
 * 
*/
typedef struct Dim{
    int x;
    int y;
}Dim;

/**
 * Structure that saves the information of an entity
*/
typedef struct Entity{
    Entity_type type; 
    Dim location;
}Entity;



/**
 * How the map is stored in the server
 * @param size: dimentions of the board, cols and rows
 * @param board: grid with the content of the board
 * @param max_players: number of maximum players in the board
*/
typedef struct Map{
    Dim size;
    int **board;
    int nbricks;
    int max_players;
}Map;


typedef struct MsgHeader{
    MsgType type;
    int size;
}MsgHeader;




#endif