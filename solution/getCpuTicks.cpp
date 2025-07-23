#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h>
void testTimeSec()
{
    auto now = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count() << std::endl;

    struct timespec clocl = { 0 };
    clock_gettime(CLOCK_MONOTONIC, &clocl);
    printf("\033[32m[%s %d]%d\033[0m\n", __func__, __LINE__, clocl.tv_sec);
}

void testTiskMs()
{

    auto now = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() << std::endl;

    struct timespec clocl = { 0 };
    clock_gettime(CLOCK_MONOTONIC, &clocl);

    printf("\033[32m[%s %d]%d\033[0m\n", __func__, __LINE__, clocl.tv_sec * 1000 + clocl.tv_nsec / 1000000);
}

int main()
{
    testTimeSec();
	testTiskMs();
	return 0;
}