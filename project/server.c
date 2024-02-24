#include "board.h"
#include "player.h"
#include "UI_library/UI_library.h"

/**
 * query if a new player can be accepted based in the current @param game
 * return 1 if TRUE and 0 if FALSE
*/
int new_player_request(Map game)
{
    if(TRUE/** TODO: accepting condition*/)
        return TRUE;
    else 
        return FALSE;
}

int main(int argc, char **argv)
{
    int n_players = 0;                          //Current number of players in the game
    int i,j,n;                                  //house keeping
    int is_server_on = 0;                       //is the server on or not?
    struct sockaddr_in client_add;              //socketaddr for the incoming client
    struct sockaddr_in server_add;              //socketadrr for the server
	socklen_t size_add = sizeof(client_add);
	int sock_server, sock_fd;                   
    SDL_Event event;
    Player* players = allocate_MAX_PLAYERS();
    GSem* board_sem = player_board_acess();


    Map game;                                   // The board
    load_file_board(&game);                     // read board
    copy_game(&game);                           // allow game to be viewed by the players
    srand(time(NULL));                          // Initiallize the random feature

    	
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

    //server is on
    is_server_on = TRUE;


	
	printf("CAN CONNECT\n");

	while(is_server_on == TRUE)
	{
        printf("Waiting for a connection...\n");
	    sock_fd = accept(sock_server,(struct sockaddr *) &client_add, &size_add);
	    printf("Received a new request for connection...\n");
	    if(sock_fd == -1){
	      	perror("accept");
	      	exit(-1);
	    }
	    
        int new_pos;
        if(TRUE == available_player_position(players,&new_pos))
        {
            printf("accepted connection \n");
            
            if(!(players[new_pos].client_t=(pthread_t*)malloc(sizeof(pthread_t))))
                {printf("FAILED MALLOC pthread_t\n");exit(0);}
            
            players[new_pos].on = TRUE;
            players[new_pos].sockID = sock_fd;
            
            pthread_create((players[new_pos].client_t), 
                            NULL, 
                            player_thread, 
                            (void*)&players[new_pos].id);

        }
        else // == FALSE
        {
            close(sock_fd);
        }
    }

	// Closing server
	close(sock_server);
	close_board_windows();

	
	for(i=0;i<game.size.x;i++)
		free(game.board[i]);
  	free(game.board);

	printf("SERVER SHUTDOWN\n"); 	

	exit(0);

}