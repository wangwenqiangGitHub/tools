# ����ļ��仯

- [Linux C ʹ�� inotify ����ļ���Ŀ¼�仯](https://www.cnblogs.com/PikapBai/p/14480881.html)

	- ע�������: vim�����޸ĵ��ļ����ܼ������������� vim �Ĺ�����������ģ�vim ���Ƚ�Դ�ļ�����Ϊ��һ���ļ���Ȼ������һ�ļ������ϱ༭(��׺��Ϊ swp)�������ʱ���ٽ�����ļ�����Դ�ļ�����ʱԭ�����ļ��Ѿ������������ļ����棬��˼��Ӷ��������ӵ��ļ��Ѿ��������ˣ�������Ȼ��������κ��¼���

- �鿴�ļ�����ʱ�䣬�����ļ��仯

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

