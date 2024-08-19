# 监控文件变化

- [Linux C 使用 inotify 监控文件或目录变化](https://www.cnblogs.com/PikapBai/p/14480881.html)

	- 注意的问题: vim编译修改的文件不能监听，这是由于 vim 的工作机制引起的，vim 会先将源文件复制为另一个文件，然后在另一文件基础上编辑(后缀名为 swp)，保存的时候再将这个文件覆盖源文件。此时原来的文件已经被后来的新文件代替，因此监视对象所监视的文件已经不存在了，所以自然不会产生任何事件。

- 查看文件更改时间，定义文件变化

```cpp
bool hasFileChanged()
{
    std::time_t currentTime = getFileLastModifiedTime();
    if (currentTime != m_LastModifiedTime)
    {
        m_LastModifiedTime = currentTime;
        return true;
    }
    return false;
}

std::time_t getFileLastModifiedTime()
{
    struct stat fileStat;
    if (stat(m_FilePath.c_str(), &fileStat) == 0)
    {
        return fileStat.st_mtime;
    }
    return 0;
}
```

- 查看某个路径下，相同后缀文件个数

```cpp

/**
 * @brief 查找路径下，某个文件个数
 * @param path 路径
 * @param suffix  后缀
 * @param  flag 是否递归查找
 * @return int  个数
 */
int count_files_with_suffix(const char *path, const char *suffix, uint8 flag)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    int count = 0;

    if (!(dir = opendir(path)))
    {
        perror("opendir");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        char fullpath[1024];

        // 跳过"."和".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (stat(fullpath, &statbuf) == -1)
        {
            perror("stat");
            continue;
        }

        // 如果是目录，则递归调用
        if (S_ISDIR(statbuf.st_mode) && flag)
        {
            count += count_files_with_suffix(fullpath, suffix);
        }
        else
        {
            // 检查文件是否以指定后缀结尾
            size_t len = strlen(entry->d_name);
            if (len > strlen(suffix) && strcmp(entry->d_name + len - strlen(suffix), suffix) == 0)
            {
                count++;
            }
        }
    }

    closedir(dir);
    return count;
}

```
