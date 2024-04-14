//=====================================================================
//
// template_anydata.cpp - 
//
// Created by wwq on 2024/04/14
// Last Modified: 2024/04/14 22:35:19
//
//=====================================================================
#include <iostream>

template <typename... Ts>
struct MaxSizeOf;

/**
 * @brief 递归模版特化
 * @tparam T
 * @tparam Ts
 */
template <typename T, typename... Ts>
struct MaxSizeOf<T, Ts...> {
    static constexpr std::size_t otherSize = MaxSizeOf<Ts...>::value;
    static constexpr std::size_t tSize = sizeof(T);

    static constexpr std::size_t value = tSize > otherSize ? tSize : otherSize;
};

/**
 * @brief 递归终止特化: 当只有一个类型参数时直接返回该类型的sizeof值
 * @tparam T
 */
template <typename T>
struct MaxSizeOf<T> {
    static constexpr std::size_t value = sizeof(T);
};

int main(int argc, char *argv[]) {
    constexpr std::size_t maxSize =
	MaxSizeOf<int, char, double, long double>::value;
    std::cout << maxSize << std::endl;
    return 0;
}
