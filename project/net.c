/**
 * This file contains the necessary functions to deal with sending and receiving messages
 * between the server and the client.
 * Here the architecture of communication is exposed, having in consideration
 * the types of messages defined in the "data.h"
 * 
*/


#include "net.h"

/**
 * Function to send data. First a message with the type of data and size is sent
 * then the real load is sent. The buffer shouldn't exceed MAX_BUFFER_SIZE.
 * 
*/
void send_message(int sfd, MsgType type, int msg_size, void* load)
{

    MsgHeader msg;
    msg.type = type;
    msg.size = msg_size;
    if(msg_size > MAX_BUFFER_SIZE)
    {
        printf("WARNING! The buffer (%d) exceeds the MAX_BUFFER_SIZE\n",msg_size);
        printf("Aborting message...\n");
        return;
    }
    if(send(sfd, &msg, sizeof(msg), 0)==-1)
    {printf("Problems in sending MsgHeader \n"); exit(0);}
    if(send(sfd, load, msg_size, 0)==-1)
    {printf("Problems in sending the msg load r\n"); exit(0);}   
}
