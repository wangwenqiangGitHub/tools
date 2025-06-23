//=====================================================================
//
// test_create_pthread.cpp -
//
// Created by wwq on 2025/06/20
// Last Modified: 2025/06/20 17:09:49
// 编译命令:arm-linux-gnueabi-g++ test_create_pthread.cpp -o test_create_pthread -lpthread
//=====================================================================

#include <cinttypes>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

void *thread_func(void *arg)
{
    // pthread_detach(pthread_self());
    static uint64_t i = 0;
    printf("Thread running %" PRId64 "\n", i++);

    return NULL;
}

int main()
{
    while (1)
    {
        pthread_t tid;
        pthread_attr_t attr;
        // 默认栈空间大小8192KB, 8M
        pthread_attr_init(&attr);
        // pthread_attr_setstacksize(&attr, 500000);
        // 设置线程分离属性
        // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        if (pthread_create(&tid, &attr, thread_func, NULL) != 0)
        {
            perror("pthread_create failed");
            break;
        }
        // 没有调用 pthread_join, pthread_detach，线程结束后资源无法回收
        usleep(1000);
    }
    printf("main exit!\n");
    return 0;
}

