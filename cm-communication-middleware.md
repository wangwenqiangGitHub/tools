# DDS

### dds well know

- multicast 组播
- unicast 单播
- broadcast 广播

### Fast-DDS

- Foonathan
  Memory库是一个C++内存分配器，提供更灵活,更高效的内存管理功能。它提供了各种内存分配器，包括堆栈分配器,静态分配器和共享内存分配器，以满足不同的内存管理需求，该库还提供了对内存布局和对齐的精细控制，以及内存操作的类型安全封装。
- Fast CDR库是一个用于序列化与反序列化数据的C++库，它实现了OMG(是 Object Management Group 制定了面向对象技术相关标准)的快速序列化规范(Fast
  CDR).该库旨在提供高性能的数据序列化和反序列化功能,适合嵌入式系统和对性能要求较高的应用程序。Fast CDR库可以帮助用户在不同平台和架构之间高效地传输和存储数据。
- 零拷贝通信:零拷贝通信允许在同一台机器上的应用程序之间传输数据,
  而无需将数据复制到内存中，从而节省时间和资源.为了实现这一点,dds使用DataWriter和DataReader之间的数据共享传递,以及应用程序和DDS之间的数据缓冲区借用。**Data-Sharing**
  使用共享内存在DataWriter和DataReader之间提供通讯通道。因此不需要复制样本数据来传输它。**DataWriter**
  样本借用是一个DDS扩展，它允许应用程序为DataWriter发布的样本借用缓冲区。样本可以直接在这个缓冲区上构建，之后无需将其复制到DataWriter中。这可以防止在发布应用程序和DataWriter之间复制数据。如果使用Data-Sharing则是借出的数据缓冲区将位于共享内存本身中。**DataReader**读取数据也可以通过借用缓冲区来完成。应用程序获取接收到的样本作为对接收队列本身的引用。这样可以防止将数据从DataReader复制到接收应用程序。同样，如果使用Data-Sharing，则借出的数据将在共享内存中，并且确实与DataWriter历史记录中使用的内存缓冲区相同。
- Loanable借阅数据
- dynamic-types是一种机制，用于在运行时动态地定义和解析数据类型。这种机制允许系统在不需要预先知道数据类型的情况下进行通信和交换。通过dynamic-types，Fast-DDS可以在运行时根据接收到的数据动态地解析其类型，并进行相应的处理和转换。
- locator 定位器,在网络编程中指的是网络上的节点或者服务的地址信息, IP地址 端口 用于唯一标识网络上的资源
- ResourceEvent类是表示资源的事件, 创建 销毁 分配 释放;资源类型,事件类型,时间戳等属性,以及处理资源时间的回调函数等方法.处理监听和处理资源的事件
- PublisherQos类是定义发布者(Publisher)的服务质量(Qos参数的类),用于设置和获取发布者的Qos参数，例如可靠性,实时性,持久性,传输方式等。该类通常定义默认的Qos参数数据
- DomainParticipantImpl类
  代表了DDS域中的参与者,创建和管理发布者(Publisher)和订阅(Subscriber),创建和管理主题(Topic).管理Qos(Quality of
  Service)配置,包括数据传输的可靠性,实时性,安全性等方面的配置和管理,处理与其他参与者的通信,包括数据的发布和订阅。主要作用
  - 加入或离开特定的DDS域:
    DDS域是指一组应用程序实体(如发布者,订阅者,主题),他们共享相同的配置或者数据分发策略.DomainParticipant允许应用程序在一个给定的DDS域中发布或者订阅数据.
  - 创建或者销毁发布者,订阅者和主题:DomainParticipant充当工厂,用于在参与的域中创建和销毁发布者,订阅者和主题实例.
  - 管理QOS(Quality of Service)策略:DomainParticipant允许应用程序配置和管理各种QoS策略,以满足不同的实时通信需求.
  - 提供发现服务: DomainParticipant负责实现DDS发现协议,以便在参与的域中自动发现其他参与者,发布者,订阅者和主题
  - DomainParticipant实现原理:
    - 实例化时,需要提供一个域ID。这个ID用于在DDS体系结构中唯一标识一个特定的域. Fast-DDS还允许用户选择特定的参与者发现协议和传输配置
    - DomainParticipant类内部包含发布者和订阅者实例的集合。使用`create_topic()和create_subscriber()`方法,可以在参与的域中创建新的发布者或者订阅者实例。
    - DomainParticipant还提供了用于创建和删除主题的方法,如`create_topic和delet_topic`,主题是发布者和订阅者之间共享的数据通信通道。
    - FastDDS通过使用基于插件的体系结构实现了多种发现协议。DomainParticipant负责协调和管理这些发现插件，以实现自动发现和通信。
    - DomainParticipan类负责管理Qos策略，例如可靠性，持久性，延迟预算等，以满足不同的应用程序需求.
  - ContentFilterProperty数据过滤的属性,数据过滤器允许用户定义一些条件，以便满足这些条件的数据才会被传输或者接收。
  - Subscriber类用于实现订阅数据并接收来自Publisher发布的数据,主要功能:
    - 创建和管理数据读取器(DataReader),用于接收特定主题的数据.
    - 实现订阅者端的QoS(Quality of Service)配置,包括数据传输的可靠性,实时性,安全性等方面的配置和管理.
    - 处理接收到的数据，可以注册回调函数来处理接收到的数据.
    - 监控订阅者与发布者之间的通信状态.
  - DomainEntity类继承自Entity类, 用于表示DDS域中的实体.域实体是指参与DDS通讯的实体,如发布者，订阅者，主题等
  - DomainParticipantFactory类是DomainParticipant实例的工厂类,DomainParticipant代表了DDS域中的参与者,它负责创建和管理发布者，订阅者和主题等实体
  ```
  static std::shared_ptr<DomainParticipantFactory> instance(
          new DomainParticipantFactory(),
          [](DomainParticipantFactory* p)
          {
          delete p;
          });
  std::shared_ptr<T> ptr(new T, [](T* p){
      delete p;
  })
  // 这个语法中new T 创建了一个类型为T的对象,并将其包装在std::shared_ptr中,紧接着,使用了一个lambda表达式作为第二个参数,这个lambda表达式定义了自定义的删除器。在lambda表达式中定义了当智能指针的引用计数器为0时，就会调用这个lambda表达式来释放这个T类型的对象。
  ```
  - EDP类(Endpoint Discovery
    Protocol)是管理和维护数据读取者和写入者之间的关系，包括发现,匹配和通知，这个类中调用了`on_subscription_matched()`函数
  - BuiltinProtocols类是用于管理和协调内置协议的类,主要负责DDS中的内置协议,比如PDP(Participant Discovery Protocol)和EDP(Endpoint
    Discovery Protocol),这些协议用于在DDS网络中管理和维护参与者(Participant),发布者(Publisher)和订阅者(Subscriber)之间的关系
  - RTPSParticipantImpl类是FastDDS中的用于实现RTPS协议的参与者功能的类,它负责创建和管理RTPS协议中的参与者，并处理与其他参与者的通信.数据的发布和订阅等功能.

