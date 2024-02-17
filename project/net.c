/**
 * This file contains the necessary functions to deal with sending and receiving messages
 * between the server and the client.
 * Here the architecture of communication is exposed, having in consideration
 * the types of messages defined in the "data.h"
 * 
 * TODO: also include the bind and listen steps in this file
 * 
*/


#include "net.h"

/**
 * Function to send data. First a message with the type of data and size is sent
 * then the real load is sent. The buffer shouldn't exceed MAX_BUFFER_SIZE.
 * 
*/
int send_message(int sfd, MsgType type, int load_size, void* load)
{

    MsgHeader msg;
    msg.type = type;
    msg.size = load_size;
    if(load_size > MAX_BUFFER_SIZE)
    {
        printf("WARNING! The buffer (%d) exceeds the MAX_BUFFER_SIZE\n",load_size);
        printf("Aborting message...\n");
        return FALSE;
    }
    if(send(sfd, &msg, sizeof(msg), 0)==-1)
    {printf("Problems in sending MsgHeader \n"); return FALSE;}
    if(send(sfd, load, load_size, 0)==-1)
    {printf("Problems in sending the msg load r\n"); return FALSE;}   
    return TRUE;
}

/**
 * Function to receive data. First a message with the type of data and 
 * size is received. Then the real load is received.
 * The buffer shouldn't exceed MAX_BUFFER_SIZE and must be allocated 
 * by the caller of this function in load.
 * 
*/
int receive_message(int sfd, MsgHeader* msg, void* load)
{
    
    if(recv(sfd, msg, sizeof(MsgHeader), 0) != sizeof(MsgHeader))
    {
        printf("Problems in receiving MsgHeader \n");
        return FALSE;
    }

    if(msg->size > MAX_BUFFER_SIZE)
    {
        printf("WARNING! The buffer (%d) exceeds the MAX_BUFFER_SIZE\n",msg->size);
        printf("Aborting message...\n");
        return FALSE;
    }
    
    if(recv(sfd, load, msg->size, 0) != msg->size)
    {
        printf("Problems in receiving the msg load r\n"); 
        return FALSE;
    }
    return TRUE;   
}



