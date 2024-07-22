//=====================================================================
//
// float.cpp -  float 转 BCD主要是为了保证float的精度问题
//
// Created by wwq on 2024/07/11
// Last Modified: 2024/07/11 08:30:40
//
//=====================================================================
#include <bitset>
#include <sstream>
#include <iostream>
#include <vector>
/**
 * @brief 
 * BCD码的表示方式:
 *       +------------------------------------------------------+
 *       |     |  7  |  6  |   5  | 4  |  3  |  2  |  1  |  0   |
 *       +------------------------------------------------------+
 *       |字节1| FLAG|  S  |  小数位W  |          BCD1          +
 *       +------------------------------------------------------+
 *       |字节2|          BCD2         |          BCD3          +
 *       +------------------------------------------------------+
 *       |字节3|          BCD4         |          BCD5          +
 *       +------------------------------------------------------+
 *
 *	   其中字节1为“定值性质”，FLAG＝1 即80H以上为新定值；
 *	   S: 符号位：1表示负数
 *	   W小数位：指明BCD1~5中小数位置，范围为0～3
 *	   ＝0，值V=B1 B2 B3 B4 B5 。0
 *	   ＝1，值V=B1 B2 B3 B4。 B5 
 *	   ＝2，值V=B1 B2 B3 。B4 B5
 *	   ＝3，值V=B1 B2 。B3 B4 B5
 * @param f   
 * @param &bcd
 */
void float2bcd(float f, uint8_t (&bcd)[3])
{
	std::ostringstream ss;
	std::string fs;
	// uint8_t B1 = 0, B2 = 0, B3 = 0, B4 = 0, B5 = 0;
    std::vector<uint8_t> digits; // 使用vector来存储多个uint8_t
	uint8_t tmp = 0;
	bcd[0] |= 0x80;
	if (f < 0) {
		bcd[0] |= 0x40;
		ss << -f;
	} else {
		ss << f;
	}
	fs = ss.str();
	printf("<%s %d> %s\n",__func__, __LINE__, fs.c_str());
	
    if (fs.length() > 5)
    {
        fs.substr(0, 5);
    }
     size_t dotPos = fs.find('.');
     if (dotPos != std::string::npos)
     {
		 printf("<%s %d>\n",__func__, __LINE__);
		 uint8_t w = fs.length() - dotPos - 1;
		 if (w > 0) {
             bcd[0] |= ( (tmp >> 4 | w) << 4);
         }
     }

	 printf("<%s %d>\n",__func__, __LINE__);
	
     // 遍历字符串
     for (char c : fs)
     {
         if (c >= '0' && c <= '9')
         {                              // 检查是否为数字字符
			printf("<%s %d>\n",__func__, __LINE__);
             digits.push_back(c - '0'); // 转换为uint8_t并存储
         }
         // 忽略小数点
     }
	 if (digits.size() < 4) {
		 auto len = digits.size();
		 for (size_t i = 0; i < 4 - len; i++) {
			 digits.push_back(0);
		 }
	 
	 }
	 for (auto& iter : digits) {
		printf("%d\n", iter);
	 }
	 bcd[1] = digits.at(0) << 4 | digits.at(1);
	 bcd[2] = digits.at(2) << 4 | digits.at(3);
}
int main(int argc, char *argv[])
{
	std::ostringstream ss;
	float a = -6.0133;
	ss << a;
	std::cout << ss.str() << std::endl;
	float f = 70.0;
	uint8_t t[3] = {0};
	float2bcd(f, t);
	for(int i = 0; i < 3; i++)
	{
		printf("%0x ", t[i]);
	}
	printf("\n");

	return 0;
}
