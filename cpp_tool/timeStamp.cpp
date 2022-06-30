//=====================================================================
//
// timeStamp.cpp - 
//
// Created by wwq on 2022/06/30
// Last Modified: 2022/06/30 15:02:27
//
//=====================================================================

// 时间戳需要定义为uint64_t
// 32位中int 表示4字节,时间戳会超

#include <time.h>
#include <sys/time.h>
#include <string>

// 时间
uint64_t now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	// 16位
	/* int64_t step = ((int64_t)tv.tv_sec) * 1000 * 1000 + tv.tv_usec; */
	// 13位
	int64_t step = ((int64_t)tv.tv_sec) * 1000 + tv.tv_usec/1000;
	/* printf("now: %lld\n", step); */
	return step;
}

//时间戳转化为时间 毫秒级
std::string Stamp2Time(uint64_t timestamp)
{
        int ms = timestamp % 1000;//取毫秒
        time_t tick = (time_t)(timestamp/1000);//转换时间
        struct tm tm;
        char s[40];
        tm = *localtime(&tick);
        strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
        std::string str(s);
        str = str+ " " + std::to_string(ms);
        return str;
}
