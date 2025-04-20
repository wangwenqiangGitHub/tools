# 一个c++类之间相互引用的例子

- 假设一个银行系统，为客户建立了一个People类，为各种银行卡建立了Card类，People类里记录着开发信息(用Card类描述),Car类里也需要说明拥有者信息(用People类描述)


# 思路

- 内存管理
    - 使用`shared_ptr`管理对象所有权
    - 使用`weak_ptr`打破循环引用
    - 通过lock()安全访问`weak_ptr`

- 文件组织
    - 前向声明解决头文件循环依赖
    - 实现细节放在.cpp文件中

- 生命周期
    - 即使People对象被销毁, `weak_ptr`会自动失效, 通过lock()检查对象有效性

- 为什么Card会使用`weak_ptr`指向People:
问题 如果`Card`使用`shared_ptr`指向`People`,同时`People`用`shared_ptr`指向Card,会形成循环引用，相互强引用时，引用计数永远不会归零，导致内存泄露，`weak_ptr`不会增加引用计数，因此不会阻止People对象的销毁。
