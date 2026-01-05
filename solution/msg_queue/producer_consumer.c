/**
 * producer_consumer.c
 * 生产者-消费者模型
 * 编译: gcc -o producer_consumer producer_consumer.c
 * 运行:
 *   终端1: ./producer_consumer consumer
 *   终端2: ./producer_consumer producer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

#define MAX_MSG_SIZE 256

struct msg_buffer
{
    long msg_type;
    char msg_text[MAX_MSG_SIZE];
    int msg_id;
    pid_t sender_pid;
    time_t send_time;
};

void producer(int msgid)
{
    struct msg_buffer msg;
    int msg_count = 0;

    printf("=== PRODUCER STARTED (PID: %d) ===\n", getpid());

    while (1)
    {
        msg.msg_type = 1; // 固定消息类型
        msg.msg_id = ++msg_count;
        msg.sender_pid = getpid();
        msg.send_time = time(NULL);

        // 生成消息内容
        snprintf(msg.msg_text, sizeof(msg.msg_text), "Message %d from producer PID %d at %ld", msg.msg_id, msg.sender_pid, msg.send_time);

        // 发送消息
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text) + sizeof(int) + sizeof(pid_t) + sizeof(time_t), 0) == -1)
        {
            perror("msgsnd failed");
            break;
        }

        printf("Producer sent: %s\n", msg.msg_text);

        // 等待一段时间
        sleep(1 + rand() % 3);

        // 每发送5条消息询问是否继续
        if (msg_count % 5 == 0)
        {
            printf("Continue producing? (y/n): ");
            char choice = getchar();
            getchar(); // 消耗换行符
            if (choice != 'y' && choice != 'Y')
            {
                break;
            }
        }
    }

    printf("Producer stopped after %d messages\n", msg_count);
}

void consumer(int msgid)
{
    struct msg_buffer msg;
    int received_count = 0;

    printf("=== CONSUMER STARTED (PID: %d) ===\n", getpid());
    printf("Press Ctrl+C to stop\n\n");

    while (1)
    {
        // 接收消息
        ssize_t bytes = msgrcv(msgid, &msg, sizeof(msg.msg_text) + sizeof(int) + sizeof(pid_t) + sizeof(time_t),
                               1,  // 只接收类型为1的消息
                               0); // 阻塞接收

        if (bytes == -1)
        {
            perror("msgrcv failed");
            break;
        }

        received_count++;

        // 显示消息
        printf("Consumer received #%d:\n", received_count);
        printf("  Message ID: %d\n", msg.msg_id);
        printf("  Type: %ld\n", msg.msg_type);
        printf("  Sender PID: %d\n", msg.sender_pid);
        printf("  Time: %s", ctime(&msg.send_time));
        printf("  Content: %s\n", msg.msg_text);

        // 模拟处理时间
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s [producer|consumer]\n", argv[0]);
        return 1;
    }

    // 创建消息队列
    key_t key = ftok("/tmp", 'B');

    int msgid = msgget(key, 0666 | IPC_CREAT);
    // int msgid = msgget(200001, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        perror("msgget failed");
        return 1;
    }

    printf("Message Queue ID: %d\n", msgid);

    // 根据参数选择角色
    if (strcmp(argv[1], "producer") == 0)
    {
        producer(msgid);
    }
    else if (strcmp(argv[1], "consumer") == 0)
    {
        consumer(msgid);
    }
    else
    {
        fprintf(stderr, "Invalid role: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
