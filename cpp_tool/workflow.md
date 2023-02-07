# 消息队列

```
struct __msgqueue
{
	size_t msg_max;
	size_t msg_cnt;

	// 消息偏移量
	int linkoff;
	// 是否为拥堵
	int nonblock;

	// 消息队列的两个头
	void* head1;
	void* head2;

	// get队列
	void **get_head;

	// put队列头部和尾部
	void **put_tail;

	// 锁
	pthread_mutex_t get_mutex;
	pthread_mutex_t put_mutex;
	pthread_cond_t get_cond;
	pthread_cond_t put_cond;
};
```

# issue跟踪

- [workflow移植到嵌入式平台-qnx](https://github.com/sogou/workflow/issues/478)
- [workflow嵌入式观察者](https://github.com/sogou/workflow/issues/750)
