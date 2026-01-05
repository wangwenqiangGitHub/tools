/**
 * advanced_features.c
 * 演示消息队列的高级特性
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
    key_t key = ftok("/tmp", 'C');
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        perror("msgget failed");
        return 1;
    }

    // ============================================
    // 1. 获取和设置消息队列属性
    // ============================================
    struct msqid_ds buf;

    // 获取当前状态
    if (msgctl(msgid, IPC_STAT, &buf) == -1)
    {
        perror("msgctl IPC_STAT failed");
    }
    else
    {
        printf("Current queue status:\n");
        printf("  Messages in queue: %lu\n", buf.msg_qnum);
        printf("  Max bytes per message: %lu\n", buf.msg_qbytes);
        printf("  Last send PID: %d\n", buf.msg_lspid);
        printf("  Last receive PID: %d\n", buf.msg_lrpid);

        // 修改队列大小
        buf.msg_qbytes = 8192; // 设为8KB
        if (msgctl(msgid, IPC_SET, &buf) == -1)
        {
            perror("msgctl IPC_SET failed");
        }
        else
        {
            printf("Queue size updated to %lu bytes\n", buf.msg_qbytes);
        }
    }

    // ============================================
    // 2. 多种消息类型处理
    // ============================================
    struct msgbuf
    {
        long mtype;
        char mtext[100];
    };

    // 发送不同类型消息
    struct msgbuf msg;

    // 发送紧急消息（类型高优先级）
    msg.mtype = 1; // 高优先级
    sprintf(msg.mtext, "Urgent message");
    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

    // 发送普通消息
    msg.mtype = 10; // 普通优先级
    sprintf(msg.mtext, "Normal message");
    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

    // 发送低优先级消息
    msg.mtype = 100; // 低优先级
    sprintf(msg.mtext, "Low priority message");
    msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

    printf("\nMessages sent with types: 1, 10, 100\n");

    // ============================================
    // 3. 多种接收方式
    // ============================================
    printf("\nReceiving messages:\n");

    // 接收类型为1的消息（最高优先级）
    if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, IPC_NOWAIT) != -1)
    {
        printf("  Received type %ld: %s\n", msg.mtype, msg.mtext);
    }

    // 接收类型小于等于10的消息
    if (msgrcv(msgid, &msg, sizeof(msg.mtext), -10, IPC_NOWAIT) != -1)
    {
        printf("  Received type <= 10: %s\n", msg.mtext);
    }

    // ============================================
    // 4. 错误处理和资源清理
    // ============================================
    // 检查队列中的消息数量
    msgctl(msgid, IPC_STAT, &buf);
    printf("\nRemaining messages: %lu\n", buf.msg_qnum);

    // 清空队列
    while (msgrcv(msgid, &msg, sizeof(msg.mtext), 0, IPC_NOWAIT) != -1)
    {
        printf("  Discarded: %s\n", msg.mtext);
    }

    if (errno != ENOMSG)
    {
        perror("Error clearing queue");
    }

    // 删除消息队列
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl IPC_RMID failed");
    }
    else
    {
        printf("\nMessage queue deleted\n");
    }

    return 0;
}
