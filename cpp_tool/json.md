# [nlohmann-json](库https://github.com/nlohmann/json)

- 简单使用发送一个json数据，技巧两个大括号变中括号

```
{
    "class": "A",
    "command": "set",
    "paraList": [
        {
            "sList": [
                {
                    "clear": "",
                    "enable": "1",
                    "name": "2",
                    "period": "1"
                },
                {
                    "clear": "",
                    "enable": "1",
                    "name": "6",
                    "period": "1"
                }
            ],
            "name": "A"
        }
    ]
}
nlohmann::json j={
    {"class", "A"},
    {"command",""},
    {"paraList",{{
                     {"sList",
                     {{{"clear",""},{"enable","1"},{"name","6"},{"period","1"}},{{"clear",""},{"enable","1"},{"name","6"},{"period","1"}}}
                 },{"name","A"}}
    }}
};
```

<++>
