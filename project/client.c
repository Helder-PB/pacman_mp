/**
 * This file has the main function of a client to connect to the server and play
*/

#include "data.h"
#include "arg_handler.h"
#include "UI_library/UI_library.h"
#include "net.h"


//Esta função envia as cores do cliente ao servidor
void color_sender(int sock_fd, int r,int g,int b)
{
	if(send(sock_fd, &r, sizeof(int), 0)==-1)
    {printf("Problems in sending r\n"); exit(0);}
	if(send(sock_fd, &g, sizeof(int), 0)==-1)
    {printf("Problems in sending g\n"); exit(0);}
	if(send(sock_fd, &b, sizeof(int), 0)==-1)
    {printf("Problems in sending b\n"); exit(0);}
}

// Stablish connection from the client to the server
int stablish_connection(char** argv,struct sockaddr_in *server_addr,int *port_number, int* sock_fd)
{
    *sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (*sock_fd == -1)
	{
        perror("socket: ");
        exit(-1);
  	}

    server_addr->sin_family = AF_INET;
    if(sscanf(argv[2], "%d", port_number)!=1){
		printf("argv[2] is not a number\n");
		exit(-1);
	}
	server_addr->sin_port= htons(*port_number);
	if(inet_aton(argv[1], &(server_addr->sin_addr)) == 0)
	{
		printf("argv[1]is not a valid address\n");
		exit(-1);
	}

  	printf("connecting to %s %d\n", argv[1], server_addr->sin_port );

	if( connect(*sock_fd,(const struct sockaddr *) server_addr,	sizeof(*server_addr)) == -1)
	{
		printf("Error connecting\n");
		exit(-1);
  	}
    return TRUE;
}


/**
 * This function executes the data gathering to start the game properly
 * This function exits only if the dada was weel received and registred
 * or if there was an error
*/
void start_game(int sock_fd)
{
    int may_play = FALSE;
    MsgHeader msg;
    char buffer[MAX_BUFFER_SIZE];// = calloc(50,1);


    while(may_play == FALSE)
    {

        if(receive_message(sock_fd, &msg, (void*)buffer) == FALSE)
        {
            may_play == FALSE;
            continue;
        }    

        // if(recv(sock_fd, &msg, sizeof(msg), 0) != sizeof(msg))
        // {printf("Problems in receiving MsgHeader \n"); exit(0);}
        // if(recv(sock_fd, &buffer, msg.size, 0) != msg.size)
        // {printf("Problems in receiving the msg load r\n"); exit(0);}

        switch (msg.type)
        {
        case Map_dim:
            create_board_window(((Dim*)buffer)->x,((Dim*)buffer)->y);
            may_play = TRUE; // Just to test
            break;

        case Draw:
            // TODO
            break;


        
        default:
            break;
        }
    }


    
}

int main(int argc, char** argv)
{
    SDL_Event event;
    Uint32 REFRESH =  SDL_RegisterEvents(1);
    int playing = FALSE;

    // Stablish connection to the server
    int port_number, sock_fd;
    struct sockaddr_in server_addr;

    if(stablish_connection(argv,&server_addr,&port_number,&sock_fd) == FALSE)
    {
        printf("Couldn't connect. Verify network of arguments of the client\n");
        exit(EXIT_FAILURE);
    }
    
    start_game(sock_fd);

    // connection was stablished with the server. The client is now a player
    playing = TRUE;
    while(playing)
    {

        SDL_WaitEvent(&event);
        if(event.type == SDL_QUIT) 
		{
			playing = FALSE;
		}
		if(event.type == SDL_MOUSEMOTION) 
		{

		}
		if ( event.type == SDL_KEYDOWN ) 
        {
            Movement pac_mov;
            switch ( event.key.keysym.sym )
            {
                case SDLK_UP:	
                    pac_mov = Up;
                    send_message(sock_fd, Mov_msg, sizeof(Mov_msg), &pac_mov);
					break;

				case SDLK_DOWN:
                    pac_mov = Down;
                    send_message(sock_fd, Mov_msg, sizeof(Mov_msg), &pac_mov);
					break;	

				case SDLK_RIGHT:
                    pac_mov = Right;
                    send_message(sock_fd, Mov_msg, sizeof(Mov_msg), &pac_mov);
					break; 	

				case SDLK_LEFT:
                    pac_mov = Left;
                    send_message(sock_fd, Mov_msg, sizeof(Mov_msg), &pac_mov);
					break;

				default:
                    break;	 
            }   
            
		}


        // char text[10] = "Bom dia \n\0";
        // MsgHeader msg;
        // msg.size = sizeof(text);
        // msg.type = Text_msg;
        // if(send(sock_fd, &msg, sizeof(msg), 0)==-1)
        // {printf("Problems in sending MsgHeader \n"); exit(0);}
        // if(send(sock_fd, &text, sizeof(text), 0)==-1)
        // {printf("Problems in sending the msg load r\n"); exit(0);}
        // sleep(1);
    }
    printf("CLOSING\n");
	close(sock_fd);
	close_board_windows();



    return EXIT_SUCCESS;
}