//=====================================================================
//
// bubbleSort.c -
//
// Created by wwq on 2023/09/21
// Last Modified: 2023/09/21 09:51:28
// vim命令，删除行尾空格:%s/\s\+$//g
// 冒泡算法是时间复杂度 空间复杂度o(1),冒泡算法只需要一个额外的空间用于交换元素，与待排序序列的大小无关
// 头插法
//=====================================================================
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
struct Node {
    int data;
    struct Node* next;
};

// 插入新节点
void insert(struct Node** head, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = (*head);
    (*head) = new_node;
}

// 冒泡排序
void bubble_sort(struct Node* head) {
    struct Node* i, * j;
    int temp;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// 打印链表
void print_list(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    insert(&head, 3);
    insert(&head, 1);
    insert(&head, 4);
    insert(&head, 2);
    insert(&head, 5);
    printf("Before sorting: ");
    print_list(head);
    bubble_sort(head);
    printf("After sorting: ");
    print_list(head);
    return 0;
}
