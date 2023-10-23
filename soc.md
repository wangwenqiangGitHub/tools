# MPU-S32G

## [MPU与MCU的区别](https://blog.csdn.net/usstmiracle/article/details/119949171)

MPU的全称叫Micro Processor Unit，MCU的全称是Mirco Controller
Unit。首先这两个词都有一个Micro开头，其实这就表明了这是计算/控制单元小型化后出现的技术。事实上，这是由于集成电路进步带来的计算机系统集成程度提高的结果。使得原来有多片分立的元件组成的计算机系统向高度集成化发展，多个芯片/元件的功能在向一颗芯片集中。这是一个大的技术演进的背景。

- MCU指的是微控制器,集合了FLASH，RAM和 一些外围器件。MCU一般使用片内FLASH来存储和执行程序代码
- MPU指的是微处理器,FLASH和ARM则需要设计者自行搭建，当然MCU也可以外扩。
- MPU的电路设计相对于MCU较为复杂。MPU将代码存储在外部FLASH中，上电后将代码搬运至RAM中运行。

## [S32V234 Linux yocto 开发环境搭建](https://blog.csdn.net/usstmiracle/article/details/125300515)

- SOME/IP Scalable service-Oriented MiddlewarE over IP 基于IP的面向服务的可扩展中间件

## [NXP Community](https://community.nxp.com)

## SPI总线

- SPI全称Serial Peripheral interface 是一种串行通讯协议,支持点对点和对点通信. SPI总线采用四根线: SCLK(时钟), MOSI(主机输出从机输入),
  MISO(主机输入从机输出)和SS(从机选择);SPI总线优点是传输速度快(最高达到几十MBps),实时性强，芯片间干扰小，硬件接口简单。

## I2C总线

- 双向半双工串行通信接口。两个线:SCK(时钟)和SDA(数据).其中SDA既充当数据输入端，又充当数据输出端，传输速度慢，数据容量小，能够方便地实现芯片间通信，节省硬件接口资源。
