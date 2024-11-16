#include <iostream>
#include <sstream>
#include <string>
#include <utility>

// ANSI 转义码
#define RESET "\033[0m"           // 重置颜色
#define RED "\033[31m"            // 红色
#define GREEN "\033[32m"          // 绿色
#define YELLOW "\033[33m"         // 黄色
#define BLUE "\033[34m"           // 蓝色
#define MAGENTA "\033[35m"        // 品红
#define CYAN "\033[36m"           // 青色
#define BRIGHT_RED "\033[91m"     // 明亮红色
#define BRIGHT_GREEN "\033[92m"   // 明亮绿色
#define BRIGHT_YELLOW "\033[93m"  // 明亮黄色
#define BRIGHT_BLUE "\033[94m"    // 明亮蓝色
#define BRIGHT_MAGENTA "\033[95m" // 明亮品红
#define BRIGHT_CYAN "\033[96m"    // 明亮青色

// 定义颜色数组
const char *colors[] = { RED,        GREEN,        YELLOW,        BLUE,        MAGENTA,        CYAN,
                         BRIGHT_RED, BRIGHT_GREEN, BRIGHT_YELLOW, BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN };

#if __cplusplus < 201703L
// #error "This code requires C++17 support. Please use a C++17 compatible compiler."
template <typename T>
std::string toString(const T &value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void printColoredValue(int index, int value)
{
    std::cout << colors[index % (sizeof(colors) / sizeof(colors[0]))] << value << RESET << " ";
}

void printColoredValue(int index, double value)
{
    std::cout << colors[index % (sizeof(colors) / sizeof(colors[0]))] << value << RESET << " ";
}

void printColoredValue(int index, const std::string &value)
{
    std::cout << colors[index % (sizeof(colors) / sizeof(colors[0]))] << value << RESET << " ";
}

void printColoredValues(int index)
{
    std::cout << std::endl;
}

template <typename T, typename... Args>
void printColoredValues(int index, const T &value, const Args &...args)
{
    printColoredValue(index, value);
    printColoredValues(index + 1, args...);
}

// 主函数
template <typename... Args>
void printColoredValues(const Args &...args)
{
    printf("<%s %d>cpp11\n", __func__, __LINE__);
    printColoredValues(0, args...);
}

//---------------------------------------------------------------------
// 方法2
//---------------------------------------------------------------------
// 打印单个值的实现
template <typename T>
void print_impl(uint8_t &index, T &&t)
{
    std::cout << colors[index % (sizeof(colors) / sizeof(colors[0]))] << t << RESET << " ";
    index++;
}

// 打印多个值的实现
template <typename T, typename... Args>
void print_impl(uint8_t &index, T &&t, Args &&...args)
{
    std::cout << colors[index % (sizeof(colors) / sizeof(colors[0]))] << t << RESET << " ";
    index++;
    print_impl(index, std::forward<Args>(args)...); // 递归调用
}

// 主打印函数
template <typename... Args>
void printa(Args &&...args)
{
    uint8_t index = 0;                              // 在这里初始化 index
    print_impl(index, std::forward<Args>(args)...); // 转发参数
    std::cout << std::endl;                         // 换行
}

//---------------------------------------------------------------------
// 方法3
//---------------------------------------------------------------------
void print3()
{
    int a = 1;
    float b = 3.14;
    std::string c = "Hello";
    int d = 100;
    float e = 200.5;
    int index = 0;
    std::cout << colors[index++ % (sizeof(colors) / sizeof(colors[0]))] << a << RESET << "|";
    std::cout << colors[index++ % (sizeof(colors) / sizeof(colors[0]))] << b << RESET << "|";
    std::cout << colors[index++ % (sizeof(colors) / sizeof(colors[0]))] << c << RESET << "|";
    std::cout << colors[index++ % (sizeof(colors) / sizeof(colors[0]))] << d << RESET << "|";
    std::cout << colors[index++ % (sizeof(colors) / sizeof(colors[0]))] << e << RESET << "|";
    std::cout << std::endl;
}
#else
// 可变参数函数
template <typename... Args>
void printColoredValues(Args... args)
{
    printf("<%s %d>cpp17\n", __func__, __LINE__);
    int index = 0;
    ((std::cout << colors[index++ % (sizeof(colors) / sizeof(colors[0]))] << args << RESET << " "), ...);
    std::cout << std::endl;
}
#endif

int main()
{
    // 调用可变参数函数，打印不同类型的值
    printColoredValues(42, 3.14, "Hello", 100, 200.5);
    printa(42, 3.14, "Hello", 100, 200.5);
    print3();
    return 0;
}
