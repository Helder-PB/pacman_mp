/**
 * This file includes functions of the server to deal with clients
 * 
*/
#include "player.h"

/**
 * Local Global variables
*/
Color list_colors[MAX_N_COLORS]=
{
    {0,0,0},        //Black
    {255,0,0},      //Red
    {0,255,0},      //Lime
    {0,0,255},      //Blue
    {0,255,255},    //Cyan
    {255,0,255},    //Magenta
    {0,100,0},      //Dark Green
    {139,69,19}     //Sadle brown
};

Player* list_players;
Map* game;

/**
 * Allocate memory for all possible new players
 * If this function fails, it means that the hardware can't 
 * work with the defined MAX_PLAYERS in the config.h
*/
Player* allocate_MAX_PLAYERS()
{
    Player* all_possible_clients;
    all_possible_clients = (Player*)malloc(MAX_PLAYERS*sizeof(Player));
    if(all_possible_clients == NULL)
    {
        printf("ERROR. Can't allocate MAX_PLAYERS\n");
        exit(-1);
    }
    for(int i=0;i < MAX_PLAYERS; i++)
    {
        all_possible_clients[i].color = list_colors[i];
        all_possible_clients[i].id = i; 
        reset_player(&all_possible_clients[i]);
        
    }
	list_players = all_possible_clients;
    return all_possible_clients;
}

// Weird chenanigans to get the board here
// TODO: this is a temporary fix
void copy_game(Map* _game)
{
	game = _game;
}


//Função que retira as cores dos argumentos do cliente e vê se estão
//dentro de valores admissíveis (0<r,g ou b<256)
void color_checker(int sock_fd,char *argv[], int* r, int* g, int* b)
{
	*r = atoi(argv[3]);
	*g = atoi(argv[4]);
	*b = atoi(argv[5]);
	if((*r < 0) || (*r > 256) || (*g < 0) || (*g > 256) || (*b < 0) || (*b > 256))
		{printf("Color code 0 < r,g,b < 256\n");exit(0);}
	
}


void reset_player(Player* client)
{
    client->client_t = NULL;
    client->score = 0;
    client->on = FALSE;
}

/**
 * find an available position for receiving a new client to be a player
 * returns True and the position if there is an available slot
 * returns False and position = -1 if no slot available
 * ! This function must be called after the slots where alocated
*/
int available_player_position(Player* list_of_clients, int *position)
{
    for(int i = 0; i < MAX_PLAYERS; i++)
        if(list_of_clients[i].on == FALSE)
        {
            *position = i;
            return TRUE;
        }
    *position = -1;
    return FALSE;
}

/**
 * This function allocates the necessary buffer to receive information
 * with variable size from a client
 * It has hardcoded limits defined in the config
*/
void* new_buffer(int size)
{
	if(size > MAX_BUFFER_SIZE)
	{
		printf("The message to be received exceeds MAX_BUFFER_SIZE!");
		return NULL;
	}
	void* buffer = malloc(size);
	if(buffer == NULL)
	{
		printf("Could malloc the buffer!");
		return NULL;
	}
	return buffer;
}


/**
 * Stablishing connection with the client, informing it's given information
 * and give the state of the game
*/
int inform_client_game_state(int id, Player* players)
{
	// Inform board size
	if((send_message(players[id].sockID, Map_dim, sizeof(Dim), &(game->size)) == FALSE) |
		(send_full_state_game(players[id].sockID, game ,players) == FALSE))
	{
		printf("Couldn't inform player.sockID=%d and id=%d the game state. excluding it...\n",
					players[id].sockID,players[id].id);
		return FALSE;
	}
	printf("Successfuly informed player %d of the game state\n",id);
	return TRUE;
}


/**
 * Thread of the player
*/

void *player_thread(void * arg)
{
    //
    MsgHeader header;
    

	pthread_t pacman_timer,monster_timer;
	int client_playing = FALSE;				// The client is not playing YET
	int id  = *((int*)arg);
	int i;

	pthread_detach(pthread_self());
	// If we can inform the client then he's going to play
	client_playing = inform_client_game_state(id,list_players);

	sleep(10);
	MsgHeader msg_h;
	char buffer[MAX_BUFFER_SIZE];


	while(client_playing == TRUE)
	{	
		int rec_s = recv(list_players[id].sockID, &msg_h , sizeof(msg_h), 0);
		// Receive the size of the header of the message
		// void* buffer = new_buffer(msg_h.size);
		// if(buffer == NULL)
		// {
		// 	printf("Couldn't allocate buffer to receive ");
		// }
		
		// Verify the type of message
		int type = msg_h.type;
		if(recv(list_players[id].sockID, &buffer , msg_h.size, 0) <= 0)
		{
			printf("didn't receive the message corpus. Deleting player\n");
			client_playing = FALSE;
			
			// TODO delete player here in case of error
		}
		else
		{
			switch (msg_h.type)
			{
			case Text_msg: // Just to test
				printf("The client %d sent \n	-- %s --\n",id,(char*)buffer);
				break;
			case Mov_msg:
				printf("Movement of type %d\n",*(Movement*)buffer);
				break;
			default:
				break;
			}
		}
		// Apply the game rules

		// 

	}
	// The player asked to exit
	close(list_players[id].sockID);
	

	list_players[id].score=0;
	list_players[id].on = FALSE;

	return (NULL);
}


