# json与protobuf互转

```cpp
#头文件
#include <google/protobuf/message.h>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/text_format.h>

// json-string 转 protobuf message
util:Status google::protobuf::util::JsonStringToMessage(const std::string content, google::protobuf::Message* message);

// protobuf 转 json-string
util:Status google::protobuf::util::MessageToJsonString(const google::protobuf::Message& message, std::string* str );

```

# protobuf字段判断可选结构体是否存在

```

```

<++>
