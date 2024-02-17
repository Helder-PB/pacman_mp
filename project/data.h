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
 * shouldn't exceed 2 bytes to be enumerated.
*/
typedef enum {
    Empty = 0,
    Pacman = 21,
    SuperPacman = 22,
    Monster = 23,
    Cherry = 24,
    Lemon = 25,
    Brick = 26
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
    Erase = 37,
    Play = 38
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
 * If an entity is a fruit, then the color field is irrelevant.
*/
typedef struct Entity{
    Entity_type type; 
    Dim location;
    Color color;
}Entity;

/**
 * Struct that defines what is saved in a square in the board
 * id represents the id of the owner of the entity in the square
 * type representes the type of entity in the square
*/
typedef struct Square{
    short id;
    Entity_type type;
}Square;


/**
 * How the map is stored in the server
 * @param size: dimentions of the board, cols and rows
 * @param board: grid with the content of the board
 * @param max_players: number of maximum players in the board
*/
typedef struct Map{
    Dim size;
    Square **board;
    int nbricks;
    int max_players;
}Map;


typedef struct MsgHeader{
    MsgType type;
    int size;
}MsgHeader;

/**
 * Information that characterizes a player, not a client
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






#endif