### Fast-DDS 编译部署

- [官网编译](https://fast-dds.docs.eprosima.com/en/latest/installation/sources/sources_linux.html#fastddsgen-sl)
- 编译时打开example选项:

```
cmake .. -DCMAKE_INSTALL_PREFIX=/mnt/d/dds/doc/learnFastDDS/Fast-DDS/install -DCOMPILE_EXAMPLES=ON
```

- WSL运行DDSHelloWorldExample

```
tasklist | grep DDSHelloWorldExample
DDSHelloWorldExample         31556 Console                    1     11,788 K
#查找出pid
netstat -aon | findstr "31556"
UDP    0.0.0.0:7400           *:*                    31556
UDP    0.0.0.0:7410           *:*                    31556
UDP    0.0.0.0:7411           *:*                    31556
UDP    0.0.0.0:58497          *:*                    31556
UDP    172.20.28.45:58498     *:*                    31556
UDP    172.21.48.1:58499      *:*                    31556
UDP    192.168.44.1:58500     *:*                    31556
UDP    192.168.208.1:58501    *:*                    31556
# DDSHelloworldExample采用的是UDP
```

### FastDDS:HelloWorldExample

- HelloWorld.idl定义payload, 生成HelloWorld.h HelloWorld.cxx HelloWorldPubSubTypes.h
  HelloWorldPubSubTypes.cxx四个文件，包含了序列化与反序列化逻辑.
- DataWriterListener类允许用户在数据发布不同阶段注册回调函数,以便在数据发布过程中进行相应的处理。DataWriterListener提供了一种机制，允许用户监控和响应DataWriter的状态变化，从而实现对数据发布过程的灵活控制和处理。通过实现DataWriterListener接口，用户可以根据自身需求定义相应的处理逻辑，以确保数据发布的可靠性和稳定性。
  - `on_publication_matched(DataWriter* writer, const PublicationMatchedStatus& info);`当DataWriter与订阅者匹配时调用此方法。用户可以在这里处理DataWriter与订阅者的匹配事件。
  - `on_offered_deadline_missed(DataWriter* writer, const OfferedDeadlineMissedStatus& status);`当DataWriter未能满足其所宣布的最后期限时调用此方法。用户可以在这里处理最后期限未能满足的情况。
  - `on_offered_incompatible_qos(DataWriter* writer, const OfferedIncompatibleQosStatus& status)`当DataWriter的QoS设置与订阅者的QoS设置不兼容时调用此方法。用户可以在这里处理QoS不兼容的情况.
- eprosima::fastdds::dds::DomainParticipant 是代表DDS域中的参与者,负责创建和管理发布者,订阅者和主题等实体。
- eprosima::fastdds::dds::Publisher负责管理数据写入者(DataWriter).
- eprosima::fastdds::dds::Topic 代表DDS中的主题,用于定义数据的类型和名称，以便发布者和订阅者可以进行数据交换。
- eprosima::fastdds::dds::DataWriter 用于将数据发布到DDS网络中, 负责管理数据的写入和传输。

### ThreadX

- [MISRA-C标准](https://learn.microsoft.com/en-us/azure/rtos/threadx/overview-threadx)

### vsomeip
