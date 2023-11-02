# 2023

### 引用&

- 引用不是变量
- 引用仅仅是变量的别名
- 引用没有自己独立的空间
- 引用要与它所引用的变量共享空间
- 对引用所要作的改变实际上对于它所引用的改变

- 引用的两个作用: 应用作为参数传递, 引用作为返回值
  - c语言中具有两种传参方式: 值传递-形参值的改变不能对实参产生影响，指针传递通过形参的改变使相应的实参改变，但程序容易产生错误且难以阅读
  - c++多了引用作为参数对传参的任何操作都能改变相应的实参的数据，使函数调用显得简单

### name managling 与 extern c

- c++重载中主要是对函数的名字进行了名字改编，c语言是不可以对名字进行名字改编的
- 如果c++中的函数不想改编，就添加extern c就可以

### inline与define

- 内联函数:当程序执行函数调用时，系统要建立栈空间，保护现场，传递参数以及控制程序的转移等等，这些工作需要系统时间和空间的开销, 有些情况下，函数本身功能简单，
  代码很短，但使用频率却很高，程序频繁调用该函数所花费的时间却很多，从而使得程序执行效率降低。
- 为了提高效率，一个解决办法就是不使用函数，直接将函数的代码嵌入到程序中，这种方法一是相同代码重复书写，二是程序可读性往往没有使用函数的好。
- 为了协调好效率和可读性之间的矛盾，c++提供了另一种方法，及定义内联函数，方法是再定义函数时用修饰次inline
- 内敛函数与带参数宏定义的区别: 内敛函数调用时，要求参数和形参的类型一致，另外内敛函数会对实参表达式进行求值，然后传递给形参，而宏调用时只用实参简单地替换形参。
- 内联函数是在编译的时候，在编译的地方将代码展开的，而宏则是在预处理进行替换的
- 而C++中建议采用inline函数来替换带参数的宏。

### 类型转换

- const\_cast
  - 用来移除对象的常量性(const away the constness)
  - const\_cast一般用于指针或者引用
  - 使用const\_cast去除const限定的目的不是为了修改它的内容
  - 使用const\_cast去除const限定，通常是为了函数能够接受这个实际参数
- static\_cast
  - 编译器隐式执行的任何类型转换都是可以static\_cast完成。
  - 当一个较大的算数类型赋值给较小的类型时，可以用shared\_cast进行强制转换。
  - 可以将void* 指针转换为某一类型的指针
  - 可以将基类指针指向派生类指针
  - 无法将const转化为nonconst;这个只有const\_cast才可以办得到
- reinterpret\_cast
  - reinterpret\_cast通常为操作数的位模式提供较低的重新解释，也就是说将数据以二进制存在形式的重新解释。
- dynamic\_cast基类与派生类向下转化

### c++ 类的特性

- 抽象
- 封装
- 继承
- 多态
- 类的设计需要满足开闭原则，软件中的对象(类,模块,函数)应该对于扩展是开放的，对于类的修改是关闭

```
封装是指将数据和行为封装在一个类中，对外部隐藏实现细节，只暴露必要的接口。这样可以保证数据的安全性和一致性，同时也方便了代码的维护和升级。
继承是指一个类可以继承另一个类的属性和方法，从而可以重用已有的代码，并且可以通过覆盖和扩展来实现新的。继承可以提高代码的复用性和可维护性，同时也可以使代码更加灵活和可扩展。
多态是指同一个方法可以在不同的对象上有不同的行为，这种行为称为动态绑定。多态可以提高代码的灵活性和可扩展性，同时也可以使代码更加简洁和易于理解。
封装、继承和多态之间的联系在于它们都是面向对象程的核心概念，都可以提高代码的复用性、可维护性和可扩展性。同时，继承和多态也可以通过封装来实现数据的安全性和一致性。
封装、继承和多态之间的区别在于它们的重点不同。封装的重点在于隐藏实现细节，保证数据的安全性和一致性；继承的重点在于重用已有的代码，并且可以通过覆盖和扩展来实现新的功能；多态的重点在于同一个方法可以在不同的对象上有不同的行为，提高代码的灵活性和可扩展性

覆盖(override)和重载(overload)都是面向对象编程中的概念，它们都与多态有关。
重载是指在同一个类中定义多个同名的方法，但是这些方法的参数类型、个数或顺序同。在调用这些方法时，编译器会根据传入的参数类型、个数或顺序来选择合适的方法进行调用。载可以提高代码的复用性和可读性，但是需要注意方法的命名和参数的类型、个数和顺序，以免造成淆。
覆盖是指子类重写父类的方法，使得子类对象在调用该方法时执行子类的方法而不是父类的方法。覆盖可以实现多态，提高代码的灵活性和可扩展性。在覆盖时需要注意方法的访问修饰符、返回值类型和参数列表必须与父类的方法一致，否则会出现编译错误。
```

### 类的构造和析构

- const成员的初始化只能在构造函数初始化列表中进行
- 引用成员的初始化只能在构造函数初始化列表中进行
- 类成员的初始化顺序与初始化列表无关，而与类的私有变量定义顺序有关
- 对于所有的对象都是常量，需要定义为枚举，而不是const
- 当函数的形参是类的对象，调用函数时，进行形参与实参的结合使用，这时要在内存中新建立一个局部对象，并把实参拷贝到新的对象中，理所当然也在调用拷贝构造。
- 当函数的返回值是类的对象，函数执行完成返回调用时使用，理由也是要建立一个临时对象中，再返回调用者。为什么不返回局部对象呢？因为局部对象在离开建立它的函数时，就已经消亡了，不可能在返回调用函数后继续生存，所以在处理这种情况时，编译系统会在调用函数表达式中创建一个无名临时对象，该临时对象的生存周期调用拷贝构造函数把该对象的值拷入临时对象，如果返回的是变量，处理过程类似，只是不调用构造函数。主要看是不是新建立一个变量，创建空间

### 软件UML

- 软件的静态建模和动态建模

### 类之间的关系

- 关联关系，一个类与另一个类之间的固定关系,双方是平级的，比如A的成员函数中有B& b(B的引用)。
- 聚合关系，整体与局部之间的关系，两个类不是平级的是整体(A类)与局部（B类)关系,B的生命周期与A无关
- 组合关系, 公司与部门之间的关系，公司是整体，公司解散后，部门随之解散。公司是A，部门是B,如果A销毁，B也销毁
- 依赖关系，从语义上讲A use B,偶然的，临时的B作为A的成员函数参数,B作为A的成员函数的局部变量；A的成员函数调用B的静态方法。A的函数传参使用了B,或者返回值为B
- 继承，关联，聚合，组合，依赖

