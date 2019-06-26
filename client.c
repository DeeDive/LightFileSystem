#include "comm.h"

int main()
{
    int msgid = getMsgQueue();

    char buf[MAX_TEXT] = {0};
    while(1)
    {
        printf("Please Enter# ");
        fflush(stdout);
        ssize_t s = read(0, buf, sizeof(buf));
        if(s > 0)
        {
            buf[s-1]=0;
            sendMsgQueue(msgid, CLIENT_TYPE, buf);
            if(strcasecmp("quit", buf) == 0)
                break;
            printf("send done, wait recv...\n");
        }

        recvMsgQueue(msgid, SERVER_TYPE, buf);
        printf("server# %s\n", buf);
    }
    return 0;
}