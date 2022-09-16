//=====================================================================
//
// time.cpp - 
//
// Created by wwq on 2022/09/16
// Last Modified: 2022/09/16 09:18:08
//
//=====================================================================
#include <time.h>
#include <string>
#include <sys/time.h>

std::string printTime()
{
	struct timeval _tv;
	struct tm _tm;
  gettimeofday(&_tv, NULL);
  localtime_r(&_tv.tv_sec, &_tm);
  char buf[128];
  snprintf(buf, sizeof(buf), "%d-%02d-%02d %02d:%02d:%02d.%03d",
		  1900 + _tm.tm_year,
		  1 + _tm.tm_mon,
		  _tm.tm_mday,
		  _tm.tm_hour,
		  _tm.tm_min,
		  _tm.tm_sec,
		  (int) (_tv.tv_usec / 1000));
  return buf;
}

int main()
{
	// printTime();
	printf("%s\n", printTime().c_str());
	return 0;
}
