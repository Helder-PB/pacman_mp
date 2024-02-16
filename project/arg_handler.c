/**
 * This file includes functions to deal with the terminal input arguments
 * 
*/

#include "arg_handler.h"

int color_checker(int sock_fd,char *argv[], int* r, int* g, int* b)
{
	*r = atoi(argv[3]);
	*g = atoi(argv[4]);
	*b = atoi(argv[5]);
	if((*r < 0) || (*r > 256) || (*g < 0) || (*g > 256) || (*b < 0) || (*b > 256))
	{
        printf("Color code 0 < r,g,b < 256\n");
        return FALSE;
    }
    return TRUE;
}

// int client_arg_net_check(char **argv)
// {
//     // if(sscanf(argv[2], "%d", &port_number)!=1)
//     // {
// 	// 	printf("argv[2] is not a number\n");
// 	// 	exit(-1);
// 	// }
// 	// server_addr.sin_port= htons(port_number);
// 	// if(inet_aton(argv[1], &server_addr.sin_addr) == 0)
// 	// {
// 	// 	printf("argv[1]is not a valid address\n");
// 	// 	exit(-1);
// 	// }
// }