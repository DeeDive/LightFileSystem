//
// Created by Yongqiang Dou on 6/4/2019.
//
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>


//system: Arch Linux x86_64
//Linux内核： 4.15.13-1-ARCH
//gcc 版本：gcc 7.3.1
//编译参数：gcc -o -pthread

/*死锁开关*/
#define lock

#define N 5
pthread_mutex_t chops[N];
void P(pthread_mutex_t *sem)
{
    pthread_mutex_lock(sem);
}
int tryP(pthread_mutex_t *sem)
{
    return pthread_mutex_trylock(sem);
}
void V(pthread_mutex_t *sem)
{
    pthread_mutex_unlock(sem);
}
void init_sem()
{
    for(int i=0;i<N;i++)
        pthread_mutex_init(&chops[i],NULL);
}

void* Person(void *arg)
{
    char p=*(char*)arg;
    char Person_id=p;
    int left=Person_id-'A';
    int right=(left+1)%N;
    while(1)
    {
        usleep(3);//思考
        P(&chops[left]);//拿起左边的筷子
        printf("Person %c is using chopstick %d\n",Person_id,left);

        //#define lock后可观察到死锁现象
#ifdef lock
        P(&chops[right]);//直接拿右边的筷子
#else
        if( tryP(&chops[right]) == EBUSY )//尝试拿右边的筷子
        {
            V(&chops[left]); //拿不到就放下左边的
            printf("Person %c released chopstick %d\n",Person_id,left);
            continue;
        }
#endif

        printf("Person %c is using chopstick %d\n",Person_id,right);
        usleep(3);//吃饭
        V(&chops[left]);//放下左边的筷子
        printf("Person %c released chopstick %d\n",Person_id,left);
        V(&chops[right]);//放下右边的筷子
        printf("Person %c released chopstick %d\n",Person_id,right);
    }

}

int main()
{
    init_sem();

    pthread_t Person_t[N];

    pthread_create(&Person_t[0],NULL,Person,"A");
    pthread_create(&Person_t[1],NULL,Person,"B");
    pthread_create(&Person_t[2],NULL,Person,"C");
    pthread_create(&Person_t[3],NULL,Person,"D");
    pthread_create(&Person_t[4],NULL,Person,"E");

    for(int i=0;i<N;i++)
    {
        pthread_join(Person_t[i],NULL);
    }

    return 0;
}


