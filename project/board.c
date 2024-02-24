#include "board.h"


/**
 * Semaphore to access the board
*/
GSem* board_sem;
/**
 * Read the txt.file board.
 * In an embedded system, txt might not exist if there is no
 * support for a file system. So the board generation must be different, 
 * rendering this function specific to the desktop version
*/
void load_file_board(Map *jogo)
{
    int i,j=0;
    char buf[100];
    //read file
	FILE *fp;
	fp=fopen(BOARD_FILE,"r");

	if(!fp)
	{
		printf("There's no board.txt\n");
		exit(-1);
	}

	fgets(buf,100,fp);
	sscanf(buf,"%d %d\n",&(jogo->size.x), &(jogo->size.y));
	printf("The board has size %dx%d\n",jogo->size.x,jogo->size.y);

    // Alocate n collumn pointers first
	if(!(jogo->board = (Square**)malloc(jogo->size.x*sizeof(Square*))))
        {printf("FAILED MALLOC board*\n");exit(0);}

    // Allocate each collumn composed of size.y positions
	for(i=0;i<jogo->size.x;i++)
		if(!(jogo->board[i] = (Square*)malloc(jogo->size.y*sizeof(Square))))
            {printf("FAILED MALLOC board\n");exit(0);}
    jogo->nbricks = 0;
    // Populate the map with the occupied positions
	while(fgets(buf,100,fp))
	{
		for(i=0;i<jogo->size.x;i++)
		{
			if(buf[i]==' ')
			{
				jogo->board[i][j].type = Empty;
			}
			else if(buf[i]=='B')
			{
				jogo->board[i][j].type = Brick;
				jogo->nbricks++;
			}		
		}
		j++;
	}

	fclose(fp);

	
	// Map's integrity check
	jogo->max_players = (int)((jogo->size.x*jogo->size.y + 2 - jogo->nbricks)/4);
	printf("maxp = %d\n",jogo->max_players);


	if (jogo->max_players<2)
	{
		printf("Bad board: not enough space to play properly\n");
		exit(-1);
	}

	if(jogo->max_players > MAX_PLAYERS)
		jogo->max_players = MAX_PLAYERS;
}

/**
 * This function initiates all the mutexes to access the board
*/
GSem* board_semaphores()
{
	board_sem = (GSem* )malloc(sizeof(GSem));
	if (sem_init(board_sem, 0, 1) == -1)
	{
		printf("Couldn't init semaphore. Exiting\n");
		exit(-1);
	}
	return board_sem;
}


/**
 * This function is responsible to send the board to the 
 * client described in the sockfd.
 * The function used to send it descripted in the *send_func
*/
int send_full_state_game(int soctFd, Map *jogo, Player* players)
{
	for(int i = 0; i < jogo->size.x; i++)
	{
		for(int j = 0; j < jogo->size.y; j++)
		{
			Entity ent;
			ent.type = jogo->board[i][j].type;
			ent.location = (Dim){.x = i, .y = j};
			if(jogo->board[i][j].type != Brick || jogo->board[i][j].type != Empty)
			{
				ent.color = players[jogo->board[i][j].id].color;
			}
			if(FALSE == send_message(soctFd, *(MsgType[]){Draw} , sizeof(ent), &ent))
				return FALSE;
		}
	}
	// Now warn the the client may play because the full board was sent
	if(FALSE == send_message(soctFd, *(MsgType[]){Play} , sizeof(char), (char[]){'a'}))
		return FALSE;
	return TRUE;
}



/**
 * Register entity
 * uses 4 bytes of information
 * the 2 most important bytes save the owner of the entity, who
 * should be the ushort id of a player
 * the 2 least significant store the id of the entity (fruit, brick, ...)
 * 
*/

// void register_entity()
// {
	
// }
