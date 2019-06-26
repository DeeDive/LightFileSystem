//
// Created by Yongqiang Dou on 6/6/2019.
//
#define green cout<<"\33[32m"
#define RESET cout<<"\033[0m"
#define BOLDGREEN cout<<"\033[1m\033[32m"
#include "comm.h"
#include "comm.c"
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;
int main()
{
    system("clear");
    fstream f_lock("server_running.lock",ios::in|ios::out|ios::binary);
    if(!f_lock)//server is not running
    {
       // int cnt =1; //the number of client
        ofstream out("server_running.lock",ios::binary);
        out.close();

        //start the server
        if(fork()==0)
        {
            system("gnome-terminal --working-directory=\"$(pwd)\" -t LightFileSystem--Server -- ./server");
        } else
        {
            int msgid = getMsgQueue();

            char buf[MAX_TEXT] = {0};
            while(1)
            {
                BOLDGREEN<<"Yongqiang@HPC:# ";
                RESET;
                cout.flush();
                //fgets(buf,MAX_TEXT,stdin);

                //  scanf("%[^\n]" , buf);
                string tmp;
                while(1)
                {
                    std::getline(cin,tmp);
                    if(tmp!="")
                        break;
                }
                strcpy(buf,tmp.c_str());
                if(strcasecmp("exit", buf) == 0)
                {
                    stpcpy(buf,"client exit");
                    sendMsgQueue(msgid, CLIENT_TYPE, buf);
                    printf("Bye! \n");
                    break;
                }
                sendMsgQueue(msgid, CLIENT_TYPE, buf);

                //printf("send done, wait recv...\n");

                recvMsgQueue(msgid, SERVER_TYPE, buf);
                //printf("server# %s\n", buf);
                printf("%s", buf);
            }
//            //--client
//            f_lock.open("server_running.lock",ios::in|ios::out|ios::binary);
//            int cnt;
//            f_lock.read((char*)&cnt,sizeof(cnt));
//            --cnt;
//            f_lock.write((char*)&cnt,sizeof(cnt));
//            f_lock.close();
//            //这样会存在一点小问题就是互斥的问题 -- solved by sending message
        }

    } 
    else{
        //server is running - change # clients
//        int cnt;
//        f_lock.read((char*)&cnt,sizeof(cnt));
//        cnt++; //client++
//        f_lock.seekp(0,ios::beg);
//        f_lock.write((char*)&cnt,sizeof(cnt));
//        f_lock.close();

        int msgid = getMsgQueue();
        char buf[MAX_TEXT] = {0};


        //tell the server to add count of clients
        strcpy(buf,"client start");
        sendMsgQueue(msgid, CLIENT_TYPE, buf);

        //running
        while(1)
        {
            BOLDGREEN<<"Yongqiang@HPC:# ";
            RESET;
            cout.flush();
            //这样会读到换行符
            //fgets(buf,MAX_TEXT,stdin);
            //一种巧妙的读取方法
           // scanf("%[^\n]" , buf);
            string tmp;
            while(1)
            {
                std::getline(cin,tmp);
                if(tmp!="")
                    break;
            }
            strcpy(buf,tmp.c_str());
            sendMsgQueue(msgid, CLIENT_TYPE, buf);
            if(strcasecmp("exit", buf) == 0){
                strcpy(buf,"client exit");
                sendMsgQueue(msgid, CLIENT_TYPE, buf);
                break;
            }
            sendMsgQueue(msgid, CLIENT_TYPE, buf);

            //printf("send done, wait recv...\n");

            recvMsgQueue(msgid, SERVER_TYPE, buf);
            //printf("server# %s\n", buf);
            printf("%s", buf);
        }
//        //--client
//        f_lock.open("server_running.lock",ios::in|ios::out|ios::binary);
//        f_lock.read((char*)&cnt,sizeof(cnt));
//        --cnt;
//        f_lock.write((char*)&cnt,sizeof(cnt));
//        f_lock.close();
    }

    //这样会存在一点小问题就是互斥的问题  -- solved
    return 0;
}