#include "board.h"
#include "data.h"
#include "UI_library/UI_library.h"

/**
 * query if a new player can be accepted based in the current @param game
 * return 1 if TRUE and 0 if FALSE
*/
int new_player_request(map game)
{
    if(/*accepting condition*/)
        return TRUE;
    else 
        return FALSE;
}

int main(int argc, char **argv)
{
    int n_players = 0;              //Current number of players in the game
    int i,n;
    SDL_Event event;

    map game;                       //The board
    load_file_board(&game);         // read board

    srand(time(NULL));              //Initiallize the random feature

    

	struct sockaddr_in server_add;
	int sock_server;
	if ( (sock_server = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
        perror("socket: ");
        exit(-1);
	}

	server_add.sin_family = AF_INET;
    server_add.sin_addr.s_addr = INADDR_ANY;
    server_add.sin_port = htons(PORT);

    if( bind(sock_server, (struct sockaddr *)&server_add,sizeof(server_add)) == -1) 
        {perror("bind");exit(-1);}

	if(listen(sock_server, game.max_players) == -1) 
	    {perror("listen");exit(-1);}



    #if SERVER_GRAPHICS
	create_board_window(game.size.x,game.size.y);
    #endif

    //server is on baby

	




	// Closing server
	close(sock_server);
	close_board_windows();

	
	for(i=0;i<game.size.x;i++)
		free(game.board[i]);
  	free(game.board);

	printf("SERVER SHUTDOWN\n"); 	

	exit(0);

}