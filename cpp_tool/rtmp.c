//=====================================================================
//
// rtmp.c - 
//
// Created by wwq on 2022/08/11
// Last Modified: 2022/08/11 13:42:39
//
//=====================================================================
/**
 *AMF(Action Message Format)是一中类似于JSON,XML的二进制数据序列化格式，Adobe Flash与远程服务端可以通过AMF格式的数据进行数据通信
 AMF的格式其实与map的数据结构相似，就是在KV键值对的基础上，中间多加了一个Value值得lengh.AMF得结果借本如图，len字段有时候是空的，
 这个是由type来决定的。length字段是表示的AMFvalue的字节数，不是表示的AMF整个占用的字节数，len的字段长度，不确定，由type来决定，
 也有可能len和value都没有。
 +----------------+-------------+---------------+
 | type(一个字节) |   len       +   value       |
 +----------------+-------------+---------------+
 AMF的type的对应表格
 +---------+----------+
 | 0x00    | number   |
 +---------+----------+
 | 0x01    | boolean  |
 +---------+----------+
 | 0x02    | string   |
 +---------+----------+
 | 0x03    | object   |
 +---------+----------+
 | 0x04    | null     |
 +---------+----------+
 | 0x05    | date     |
 +---------+----------+
 | 0x06    |object-end|
 +---------+----------+
 可以通过wrireshak来抓包查看具体的AMF0的格式。AMF目前主要是有两个版本，分别是AMF0和AMF3,目前主流是AMF0;
 实际上RTMP在Chunk Header中使用message type id来进行区分，当消息使用AMF0编码时，message type id等于20，使用AMF3编码时message type id等于17。
 * **/
