//=====================================================================
//
// df_h.cpp - 
//
// Created by wwq on 2023/12/22
// Last Modified: 2023/12/22 10:01:42
//
//=====================================================================
#if 0
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct FileSystemInfo {
    std::string filesystem;
    std::string size;
    std::string used;
    std::string available;
    std::string usePercent;
    std::string mountedOn;
};

std::vector<FileSystemInfo> parseDfOutput(const std::string& dfOutput) {
    std::vector<FileSystemInfo> filesystems;
    std::istringstream ss(dfOutput);
    std::string line;

    // 跳过第一行标题
    std::getline(ss, line);

    while (std::getline(ss, line)) {
        std::istringstream lineStream(line);
        FileSystemInfo info;
        lineStream >> info.filesystem >> info.size >> info.used >> info.available >> info.usePercent >> info.mountedOn;
        filesystems.push_back(info);
    }

    return filesystems;
}

int main() {
    std::ifstream dfOutputFile("/tmp/df_output.txt"); // 将df -h的输出保存到文件中
    std::string dfOutput((std::istreambuf_iterator<char>(dfOutputFile)), std::istreambuf_iterator<char>());

    std::vector<FileSystemInfo> filesystems = parseDfOutput(dfOutput);

    for (const auto& fs : filesystems) {
        if (fs.mountedOn == "/var/romlog") {
            std::cout << "/var/romlog usage: " << fs.usePercent << std::endl;
            break;
        }
    }

    return 0;
}
#endif
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>

struct FileSystemInfo {
    std::string filesystem;
    std::string size;
    std::string used;
    std::string available;
    std::string usePercent;
    std::string mountedOn;
};

std::vector<FileSystemInfo> parseDfOutput(const std::string& dfOutput) {
    std::vector<FileSystemInfo> filesystems;
    std::istringstream ss(dfOutput);
    std::string line;

    // 跳过第一行标题
    std::getline(ss, line);

    while (std::getline(ss, line)) {
        std::istringstream lineStream(line);
        FileSystemInfo info;
        lineStream >> info.filesystem >> info.size >> info.used >> info.available >> info.usePercent >> info.mountedOn;
        filesystems.push_back(info);
    }

    return filesystems;
}

int main() {
    FILE *fp;
    char path[1035];
    std::string dfOutput;

    /* 执行df -h命令 */
    fp = popen("df -h", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    /* 读取命令输出 */
    while (fgets(path, sizeof(path), fp) != NULL) {
        dfOutput += path;
    }

    pclose(fp);

    /* 解析输出并打印信息 */
    std::vector<FileSystemInfo> filesystems = parseDfOutput(dfOutput);
    for (const auto& fs : filesystems) {
        std::cout << "Filesystem: " << fs.filesystem << ", Size: " << fs.size << ", Used: " << fs.used << ", Available: " << fs.available << ", Use%: " << fs.usePercent << ", Mounted on: " << fs.mountedOn << std::endl;
    }

    return 0;
}