### 值语义与对象语义

- 值语义-基于对象编程，值语义是指对象得拷贝与原对象无关，拷贝之后就与原对象脱离关系，彼此独立互不影响，c++中得内置类型都是值语义。string vector map 也是值语义
- 对象语义-面向对象编程:是面向对象下的对象，对象拷贝是禁止的(noncopyable), 一个对象被系统标准的复制方式复制后
- 值语义对象声明周期容易控制
- 对象语义对象生命不容易控制(通过智能指针来解决),智能指针实际上是将对象语义转化为值语义
- 值语义与对象语义是分析模型决定的，语言的语法技巧用来匹配模型。
- auto\_ptr 所有权独占，不能共享，但是可以转义
- shared\_ptr 所有权共享，内部维护了一个引用计数
- weak\_ptr 弱指针，他与shared\_ptr配合使用，解决循环引用问题

### 前向声明

- 头文件比较小,CPP文件包含这个头文件就会增大

### static

- c中有两种用法:
  - 用于函数内部修饰变量，即函数内的静态变量。这种变量的生存期长于该函数，使得函数具有一定的"状态"。使用静态变量的函数一般是不可重入的，也不一定是线程安全的。strock(3);
  - 在文件级别(函数体之外)，修饰变量或函数，表示该变量或函数只在本文件可见，其他文件看不到该变量或者函数。专业的说法叫"具有intenal
    linkage"(简而言之:不暴漏给别的translation unit).
  - c语言的两种用法比较明确，一般不容易混淆。
- c++新增两种用法:
  - 由于C++引入了类，在保持C语言兼容的同时，static 关键字又有了两种新的用法
  - 修饰类的数据成员, 即所谓"静态成员"。这种数据成员的生存期大于class的对象(实例instance).静态数据成员是每个class有一份，普通数据成员是每个instance有一份。
  - 用于修饰class的成员函数，即所谓“静态成员函数”,这种成员函数只是能访问静态成员和其他静态成员函数，不能访问非静态成员和非静态成员函数。 静态成员函数没有this指针。

### 友元函数,友元类

- 友元破坏了类的封装,作用在于提升程序的运行效率
- 友元函数: - 友元函数在类作用域外定义，但是它在类中就行说明 - 为了与该类的成员函数加以区别，定义的方式是在类中用关键字friend说明该函数: friend 类型 友元函数名(参数表);

- 友元类: 如果某类B的成员函数会频繁的存取另一个类A的数据成员，而A的数据成员的Private/Protectd限制造成B存取的麻烦，B只能通过A的public的成员函数进行间接存取 -
  把B做成A类的友元类，即A类向B类开发其Private/Protectd内容，让B直接存取 - 友元类: 一个类可以作为另一个类的友元 - 友元类的所有成员函数都是另一个类的友元函数 -
  友元类的声明: friend class name; - 友元关系是单向的(B是A的友元类，在A中friend class B;)并不代表A是B的友元类，B的一些私有-保护成员，A不能访问 -
  友元关系不能被传递(A是B的友元类，B又是C的友元类，并不代表A是C的友元类) - 友元关系不能被继承(A是B的友元类，C继承自A,并不代表C是B的友元类)

### 重载

- 分为两类:成员函数重载和非成员函数的重载
- 成员函数重载
  - 成员函数原型的格式:
    \
    函数类型 operator 运算符(参数表);
  - 成员函数的定义格式:
    \
    函数类型 类名::operator 运算符(参数表) { 函数体; }
- 非成员函数的重载:
  - 友元函数原型的格式: friend函数类型operator运算符(参数表);
  - 友元函数定义的格式: friend 函数类型 类名::operator 运算符(参数表){函数体;}

### 继承

- 派生类对象指针可以转换为基类指针，将派生类对象看成是基类对象。
- 基类指针无法转换成为派生类指针，无法将基类对象看成是派生类对象
- 派生类到基类的转换:
  - 当派生类以public方式继承,编译器可以自动执行的转换(向上转型upcasting安全转换)
    - 派生类对象指针自动转换为基类对象指针
    - 派生类对象引用转换为基类对象引用
    - 派生类对象自动转换为基类对象(特有的成员消息)
  - 当派生类以private/protected方式继承基类时
    - 派生类对象指针(引用)转化为基类对象指针(引用)需要强制类型转化，但是不能static\_cast,要reubteroret\_cast
    - 不能把派生类对象强制转换为基类对象
- 基类到派生类的转换:
  - 基类对象指针(引用)可以用强制类型转换为派生类对象指针(引用)，而基类对象无法执行这类转换。
  - 向下转型不安全，没有自动转换的机制
- 虚继承与虚基类
  - 当派生类从多个基类派生，而这些基类又从同一个基类派生，则在访问此共同基类中的成员时，将产生二义性---采用虚基类来解决。
  - 虚基类的引入
    - 有共同基类的场合
  - 声明
    - 用virtual关键字修饰说明基类: class B1 : public BB
  - 作用
    - 主要用来解决多继承时可能发生的对同一个基类继承多次而产生的二义性问题。
    - 为最远的派生类提供唯一的基类成员，而不重复产生对此拷贝
- 虚基类及其派生类构造函数
  - 虚基类的成员是由最远派生类的构造函数通过调用虚基类构造函数进行初始化的。
  - 在整个继承结构中，直接或者间接继承虚基类的所有派生类，都必须在构造函数的成员初始化列表中给出对虚基类的构造函数的调用，如果未给出，则表示调用该虚基类的默认构造函数。
  - 在建立对象时，只有最远派生类的构造函数调用虚基类的构造函数，该派生类的其他基类对虚基类构造函数的调用被忽略。

### 作用域

- 块作用域，文件作用域，函数原型作用域:函数声明，函数作用域:goto语句，类作用域

### 前向声明

- c++中类必须先定义，才能够实例化。
- 两个类需要相互引用形成一个环形引用时，无法先定义使用，这时候就需要用到前向声明
- 前向声明的类不能实例化，只能是指针或者引用

### 嵌套类

- 在类的定义内在定义的类

