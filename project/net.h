/**
 * This file contains the necessary functions to deal with sending and receiving messages
 * between the server and the client.
 * Here the architecture of communication is exposed, having in consideration
 * the types of messages defined in the "data.h"
 * 
*/

#ifndef _NET_H_
#define _NET_H_

#include "data.h"


void send_message(int sfd, MsgType type, int msg_size, void* load);


#endif