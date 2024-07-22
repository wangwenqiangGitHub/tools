#include <stdio.h>
int main() {
    char str[] = "123,456,789";
    int  secondNum;
    // 跳过第一个数字（包括逗号）并读取第二个数字
    if (sscanf(str, "%*[^,],%d", &secondNum) == 1) {
        printf("The second number is: %d\n", secondNum);
    } else {
        printf("Failed to parse the string.\n");
    }
    return 0;
}