```cpp
class A
{
public:
    class B
    {
        public:
            void function()
            {
                std::cout << "inner function" << std::endl;
            }
    };
};
```

### 局部类

### unix domain

- socket绑定的路径必须是绝对路径
- unix domain 中没有明确的客户端与服务端的概念，因为进程之间的通讯是对等的。在Unix
  Domain中，进程通过socket文件进行通信，一个进程可以作为服务器，另一个进程可以作为客户端，它们之间的角色是动态的，取决于它们之间的通信方式。

### socket中close状态的原因

- 程序建立连接后netstat -nap | grep 20300就会查看到所有的连接关系

```
netstat -nap | grep 20300
tcp        0      0 0.0.0.0:20300           0.0.0.0:*               LISTEN      28193/progam1
tcp        0      0 127.0.0.1:47427         127.0.0.1:20300         CLOSE_WAIT  15099/progam2
tcp        0      0 172.20.65.70:20300      172.20.28.45:12158      ESTABLISHED 28193/progam1
tcp        0      0 172.20.65.70:20300      172.20.28.45:11813      TIME_WAIT   -
tcp        0      0 172.20.65.70:20300      172.20.28.47:51660      TIME_WAIT   -
tcp        0      0 172.20.65.70:20300      172.20.28.47:63161      ESTABLISHED 28193/progam1
```

    - 主动关闭的一方发出FIN包,被动关闭的一方响应ACK包，此时，被动关闭的一方就进入了CLOSE\_WAIT状态。如果一切正常，稍后被动关闭的一方就会发送出FIN包，然后迁移到LAST\_WAIT状态。
    -

### socket中的LT模式和ET模式

- LT(level-triggered)是一种触发方式，它的含义是Socket中有缓冲区中有数据可以读或者可写时，就会触发相应的事件，而不管这些数据是否已经被读取或者写入。
- ET(Edge-Triggered)是在socket缓冲区中有新数据到达时才会触发事件
- linux程序中采用select,epoll方式设置LT模式和ET模式
- 需要注意的是，ET模式需要程序及时处理所有的就绪事件，否则可能会导致事件丢失。而LT模式则不需要考虑这个问题，因为它会一直触发事件，直到数据被读取或写入。因此，在选择LT模式和ET模式时，需要根据具体的应用场景和需求进行选择。
- ET模式（边缘触发模式）适用于需要高效处理大量Socket事件的场景，例如高并发的网络服务器。ET模式的特点是只有在Socket状态发生变化时才会触发事件，因此可以减少事件触发的次数，提高程序的性能。在ET模式下，当Socket状态发生变化时，epoll\_wait函数只会返回一次就绪事件，直到程序读取或写入所有的数据。因此，程序需要及时处理所有的就绪事件，否则可能会导致事件丢失。ET模式的优点是可以提高程序的性能，因为它只在Socket状态发生变化时才会触发事件，减少了事件触发的次数。ET模式适用于需要高效处理大量Socket事件的场景，例如高并发的网络服务器。需要注意的是，在使用ET模式时，程序需要及时处理所有的就绪事件，否则可能会导致事件丢失。因此，在选择LT模式和ET模式时，需要根据具体的应用场景和需求进行选择。
- LT模式的特性如下：稳定性高：由于LT模式会在Socket缓冲区中有数据可读或可写时一直触发事件，因此可以保证程序能够及时处理所有的数据，避免数据丢失或延迟。适用性广：由于LT模式不需要考虑数据是否已经被读取或写入，因此适用于各种不同的Socket应用场景，包括HTTP、FTP、SMTP等。编程简单：由于LT模式只需要在事件触发时进行相应的处理，因此编程比较简单，容易实现和维护。可靠性高：由于LT模式会在Socket缓冲区中有数据可读或可写时一直触发事件，因此可以保证程序能够及时处理所有的数据，避免数据丢失或延迟。总的来说，LT模式是一种稳定性高、适用性广、编程简单、可靠性高的Socket触发方式，适用于各种不同的Socket应用场景。
- select的LT模式

```
fd_set read_fds;
FD_ZERO(&read_fds);
FD_SET(sockfd, &read_fds);
select(sockfd + 1, &read_fds, NULL, NULL, NULL);
```

- select的ET模式

```
int flags = fcntl(sockfd, F_GETFL, 0);
fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
```

- epoll的ET

```cpp
int epoll_fd = epoll_create(1);
struct epoll_event event;
event.data.fd = sockfd;
event.events = EPOLLIN | EPOLLET;
epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event);
//在等待事件触发时，可以使用epoll_wait函数等待事件的触发，并指定超时时间。例如，以下代码等待Socket事件的触发，并处理就绪事件：
struct epoll_event events[MAX_EVENTS];
int n = epoll_wait(epoll_fd, events, MAX_EVENTS, timeout);
for (int i = 0; i < n; i++) {
    if (events[i].events & EPOLLIN) {
        // 处理读事件
    }
    if (events[i].events & EPOLLOUT) {
        // 处理写事件
    }
}
```

- epoll的LT模式:LT模式是epoll的默认触发方式，因此在使用epoll时，如果不指定触发方式，则默认为LT模式。以下代码将Socket文件描述符注册到epoll实例中，并设置LT模式

```
int epoll_fd = epoll_create(1);
struct epoll_event event;
event.events = EPOLLIN;
event.data.fd = sockfd;
epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event);
```

- epoll 使用LT模式的原因
  - poll兼容
  - LT模式不会出现发生漏掉事件的bug，但是POLLOUT事件不能一开始就关注，否则会出现busyloop的现象，而应该在write无法完全写入内核缓冲区的时候才关注，将未写到内核缓冲区的数据添加到应用层output
    buffer直到应用层output buffer写完，停止关注POLLOUT事件。
  - 读写的时候不必等到EAGAIN，可以减少系统调用次数，降低延迟，---边沿触发只通知一次，没有处理好，就会出现事件漏掉的bug，ET模式会多读一次直到读到EAGAIN,至少多读一次(boost
    asio, libevent都是采用LT模式)

### 右值引用

- 右值引用可以减少对象的拷贝次数，可以将临时对象的值，直接移动到目标对象，不需要将对象进行拷贝构造
- A&&是一个右值引用,c++中的右值和左值，左值是一个持久对象，其生命周期超过了当前表达式的范围，右值是一个临时对象，其声明周期仅在当前表达式中。

