/**
 * This file includes information about data structures used
 * 
*/

#ifndef _DATA_H_
#define _DATA_H_

/**
 * Structure to store 2D dimentions
 * 
*/
typedef struct dim{
    int x;
    int y;
}dim;

/**
 * How the map is stored in the server
 * @param size: dimentions of the board, cols and rows
 * @param board: grid with the content of the board
 * @param max_players: number of maximum players in the board
*/
typedef struct map{
    dim size;
    int **board;
    int nbricks;
    int max_players;
}map;



/**
 * Information that characterizes a client
 * TODO: all
*/
typedef struct client{


}client;


#endif