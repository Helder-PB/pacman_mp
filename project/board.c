#include "board.h"




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
	if(!(jogo->board = (int**)malloc(jogo->size.x*sizeof(int*))))
        {printf("FAILED MALLOC board*\n");exit(0);}

    // Allocate each collumn composed of size.y positions
	for(i=0;i<jogo->size.x;i++)
		if(!(jogo->board[i] = (int*)malloc(jogo->size.y*sizeof(int))))
            {printf("FAILED MALLOC board\n");exit(0);}
    jogo->nbricks = 0;
    // Populate the map with the occupied positions
	while(fgets(buf,100,fp))
	{
		for(i=0;i<jogo->size.x;i++)
		{
			if(buf[i]==' ')
			{
				jogo->board[i][j]=0;
			}
			else if(buf[i]=='B')
			{
				jogo->board[i][j]=-1;
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

//Esta função envia as cores do cliente ao servidor
void color_sender(int sock_fd, int r,int g,int b)
{
	if(send(sock_fd, &r, sizeof(int), 0)==-1){printf("Problems in sending r\n"); exit(0);}
	if(send(sock_fd, &g, sizeof(int), 0)==-1){printf("Problems in sending g\n"); exit(0);}
	if(send(sock_fd, &b, sizeof(int), 0)==-1){printf("Problems in sending b\n"); exit(0);}
}