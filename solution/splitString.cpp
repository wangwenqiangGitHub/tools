#include <iostream>
#include <string>
#include <vector>
std::vector<std::string> splitString(const std::string &str, char delimiter)
{
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos)
    {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    if (start < str.length())
    {
        tokens.push_back(str.substr(start));
    }
    return tokens;
}
int main(int argc, char *argv[])
{
    std::string fileName = "AAA-BBB-CCC_DDDD_94_20241217_200406_993_f";
    std::vector<std::string> tokens = splitString(fileName, '_');
    for (auto &iter : tokens)
    {
        std::cout << iter << std::endl;
    }

    return 0;
}
