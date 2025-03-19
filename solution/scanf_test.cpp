//=====================================================================
//
// scanf_test.cpp - 从sscanf 引发问题,理解类型格式化问题
//
// Created by wwq on 2025/02/19
// Last Modified: 2025/02/19 10:38:31
//
//=====================================================================
#include <cstdint>
#include <cstdio>
#include <inttypes.h>
#include <iostream>
#include <string.h>
struct testA
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
};

// 扩展
// uint8_t 对应的是 %hhu。
// uint16_t 对应的是 %hu。注意，这里不是 %hhu，因为%hhu是专门用于unsigned char的。对于uint16_t，应该使用%hu，它表示一个无符号的短整数（short），但在这种情况下，它实际上用于表示16位无符号整数。
// uint32_t 对应的是 %u。对于32位无符号整数，标准的格式说明符是%u。
int test1()
{
    uint8_t value8 = 255;
    uint16_t value16 = 65535;
    uint32_t value32 = 4294967295U; // 32位无符号整数的最大值

    printf("uint8_t value: %hhu\n", value8);
    printf("uint16_t value: %" PRIu16 "\n", value16);
    printf("uint32_t value: %" PRIu32 "\n", value32);

    return 0;
}

// 基本描述:
// int 对应格式说明符：%d（有符号十进制整数）或 %u（无符号十进制整数，但通常不推荐用于int类型，因为它假设了无符号性）
// long 对应格式说明符：%ld（有符号长整数) C99及更高版本引入了固定宽度的整数类型，如int64_t和uint64_t, 64位系统上的long类型，可能需要使用%lld（有符号长长整数）和%llu（无符号长长整数）。然而，对于32位系统上的long类型，%ld和%lu通常是正确的
// float %f
// double 对应格式说明符：%lf（在printf中也可以使用%f，因为double参数会根据“默认参数提升”规则被提升为double类型，但为了清晰和避免潜在的可移植性问题，建议使用%lf）
// 在scanf中，必须使用%lf来读取double类型的值。
int test2()
{
    int i = 42;
    long l = 123456789L;
    float f = 3.14f;
    double d = 3.141592653589793;
    printf("int: %d\n", i);
    printf("long: %ld\n", l); // 对于32位系统上的long类型
    // 如果是在64位系统上，并且你确定long是64位的，那么应该使用%lld
    // printf("long (64-bit): %lld\n", (long long)l);
    printf("float: %f\n", f);
    printf("double: %lf\n", d); // 在printf中也可以使用%f，但为了清晰建议使用%lf
    return 0;
}

int main(int argc, char *argv[])
{
    testA a;
    memset(&a, 0xEE, sizeof(testA));
    int tmp[4] = { 0 };
    printf("\033[32m[%s %d] %d - %d - %d\033[0m\n", __func__, __LINE__, a.a, a.b, a.c);
    // 这个写法
    // sscanf("17.11.12.11","%d.%d.%d.%d", &a.a,  &tmp[0], &tmp[1], &tmp[2]);
    sscanf("17.11.12.11", "%hhu.%d.%d.%d", &a.a, &tmp[0], &tmp[1], &tmp[2]);
    printf("\033[32m[%s %d] %hhu - %d - %d\033[0m\n", __func__, __LINE__, a.a, a.b, a.c);

    test1();

    return 0;
}
