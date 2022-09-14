#include <cstdio>
#include <string>
#include <sstream>
#include <fstream>

// json传输数据必须是utf8的数据，其他格式的需要转成hex
std::string hexToString(const std::string& str)
{
	std::string result;
	for(size_t i=0; i < str.length(); i+=2)
	{
		std::string byte = str.substr(i, 2);
		char chr = (char)(int)std::strtol(byte.c_str(), NULL, 16);
		result.push_back(chr);
	}
	return result;
}

std::string stringToHex(const std::string& data)
{
	const std::string hex = "0123456789ABCDEF";
	std::stringstream ss;

	for(std::string::size_type i = 0; i< data.size();++i)
	{
		ss << hex[(unsigned char)data[i] >> 4] << hex[(unsigned char)data[i]&0xf];
	}
	return ss.str();
}

// 保存文件
void save_file()
{

	std::stringstream g_file_stream;
	g_file_stream.clear();
	g_file_stream.str("");
	g_file_stream << "test.txt";
	std::ofstream out;
	out.open(g_file_stream.str(), std::ios_base::app);
	out << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" <<"\n";
	out << "\n\n" ;
	out.close();
}
#include <algorithm>

void stringFind(std::string& request)
{
	std::string id;
	std::string puzzle;
	auto colon = std::find(request.begin(), request.end(), ':');
	if (colon != request.end())
	{
		id.assign(request.begin(), colon);
		puzzle.assign(colon+1, request.end());
		printf("%s \n%s \n",id.c_str(),puzzle.c_str());
	}
	else{
		printf("hhhhh\n");
	}
}

// std::string::const_iterator 对应着cbegin() cend()
void stringFind2(std::string& request)
{
	std::string test="testtwee:1234847378";
	printf("%s\n", test.c_str());
	std::string::const_iterator c = std::find(test.cbegin(), test.cend(), ':');
	std::string id;
	std::string pp;
	if(c != test.end())
	{
		id.assign(test.cbegin(), c);
		pp.assign(c+1, test.cend());
	}
	printf("%s \n%s \n",id.c_str(),pp.c_str());
}

// find world
void findN(const char* begin, const char* end)
{
	const char* start = begin;
	const char* space = std::find(start,end,' ');
	if(space != end)
	{
		// 跳过一个char
		start = space + 1;
	}
}

bool isIpv6(const std::string& buf)
{
	if(buf[0] == '[')
		return true;
	else
	{
		return false;
	}
}
// test需要为const, 才可以用std::string::const_iterator
// 要不返回的是std::string::iterator
int main()
{
	const std::string test="testtwee:1234847378";
	printf("%s\n", test.c_str());
	std::string::const_iterator c = std::find(test.begin(), test.end(), ':');
	std::string id;
	std::string pp;
	if(c != test.end())
	{
		id.assign(test.begin(), c);
		pp.assign(c+1, test.end());
	}
	printf("%s \n%s \n",id.c_str(),pp.c_str());
	std::string ip="[fe80::20c:29ff:fefa:3790]";
	if(isIpv6(ip))
		printf("is isIpv6\n");
	return 0;
}

