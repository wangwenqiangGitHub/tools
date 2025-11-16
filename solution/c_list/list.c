//=====================================================================
//
// list.c -侵入式链表
//
// Created by wwq on 2025/11/16
// Last Modified: 2025/11/16 21:02:30
//
//=====================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct list_head
{
    struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) };
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

// 初始化链表节点（让节点的 prev 和 next 都指向自己）
static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

// 将新节点插入到 prev 和 next 之间
static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

// 在 head 后面插入新节点（头部插入）
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

// 从链表中删除节点(只需要修改前后节点的指针)
static inline __list_del(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

// 遍历链表的宏
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

// 内核风格 container_of 宏（安全转换指针）
#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr); \
    (type *)( (char *)__mptr - offsetof(type, member) ); })

void list_for_each_callback(struct list_head *head, void (*callback)(struct list_head *node))
{
    struct list_head *pos;
    list_for_each(pos, head)
    {
        callback(pos);
    }
}

//-------------------------------测试数据结构--------------------------------------

struct student
{
    int id;
    char name[20];
    struct list_head list;
};

void print_student(struct list_head *node)
{
    struct student *stu = (struct student *)((char *)node - offsetof(struct student, list));
    printf("ID: %d, Name: %s\n", stu->id, stu->name);
}

// 回调2：统计学生总数（通过外部变量传递结果）
int total = 0;
void count_student(struct list_head *node)
{
    total++; // 每次回调计数+1
}

// 回调3：释放学生节点的内存
void free_student(struct list_head *node)
{
    struct student *stu = container_of(node, struct student, list);
    free(stu); // 释放整个学生结构体
}

// -------------------------- 主函数测试 --------------------------
int main()
{
    // 1. 初始化链表头
    LIST_HEAD(student_head); // 等价于 struct list_head student_head = {&student_head, &student_head}

    // 2. 创建3个学生节点并插入链表
    struct student *s1 = malloc(sizeof(struct student));
    s1->id = 1001;
    strcpy(s1->name, "Alice");
    INIT_LIST_HEAD(&s1->list);               // 初始化节点的链表指针
    list_add_tail(&s1->list, &student_head); // 尾部插入

    struct student *s2 = malloc(sizeof(struct student));
    s2->id = 1002;
    strcpy(s2->name, "Bob");
    INIT_LIST_HEAD(&s2->list);
    list_add_tail(&s2->list, &student_head);

    struct student *s3 = malloc(sizeof(struct student));
    s3->id = 1003;
    strcpy(s3->name, "Charlie");
    INIT_LIST_HEAD(&s3->list);
    list_add_tail(&s3->list, &student_head);

    // 3. 使用回调函数遍历并打印所有学生
    printf("所有学生信息：\n");
    list_for_each_callback(&student_head, print_student);

    // 4. 使用回调函数统计学生总数
    total = 0; // 重置计数
    list_for_each_callback(&student_head, count_student);
    printf("\n学生总数：%d\n", total);

    // 5. 使用回调函数释放所有节点内存
    list_for_each_callback(&student_head, free_student);
    // 注意：释放后链表头仍存在，但节点已被删除（此时链表为空）

    return 0;
}
