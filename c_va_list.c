#include <stdio.h>
#include <stdarg.h>
#include <string.h>
char *strcat_muti(char *buf, ...)
{
    va_list arg_ptr; // 1. 定义可变参数列表
    char *s = NULL;  // 2. 临时字符串指针
    if (!buf)
        return buf; // 3. 安全检查：如果buf为空直接返回

    va_start(arg_ptr, buf);      // 4. 初始化可变参数，从buf后第一个参数开始
    s = va_arg(arg_ptr, char *); // 5. 获取第一个可变参数

    while (s)
    {                                // 6. 循环直到遇到NULL指针
        strcat(buf, s);              // 7. 将当前字符串连接到buf末尾
        s = va_arg(arg_ptr, char *); // 8. 获取下一个可变参数
    }

    va_end(arg_ptr); // 9. 清理可变参数列表
    return buf;      // 10. 返回连接后的字符串
}

// 优化后的字符串拼接复制，支持多字符串

#define STRCAT_MULTI_SAFE(buf, buf_size, ...) \
    strcat_multi_impl(buf, buf_size, __VA_ARGS__, NULL)
char *strcat_multi_impl(char *buf, size_t buf_size, ...)
{
    if (!buf || buf_size == 0)
    {
        return NULL;
    }

    va_list arg_ptr;
    char *current_str = NULL;
    char *dest = buf + strlen(buf);                 // 直接指向当前字符串结尾
    size_t remaining = buf_size - (dest - buf) - 1; // 计算剩余空间

    // 初始检查
    if (dest - buf >= buf_size)
    {
        buf[buf_size - 1] = '\0';
        return buf;
    }

    // va_start 传参的第二个参数，表示从第几个参数后是可变参数
    va_start(arg_ptr, buf_size);

    current_str = va_arg(arg_ptr, char *);
    while (current_str != NULL && remaining > 0)
    {
        size_t str_len = strlen(current_str);

        // 计算实际可复制的长度
        size_t copy_len = (str_len < remaining) ? str_len : remaining;

        // 手动复制字符
        for (size_t i = 0; i < copy_len; i++)
        {
            *dest++ = current_str[i];
        }

        // 更新剩余空间
        remaining -= copy_len;

        // 如果空间不足，提前退出
        if (remaining == 0)
        {
            break;
        }

        current_str = va_arg(arg_ptr, char *);
    }

    // 确保字符串正确终止
    *dest = '\0';

    va_end(arg_ptr);
    return buf;
}

int main(int argc, char *argv[])
{
    char test[128] = { 0 };
    strcat_muti(test, "aaaa", "bbbb", NULL);
    char testa[128] = { 0 };
    STRCAT_MULTI_SAFE(testa, 128, "aaaa", "bbbb");
    printf("%s\n", test);
    printf("%s\n", testa);
    return 0;
}
