#include <iostream>
#include <vector>
#include <chrono>

#include "ThreadPool.h"

int main()
{
    
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

	uint8_t aa = 100;
	std::string test = "for test";
    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            pool.enqueue([i, aa, test] {
				printf("===aaa:%d\n", aa);
				printf("===aaa:%s\n", test.c_str());
                std::cout << "hello " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "world " << i << std::endl;
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}
