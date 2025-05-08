//=====================================================================
//
// array_access.c -
//
// Created by wwq on 2025/05/08
// Last Modified: 2025/05/08 10:21:59
//
//=====================================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 定义宏：自动计算数组大小并检查索引
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

// 可读写的安全访问宏（兼容 GNU C 的语句表达式）
#if defined(__GNUC__) || defined(__clang__)
#define ARRAY_ACCESS(arr, idx) ({                          \
    assert((idx) >= 0 && (size_t)(idx) < ARRAY_SIZE(arr)); \
    &(arr)[(idx)];                                         \
})
#else
// 非 GNU 编译器的替代方案（功能受限）
#define ARRAY_ACCESS(arr, idx) (                           \
    (void)((idx) >= 0 && (size_t)(idx) < ARRAY_SIZE(arr)), \
    (arr) + (idx))
#endif

void example_function()
{
    int my_array[10];

    // 正确访问
    for (int i = 0; i < 10; i++)
    {
        *ARRAY_ACCESS(my_array, i) = i; // 通过宏安全访问（解引用后赋值）
    }

    // 错误示例：越界访问（运行时会触发断言）
    *ARRAY_ACCESS(my_array, 10) = 42; // 索引 10 越界（有效索引 0-9）
}

int main()
{
    example_function();
    return 0;
}