```
int x = 1;
int y = x + 2;
```

在x和y是左值，因为存在的时间超过了当前的表达式，`x+2`是一个右值，因为它是一个临时的未命名的值。仅在赋值操作期间存在。右值引用类型是扩展c++中的移动语义和完美转发功能，右值引用可以绑定到一个右值(例如临时对象)，并且在我们不创建对象副本的情况下，修改它，这样的好处是提高性能，因为不需要进行额外的复制操作。在函数参数中，A&&可以匹配任意类型的A，无论是左值还是右值，然而，如果传递给它的是左值,那么函数的模版的推导会将A&&视为左值引用，这是一种被称为"引用折叠"的行为，如果A&&作为函数参数，并且它是模版参数，那么可能看到的是所谓的完美转发，这是一种允许函数转发给其参数到其他函数，同时保证原始参数的左值和右值性质。

### std::stringstream类型的数据提取

- 当使用>>运算符从std::stringstream类型的数据中提取std::string类型的数据时，遇到空格、制表符、换行符等空白字符或者遇到字符串结束符\0时，提取操作就会结束。

```
std::stringstream ss("Hello, world!");
std::string str;
std::getline(ss, str);
```

- std::getline()函数会从ss中提取整个字符串"Hello, world!"，并将其存储到str中。
- std::string子函数

```
std::string test = "xml.a.core.system";
auto pos = test.find_first_of('.');
std::string a = test.substr(pos); // .a.core.system
```

# weak\_ptr与shared\_ptr

- weakSelf.lock()是std::weak\_ptr类的成员函数，用于获取一个指向底层对象的std::shared\_ptr,如果std::weak\_ptr对象已经失效，即指向的底层对象已经被释放，那么std::shared\_ptr将为空指针。

# multiset与set

- multiset是支持重复, set会去重，不会排序
- multiset可以看成一个序列，插入删除都是在O(logn)的时间内完成，而且他能时刻保证序列中的数据是有序的，而序列中可以存在重复的数。

# c++的接口调用

- 调用接口的作用主要是解耦，对用户隐藏实现，用户只实现要关心接口的形势，不用关心具体的实现，要保证接口的兼容性，实现上的修改或者升级对用户无感知，解偶后方便多人合作开发，设计好后，各模块通过接口交互。
- 回调接口
- 调用接口
- 虚函数
- 指向实现的指针;实现对用户隐藏，使用指向实现的指针的方式定义接口;Network的实现通过impl指针发给NetworkImpl,
  NetworkImpl使用前置声明，实现对用户隐藏，使用指向实现的指针的方式定义接口，接口类对象的创建和销毁可以由用户负责，因此用户可以选择将Network类的对象创建在栈上，生病周期自动管理。使用指向实现的指针定义接口具有良好的通用性，用户能够直接创建和销毁对象，增加新的接口函数不影响二进制兼容，便于系统的演进。指向实现的指针增加了一层调用，尽管对性能的影响几乎可以忽略不计，但不太符合C++的零开销原则

```
class NetworkImpl;
class Network;
{
public:
    bool send(const char* host,
            uint16_t port,
            const std::string& message);
    Network();
    ~Network();
private:
    NetworkImpl* impl;
};
```

- 隐藏的子类
- 回调接口
- 虚函数
- 函数指针
- 类成员函数指针

# 类型擦除

- 对于地方库实现是c语言的类型封装，比如speak函数，把speak封装成多态的虚函数，可以如下实现:

```
// 类型擦除
struct Cat
{
	void speak() const
	{
		printf("Meow~~~~\n");
	}
};
struct Dog
{
	void speak() const
	{
		printf("Woah~~~~\n");
	}
};
struct Animal 
{
	virtual void speak() const = 0;
	virtual ~Animal() = default;
};

template<class Inner>
struct AnimalWrapper : Animal
{
	Inner m_inner;

	virtual void speak() const override
	{
		return m_inner.speak();
	}
};
```

这里我们的animal擦除了speak这个成员函数,而std::any实际上擦除了拷贝构造函数和解构函数，std::function则是擦除了operator()函数;

- 实际上std::any也是一种类型擦除的容器

- 静态初始化用于批量注册函数

```
#include <map>

std::map<std::string, std::function<void()>> funcitontab;
static void catFunc()
{
	printf("Meow ~~~\n");
}
static int defCat = (functab.emplace("cat", catFunc), 0);

static void dogFunc()
{
	printf("Meow ~~~\n");
}
static int defDog = (functab.emplace("dog", dogFunc), 0);
int main()
{
	functab.at("cat")();
	functab.at("dog")();
	return 0;
}
```

# 编译问题

