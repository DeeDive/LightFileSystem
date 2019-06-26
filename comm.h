#ifndef _COMM_H_
#define _COMM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

#define MAX_TEXT 8192
//greater than this(10240) get error: invalid argument
struct msgbuff
{
    long mtype;
    char mtext[MAX_TEXT];
};

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

int createMsgQueue();
int getMsgQueue();
int destoryMsgQueue(int msg_id);
int sendMsgQueue(int msg_id, int who, char* msg);
int recvMsgQueue(int msg_id, int recvType, char out[]);

#endif