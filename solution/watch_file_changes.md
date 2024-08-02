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

