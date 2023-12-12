#include <iostream>
#include <vector>
#include <algorithm>

class TimedEventImpl {
public:
    TimedEventImpl(int trigger_time) : trigger_time_(trigger_time) {}
    int next_trigger_time() const { return trigger_time_; }

private:
    int trigger_time_;
};

void algorithm_1()
{
    std::vector<TimedEventImpl*> active_timers;
	// vector需要先排序

    // 添加一些示例数据
    active_timers.push_back(new TimedEventImpl(10));
    active_timers.push_back(new TimedEventImpl(20));
    active_timers.push_back(new TimedEventImpl(30));
    active_timers.push_back(new TimedEventImpl(40));
    active_timers.push_back(new TimedEventImpl(50));

    // 取消时间
    int cancel_time = 25;

    // 使用算法移除满足条件的元素
    active_timers.erase(
        std::lower_bound(active_timers.begin(), active_timers.end(), nullptr,
            [cancel_time](TimedEventImpl* a, TimedEventImpl* b) {
                (void)b;
				printf("------%d %d\n", a->next_trigger_time(),a->next_trigger_time() > cancel_time);
                return a->next_trigger_time() < cancel_time;
            }),
        active_timers.end()
    );

    // 打印剩余的元素
    for (auto timer : active_timers) {
        std::cout << "Next trigger time: " << timer->next_trigger_time() << std::endl;
    }

    // 释放内存
    for (auto timer : active_timers) {
        delete timer;
    }

}

void algorithm_2()
{
    std::vector<TimedEventImpl*> active_timers;
	// vector需要先排序
    // 添加一些示例数据
    active_timers.push_back(new TimedEventImpl(10));
    active_timers.push_back(new TimedEventImpl(20));
    active_timers.push_back(new TimedEventImpl(30));
    active_timers.push_back(new TimedEventImpl(40));
    active_timers.push_back(new TimedEventImpl(50));

    // 取消时间
    int cancel_time = 25;

    // 使用算法移除不满足条件的元素
    active_timers.erase(
        std::remove_if(active_timers.begin(), active_timers.end(),
            [cancel_time](TimedEventImpl* a) {
                return a->next_trigger_time() <= cancel_time;
            }),
        active_timers.end()
    );

    // 打印剩余的元素
    for (auto timer : active_timers) {
        std::cout << "---------Next trigger time: " << timer->next_trigger_time() << std::endl;
    }

    // 释放内存
    for (auto timer : active_timers) {
        delete timer;
    }
}

int main() {
	algorithm_1();
	algorithm_2();
    return 0;
}

