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

# protobuf3中修改

- 直接去掉了required和option修饰符,所有字段都是optional的，而且对于原始数据类型字段不提供hasXxx()方法
- 如果对于默认字段的值为0，由于默认情况下该字段被忽略，并且在序列化和反序列化时不会包含该字段。如果希望序列化和反序列化时包含该字段，可以使用"optional"关键字来定义该字段，使用optional关键字定义的字段，如果没有被设置该值,则在序列化和反序列化时，都会包含该字段，并且该字段的值为0，如果希望在序列化时忽略该字段，可以使用"oneof"关键字来定义该字段。

```
message MyMessage{
    oneof my_filed{
        int32_t field1 = 1;
        string field2 = 2;
    }
}
```

在这种情况下只能设置field1和field2中的一个，如果设置了field1那么field2就会被忽略，在序列化和反序列化时只有field1

# protobuf版本

- protobuf3.2版本序列化成json,一些必选字段的值为0，或者字符串为空，就会出现传输中省略的情况。
- protobuf3.8增加了一些方法解决了这个问题。

```
using google::protobuf::util::JsonStringToMessage;
google::protobuf::util::JsonPrintOptions options;
options.add_whitespace = true;
options.always_print_primitive_fields = true;
options.preserve_proto_field_names = true;
return MessageToJsonString(message, &json, options).ok();
```
