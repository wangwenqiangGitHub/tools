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