- Linux链接静态库到动态库出错(编译静态库需要开启
  -fPIC选项，如果是cmake则是在最前面添加`set(CMAKE_POSITION_INDEPENDENT_CODE ON))`即可，建议linux全部用动态库，windows全部用静态库

- 使用`set(CMAKE_CXX_STANDARD 17)`代替`set(CMAKE_CXX_FLAGS "-std=c++17")`(有概率被覆盖而且不跨平台);
  `set(CMAKE_CXX_FLAGS "-O3")`
  (可能会被覆盖，并且不跨平台),`set(CMAKE_BUILD_TYPE Release)`是标准做法，Release开优化，Debug关优化，如果让Release从默认的-O3变成-O2应该`set(CMAKE_CXX_FLAGS_RELEASE "-O2")`同理还有`CMAKE_CXX_FLAGS_DEUBUG`可以设置;我想要链接
  pthread，有没有现代 CMake 跨平台的写法？（用 `find_package(Threads REQUIRED)` 和
  `target_link_libraries(你的目标程序名 Threads::Threads)` 即可，Linux 上等同于 pthread，在 Wendous 上会变成 Wendous
  的线程库）

# 包含头部信息的流协议

```
+----------+--------------+-------+
| 0x0F     | Length       | JSON  |
+----------+--------------+-------+
采用[魔幻数+长度]的形式进行数据包界定
```

# 单进程中的类模块之间的通讯: 观察者模式 信号槽

- 单进程里不同业务模块之间的交互，控制, 比如: 手机设置了夜晚模式，所有的app都会知道系统设置了夜晚模式, 进而都调整app自己UI和亮度等。

- nod.hpp 是一个C++库，他提供了一种简单. 灵活和高效的信号机制。是一种事件驱动编程模式，它允许在特定事件发生时触发一组操作。

- 信号槽: 是c++中用于实现对象间的一种机制，它类似于事件驱动编程中的事件和事件处理函数，可以用于在对象之间传递信号和消息。
  - 定义信号和槽: 信号是一个可以被发送的信号标识符，槽函数是一个可以被调用的函数。在信号槽机制中，信号和槽函数之间通过建立连接操作来建立对应关系。
  - Q&A: How does nod differ from other signals&slots libraries
  ```
  Since the scope of the signal & slots construct is pretty narrow, you will find most of the differences are syntactical in nature.

  The nod library is primarily designed to be easy to use, have a modern C++ feel to it, and above all be lightweight and only be dependent on the standard template library. Performance is not the primary focus of the nod library. Many libraries out there sacrifice "syntactical sugar" for performance. Nod was developed as an alternative to using boost.signal2 in my own projects, just to avoid the massive dependency that using boost libraries can incur.

  Compared specifically to nano there are a few points that are different, besides slightly different ways of doing things like connection management and retrieving slot return values.

  Nod guarantees that slots are called in connection order.
  Nod aims to provide thread safe signals by default, but also provide the possibility of single threaded only signals if needed.
  ```

```cpp
#ifndef IG_NOD_INCLUDE_NOD_HPP
#define IG_NOD_INCLUDE_NOD_HPP
#include <vector>        // std::vector
#include <functional>    // std::function
#include <mutex>         // std::mutex, std::lock_guard
#include <memory>        // std::shared_ptr, std::weak_ptr
#include <algorithm>     // std::find_if()
#include <cassert>       // assert()
#include <thread>        // std::this_thread::yield()
#include <type_traits>   // std::is_same
#include <iterator>      // std::back_inserter

namespace nod{
    /// implemetentational details
    /// 实现细节
    namespace detail {
        /// interface for type erasure when disconnection slots
        /// 断开插槽连接时用于类型擦除的接口
        struct disconnect {
            virtual void operator()(std::size_t index) const = 0;
        };

        /// Deleter that doesn't delete
        /// 不删除的删除程序
        inline void no_delete(disconnector*){
        }
    } // namespace detail

    /// Base template for the signal class
    /// 信号类的模板基类
    template <class P, class T>
    class signal_type;

    /// Connection class.
    ///
    /// This is used to be able to disconnect slots after they have been connected.
    /// Used as return type for the connect method of the signals.
    ///
    /// Connections are default constructible.
    /// Connections are not copy constructible or copy assignable.
    /// Connections are move constructible and move assignable.
    ///
    ///连接类。
    ///
    ///这用于在插槽连接后断开它们的连接。
    ///用作信号的连接方法的返回类型。
    ///
    ///连接是默认可构造的。
    ///连接不可复制构造或可复制分配。
    ///连接可移动构造，也可移动指定。
    ///
    class connection {
        public:
            connection():
                _index() {}
            /// Connection are not copy constructible or copy assignable
            /// 拷贝构造 赋值构造
            connection( connection const& ) = delete;
            connection& operator=( connection const& ) = delete;
            /// Move constructor
            /// @param other   The instance to move from.
            /// 移动构造
            connection(connection&& other):
                _weak_disconnector(std::move(other._weak_disconnector)),
                _index(other._index)
            {}
            /// 移动赋值操作符
            /// Move assign operator.
            /// @param other   The instance to move from.
            connection& operator=( connection&& other ) {
                _weak_disconnector = std::move( other._weak_disconnector );
                _index = other._index;
                return *this;
            }

            /// @returns `true` if the connection is connected to a signal object,
            ///          and `false` otherwise.
            bool connected() const {
                return !_weak_disconnector.expired();
            }

            /// Disconnect the slot from the connection.
            ///
            /// If the connection represents a slot that is connected to a signal object, calling
            /// this method will disconnect the slot from that object. The result of this operation
            /// is that the slot will stop receiving calls when the signal is invoked.
            // 如果连接表示连接到信号对象的插槽，则调用此方法将断开插槽与该对象的连接。此操作的结果是，当调用信号时，插槽将停止接收调用。
            void disconnect();

        private:
            /// The signal template is a friend of the connection, since it is the
            /// only one allowed to create instances using the meaningful constructor
            /// 信号模板是连接类的友元类，因为它是只有一个允许使用有意义的构造函数创建实例。
            template<class P,class T> friend class signal_type;
            
            /// Create a connection.
            /// @param shared_disconnector Disconnector instance that will be used to disconnect
            ///                            the connection when the time comes. A weak pointer
            ///                            to the disconnector will be held within the connection
            ///                            object.
            /// @param index               The slot index of the connection.
            ///创建连接。
            ///@param shared_disconnector 该实例将在时间到来时用于断开连接。指向隔离开关的弱指针将保持在连接对象内。
            ///@param index连接的插槽索引。
            connection(std::shared_ptr<detail::disconnector> const& shared_disconnector, std::size_t index) :
                _ weak_disconnector( shared_disconnector ),
                _index( index )
        {}

            /// Weak pointer to the current disconnector functor.
            /// 指向当前断开连接函数的弱指针
            std::weak_ptr<detail::disconnector> _weak_disconnector;
            /// Slot index of the connected slot.
            ///已连接插槽的插槽索引。
            std::size_t _index;
    };
    /// Scoped connection class.
    ///
    /// This type of connection is automatically disconnected when the connection object is destructed.
    /// 作用域连接类。当连接对象被破坏时，这种类型的连接会自动断开。
    class scoped_connection
    {
    public:
        /// Scoped are default constructible
        scoped_connection() = default;
        /// Scoped connections are not copy constructible
        scoped_connection( scoped_connection const& ) = delete;
        /// Scoped connections are not copy assingable
        scoped_connection& operator=( scoped_connection const& ) = delete;

        /// Move constructor
        scoped_connection( scoped_connection&& other ) :
            _connection( std::move(other._connection) )
        {}

		/// Move assign operator.
		/// @param other   The instance to move from.
		scoped_connection& operator=( scoped_connection&& other ) {
			reset( std::move( other._connection ) );
			return *this;
		}

		/// Construct a scoped connection from a connection object
		/// @param connection   The connection object to manage
		scoped_connection( connection&& c ) :
			_connection( std::forward<connection>(c) )
		{}

		/// destructor
		~scoped_connection() {
			disconnect();
		}

		/// Assignment operator moving a new connection into the instance.
		/// @note If the scoped_connection instance already contains a
		///       connection, that connection will be disconnected as if
		///       the scoped_connection was destroyed.
		/// @param c   New connection to manage
		scoped_connection& operator=( connection&& c ) {
			reset( std::forward<connection>(c) );
			return *this;
		}

		/// Reset the underlying connection to another connection.
		/// @note The connection currently managed by the scoped_connection
		///       instance will be disconnected when resetting.
		/// @param c   New connection to manage
		void reset( connection&& c = {} ) {
			disconnect();
			_connection = std::move(c);
		}

		/// Release the underlying connection, without disconnecting it.
		/// @returns The newly released connection instance is returned.
		connection release() {
			connection c = std::move(_connection);
			_connection = connection{};
			return c;
		}

		///
		/// @returns `true` if the connection is connected to a signal object,
		///          and `false` otherwise.
		bool connected() const {
			return _connection.connected();
		}

		/// Disconnect the slot from the connection.
		///
		/// If the connection represents a slot that is connected to a signal object, calling
		/// this method will disconnect the slot from that object. The result of this operation
		/// is that the slot will stop receiving calls when the signal is invoked.
		void disconnect() {
			_connection.disconnect();
		}

	private:
		/// Underlying connection object
		connection _connection;
	};


    };

   	/// Signal accumulator class template.
	///
	/// This acts sort of as a proxy for triggering a signal and
	/// accumulating the slot return values.
	///
	/// This class is not really intended to instantiate by client code.
	/// Instances are aquired as return values of the method `accumulate()`
	/// called on signals.
	///
	/// @tparam S      Type of signal. The signal_accumulator acts
	///                as a type of proxy for a signal instance of
	///                this type.
	/// @tparam T      Type of initial value of the accumulate algorithm.
	///                This type must meet the requirements of `CopyAssignable`
	///                and `CopyConstructible`
	/// @tparam F      Type of accumulation function.
	/// @tparam A...   Argument types of the underlying signal type.
	/// 信号累加器类模板
	/// 这在某种程度上充当了触发信号和累积时隙返回值的代理。
	/// 这个类实际上并不是用来由客户端代码实例化的。实例被获取为对信号调用的方法“accumulate（）”的返回值。
	/// @tparam S信号类型。signal_accumulator充当此类型的信号实例的代理类型;
	/// @tparam T累加算法的初始值类型。此类型必须满足“CopyAssignable”的要求，并且`CopyConstructable`
	/// @tparam F累加函数的类型；
	/// @tparam A…基本信号类型的参数类型。
	template <class S, class T, class F, class...A>
	class signal_accumulator
	{
		public:
			/// Result type when calling the accumulating function operator.
			#if (__cplusplus > 201703L)
			using result_type = typename std::invoke_result<F, T, typename S::slot_type::result_type>::type;
			#else
			using result_type = typename std::result_of<F(T, typename S::slot_type::result_type)>::type;
			#endif

			/// Construct a signal_accumulator as a proxy to a given signal
			//
			/// @param signal   Signal instance.
			/// @param init     Initial value of the accumulate algorithm.
			/// @param func     Binary operation function object that will be
			///                 applied to all slot return values.
			///                 The signature of the function should be
			///                 equivalent of the following:
			///                   `R func( T1 const& a, T2 const& b )`
			///                  - The signature does not need to have `const&`.
			///                  - The initial value, type `T`, must be implicitly
			///                    convertible to `R`
			///                  - The return type `R` must be implicitly convertible
			///                    to type `T1`.
			///                  - The type `R` must be `CopyAssignable`.
			///                  - The type `S::slot_type::result_type` (return type of
			///                    the signals slots) must be implicitly convertible to
			///                    type `T2`.
			signal_accumulator( S const& signal, T init, F func ) :
				_signal( signal ),
				_init( init ),
				_func( func )
			{}

			/// Function call operator.
			///
			/// Calling this will trigger the underlying signal and accumulate
			/// all of the connected slots return values with the current
			/// initial value and accumulator function.
			///
			/// When called, this will invoke the accumulator function will
			/// be called for each return value of the slots. The semantics
			/// are similar to the `std::accumulate` algorithm.
			///
			/// @param args   Arguments to propagate to the slots of the
			///               underlying when triggering the signal.
			result_type operator()( A const& ... args ) const {
				return _signal.trigger_with_accumulator( _init, _func, args... );
			}

		private:

			/// Reference to the underlying signal to proxy.
			S const& _signal;
			/// Initial value of the accumulate algorithm.
			T _init;
			/// Accumulator function.
			F _func;

	};

    /// Signal template specialization.
    ///
    /// This is the main signal implementation, and it is used to
    /// implement the observer pattern whithout the overhead
    /// boilerplate code that typically comes with it.
    ///
    /// Any function or function object is considered a slot, and
    /// can be connected to a signal instance, as long as the signature
    /// of the slot matches the signature of the signal.
    ///
    /// @tparam P      Threading policy for the signal.
    ///                A threading policy must provide two type definitions:
    ///                 - P::mutex_type, this type will be used as a mutex
    ///                   in the signal_type class template.
    ///                 - P::mutex_lock_type, this type must implement a
    ///                   constructor that takes a P::mutex_type as a parameter,
    ///                   and it must have the semantics of a scoped mutex lock
    ///                   like std::lock_guard, i.e. locking in the constructor
    ///                   and unlocking in the destructor.
    ///
    /// @tparam R      Return value type of the slots connected to the signal.
    /// @tparam A...   Argument types of the slots connected to the signal.
    /// 信号模板专业化
    /// 这是主要的信号实现，它用于实现观测器模式，而不需要通常附带的开销样板代码。
    /// 任何函数或函数对象都被视为槽，并且可以连接到信号实例，只要槽的签名与信号的签名匹配即可。
    /// tparam P信号的线程策略。线程策略必须提供两种类型定义：
    /// -P：：mutex _type，此类型将用作signal_type类模板中的互斥对象。
    /// -P:：mute_lock_type，此类型必须实现一个以P:：mutex _type为参数的构造函数，并且它必须具有类似std:：lock_guard的作用域互斥锁的语义，即在构造函数中锁定，在析构函数中解锁。
    ///@tparam R返回连接到信号的插槽的值类型。
    ///@tparam A…连接到信号的插槽的参数类型。
    /// R(A...)(表示的是传入的回调函数，R表示回调函数的返回类型，A...表示变参;比如:signal_type<P, void(Args ..)>)
	template <class P, class R, class... A >
	class signal_type<P,R(A...)>
	{
		public:
			/// signals are not copy constructible
			signal_type( signal_type const& ) = delete;
			/// signals are not copy assignable
			signal_type& operator=( signal_type const& ) = delete;
			/// signals are move constructible
			signal_type(signal_type&& other)
			{
				mutex_lock_type lock{other._mutex};
				_slot_count = std::move(other._slot_count);
				_slots = std::move(other._slots);
				if(other._shared_disconnector != nullptr)
				{
					_disconnector = disconnector{ this };
					_shared_disconnector = std::move(other._shared_disconnector);
					// replace the disconnector with our own disconnector
					*static_cast<disconnector*>(_shared_disconnector.get()) = _disconnector;
				}
			}
			/// signals are move assignable
			signal_type& operator=(signal_type&& other)
			{
				auto lock = thread_policy::defer_lock(_mutex);
				auto other_lock = thread_policy::defer_lock(other._mutex);
				thread_policy::lock(lock,other_lock);

				_slot_count = std::move(other._slot_count);
				_slots = std::move(other._slots);
				if(other._shared_disconnector != nullptr)
				{
					_disconnector = disconnector{ this };
					_shared_disconnector = std::move(other._shared_disconnector);
					// replace the disconnector with our own disconnector
					*static_cast<disconnector*>(_shared_disconnector.get()) = _disconnector;
				}
				return *this;
			}
            /// signals are default constructible
            signal_type() :
                _slot_count(0)
            {}

            // Destruct the signal object.
            ~signal_type() {
                invalidate_disconnector();
            }

            /// Type that will be used to store the slots for this signal type.
            using slot_type = std::function<R(A...)>;
            /// Type that is used for counting the slots connected to this signal.
            using size_type = typename std::vector<slot_type>::size_type;
				/// Connect a new slot to the signal.
			///
			/// The connected slot will be called every time the signal
			/// is triggered.
			/// @param slot   The slot to connect. This must be a callable with
			///               the same signature as the signal itself.
			/// @return       A connection object is returned, and can be used to
			///               disconnect the slot.
			template <class T>
			connection connect( T&& slot ) {
				mutex_lock_type lock{ _mutex };
				_slots.push_back( std::forward<T>(slot) );
				std::size_t index = _slots.size()-1;
				if( _shared_disconnector == nullptr ) {
					_disconnector = disconnector{ this };
					_shared_disconnector = std::shared_ptr<detail::disconnector>{&_disconnector, detail::no_delete};
				}
				++_slot_count;
				return connection{ _shared_disconnector, index };
			}

			/// Function call operator.
			///
			/// Calling this is how the signal is triggered and the
			/// connected slots are called.
			///
			/// @note The slots will be called in the order they were
			///       connected to the signal.
			///
			/// @param args   Arguments that will be propagated to the
			///               connected slots when they are called.
			void operator()( A const&... args ) const {
				for( auto const& slot : copy_slots() ) {
					if( slot ) {
						slot( args... );
					}
				}
			}

			/// Construct a accumulator proxy object for the signal.
			///
			/// The intended purpose of this function is to create a function
			/// object that can be used to trigger the signal and accumulate
			/// all the slot return values.
			///
			/// The algorithm used to accumulate slot return values is similar
			/// to `std::accumulate`. A given binary function is called for
			/// each return value with the parameters consisting of the
			/// return value of the accumulator function applied to the
			/// previous slots return value, and the current slots return value.
			/// A initial value must be provided for the first slot return type.
			///
			/// @note This can only be used on signals that have slots with
			///       non-void return types, since we can't accumulate void
			///       values.
			///
			/// @tparam T      The type of the initial value given to the accumulator.
			/// @tparam F      The accumulator function type.
			/// @param init    Initial value given to the accumulator.
			/// @param op      Binary operator function object to apply by the accumulator.
			///                The signature of the function should be
			///                equivalent of the following:
			///                  `R func( T1 const& a, T2 const& b )`
			///                 - The signature does not need to have `const&`.
			///                 - The initial value, type `T`, must be implicitly
			///                   convertible to `R`
			///                 - The return type `R` must be implicitly convertible
			///                   to type `T1`.
			///                 - The type `R` must be `CopyAssignable`.
			///                 - The type `S::slot_type::result_type` (return type of
			///                   the signals slots) must be implicitly convertible to
			///                   type `T2`.
			template <class T, class F>
			signal_accumulator<signal_type, T, F, A...> accumulate( T init, F op ) const {
				static_assert( std::is_same<R,void>::value == false, "Unable to accumulate slot return values with 'void' as return type." );
				return { *this, init, op };
			}


			/// Trigger the signal, calling the slots and aggregate all
			/// the slot return values into a container.
			///
			/// @tparam C     The type of container. This type must be
			///               `DefaultConstructible`, and usable with
			///               `std::back_insert_iterator`. Additionally it
			///               must be either copyable or moveable.
			/// @param args   The arguments to propagate to the slots.
			template <class C>
			C aggregate( A const&... args ) const {
				static_assert( std::is_same<R,void>::value == false, "Unable to aggregate slot return values with 'void' as return type." );
				C container;
				auto iterator = std::back_inserter( container );
				for( auto const& slot : copy_slots() ) {
					if( slot ) {
						(*iterator) = slot( args... );
					}
				}
				return container;
			}

			/// Count the number of slots connected to this signal
			/// @returns   The number of connected slots
			size_type slot_count() const {
				return _slot_count;
			}

			/// Determine if the signal is empty, i.e. no slots are connected
			/// to it.
			/// @returns   `true` is returned if the signal has no connected
			///            slots, and `false` otherwise.
			bool empty() const {
				return slot_count() == 0;
			}

			/// Disconnects all slots
			/// @note This operation invalidates all scoped_connection objects
			void disconnect_all_slots() {
				mutex_lock_type lock{ _mutex };
				_slots.clear();
				_slot_count = 0;
				invalidate_disconnector();
			}
		private:
			template<class, class, class, class...> friend class signal_accumulator;
			/// Thread policy currently in use
			using thread_policy = P;
			/// Type of mutex, provided by threading policy
			using mutex_type = typename thread_policy::mutex_type;
			/// Type of mutex lock, provided by threading policy
			using mutex_lock_type = typename thread_policy::mutex_lock_type;

			/// Invalidate the internal disconnector object in a way
			/// that is safe according to the current thread policy.
			///
			/// This will effectively make all current connection objects to
			/// to this signal incapable of disconnecting, since they keep a
			/// weak pointer to the shared disconnector object.
			void invalidate_disconnector() {
				// If we are unlucky, some of the connected slots
				// might be in the process of disconnecting from other threads.
				// If this happens, we are risking to destruct the disconnector
				// object managed by our shared pointer before they are done
				// disconnecting. This would be bad. To solve this problem, we
				// discard the shared pointer (that is pointing to the disconnector
				// object within our own instance), but keep a weak pointer to that
				// instance. We then stall the destruction until all other weak
				// pointers have released their "lock" (indicated by the fact that
				// we will get a nullptr when locking our weak pointer).
				std::weak_ptr<detail::disconnector> weak{_shared_disconnector};
				_shared_disconnector.reset();
				while( weak.lock() != nullptr )	{
					// we just yield here, allowing the OS to reschedule. We do
					// this until all threads has released the disconnector object.
					thread_policy::yield_thread();
				}
			}

			/// Retrieve a copy of the current slots
			///
			/// It's useful and necessary to copy the slots so we don't need
			/// to hold the lock while calling the slots. If we hold the lock
			/// we prevent the called slots from modifying the slots vector.
			/// This simple "double buffering" will allow slots to disconnect
			/// themself or other slots and connect new slots.
			/// 检索当前插槽的副本
			/// 复制插槽是有用和必要的，这样我们在调用插槽时就不需要持有锁。如果我们保持锁定，我们将阻止被调用的槽修改槽向量。这种简单的“双重缓冲”将允许插槽断开自身或其他插槽的连接，并连接新的插槽。
			std::vector<slot_type> copy_slots() const
			{
				mutex_lock_type lock{ _mutex };
				return _slots;
			}

			/// Implementation of the signal accumulator function call
            /// 信号累加器函数调用的实现
			template <class T, class F>
			typename signal_accumulator<signal_type, T, F, A...>::result_type trigger_with_accumulator( T value, F& func, A const&... args ) const {
				for( auto const& slot : copy_slots() ) {
					if( slot ) {
						value = func( value, slot( args... ) );
					}
				}
				return value;
			}

			/// Implementation of the disconnection operation.
			///
			/// This is private, and only called by the connection
			/// objects created when connecting slots to this signal.
			/// @param index   The slot index of the slot that should
			///                be disconnected.
			void disconnect( std::size_t index ) {
				mutex_lock_type lock( _mutex );
				assert( _slots.size() > index );
				if( _slots[ index ] != nullptr ) {
					--_slot_count;
				}
				_slots[ index ] = slot_type{};
				while( _slots.size()>0 && !_slots.back() ) {
					_slots.pop_back();
				}
			}

			/// Implementation of the shared disconnection state
			/// used by all connection created by signal instances.
			///
			/// This inherits the @ref detail::disconnector interface
			/// for type erasure.
            ///信号实例创建的所有连接使用的共享断开状态的实现。
            ///这继承了用于类型擦除的@ref detail:：隔离开关接口。
			struct disconnector :
				detail::disconnector
			{
				/// Default constructor, resulting in a no-op disconnector.
				disconnector() :
					_ptr(nullptr)
				{}

				/// Create a disconnector that works with a given signal instance.
				/// @param ptr   Pointer to the signal instance that the disconnector
				///              should work with.
				disconnector( signal_type<P,R(A...)>* ptr ) :
					_ptr( ptr )
				{}

				/// Disconnect a given slot on the current signal instance.
				/// @note If the instance is default constructed, or created
				///       with `nullptr` as signal pointer this operation will
				///       effectively be a no-op.
				/// @param index   The index of the slot to disconnect.
				void operator()( std::size_t index ) const override {
					if( _ptr ) {
						_ptr->disconnect( index );
					}
				}

				/// Pointer to the current signal.
				signal_type<P,R(A...)>* _ptr;
			};

			/// Mutex to synchronize access to the slot vector   互斥锁 用于同步slot vector
			mutable mutex_type _mutex;
			/// Vector of all connected slots     所有的slots
			std::vector<slot_type> _slots;
			/// Number of connected slots        slots的数量
			size_type _slot_count;
			/// Disconnector operation, used for executing disconnection in a
			/// type erased manner.
            /// 隔离开关操作，用于以类型擦除的方式执行隔离。
			disconnector _disconnector;
			/// Shared pointer to the disconnector. All connection objects has a
			/// weak pointer to this pointer for performing disconnections.
            /// 隔离开关的共享指针。所有连接对象都有一个指向该指针的弱指针，用于执行断开连接。
			std::shared_ptr<detail::disconnector> _shared_disconnector;
	};

		inline void connection::disconnect(){
			auto ptr = _weak_disconnector.lock();
			if (ptr) {
				(*ptr)( _index;);
			}
			_weak_disconnector.reset();
		}

		template <class T> using signal = signal_type<multithread_policy, T>;
	}// namespace nod
```

用vector去存储slots槽函数，然后通过signal的时候去遍历这个vector，触发事件

# C++与C

- 函数和类:
  在C语言中，我们通过函数来封装和复用代码，函数可以接受参数，执行特定任务，并返回值，然而复用是有限的，因为函数不能封装状态(不能拥有字段和属性)，相比之下，C++的类不仅可以封装函数，还可以封装状态，这为更高级的复用提供了可能。c语言没有字段和属性，是因为C语言是一种面向过程的语言，而不是面向对象的编程语言，在C语言中，数据通常是通过变量来表示，而函数来操作这些变量，数据和函数是分开的，不能紧密联系
- 代码复用

# JSON-C

```
json_object_new_object():创建一个新的JSON对象.该函数会分配内存来存储JSON对象的结构和相关数据;
json_object_new_array(): 创建一个新的JSON数组对象,该函数会分配一个JSON数据对象
json_object_new_string()
json_object_new_int()
json_object_new_double()
json_object_new_boolean()
json_object_new_null()
统一采用json_object_put()函数来释放分配的内存;
```
