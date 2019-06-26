//
// Created by Yongqiang Dou on 6/6/2019.
//

#include "LightFileSystem.h"

#include "comm.h"
int main()
{
    LightFileSystem fs;

    fs.run();
}
//int main()
//{
//    int msgid = createMsgQueue();
//
//    char buf[MAX_TEXT] = {0};
//    while(1)
//    {
//        recvMsgQueue(msgid, CLIENT_TYPE, buf);
//        if(strcasecmp("quit", buf) == 0)
//            break;
//        printf("client# %s\n", buf);
//
//        printf("Please enter# ");
//        fflush(stdout);
//        fgets(buf,MAX_TEXT,stdin);
//        sendMsgQueue(msgid, SERVER_TYPE, buf);
//        printf("send done, wait recv...\n");
//
//    }
//
//    destoryMsgQueue(msgid);
//    return 0;
//}
