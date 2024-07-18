# sqlite3

#### 编译

- 将sqlite3交叉编译，在arm板上直接使用sqlite3命令查看数据库

```
q-extract sqlite-autoconf-3460000.tar.gz
./configure CC=arm-buildroot-linux-gnueabi-gcc --host=arm-linux --prefix=`pwd`/OUT
make -j12 && make install
```

#### 基本命令[参考](https://blog.csdn.net/qq_36091214/article/details/131758305)

- 系统以`.`开头的命令

```
.help 帮助手册
.exit  退出
.table  查看当前数据库的有的表格名
.databases 
.schema  查看表的结构属性
.headers on 显示表格的头
```

- sql语句 以 ';'结尾

1. 创建表格

```
create table <table-name> (id integer, age integer, name char, score float);
```

2. 插入数据

```
insert into <table-name> values(1001, 15, zhangsan, 89);// 标准插入
insert into <table-name> values (id, age, name) values(1002, 18, lisi);//按列名插入
```

3. 查看数据库记录

```
select * from <table-name>; //查看全部
select * from <table-name> were age = 15;//按列名的信息 age=15 的查看
select * from <table-name> were age = 15 and name = lisi;//按多个列名的信息查看
select * from <table-name> were age = 15 or name = lisi;//age = 15 或 name = lisi满足一个条件就输出
select name, id from <table-name>;//指定字段查询
select * from <table-name> where score >= 90 and score <= 100;//查询score[90,100] 之间的信息
```

4. 删除信息

```
delete from <table-name> where id = 1005 and name = 'zhangsan';//删除id=1005和name=‘张三’的信息（同时满足）
delete from <table-name> where id = 1005 or name = 'zhangsan';//删除id=1005或name=‘张三’的信息（有一个条件满足就执行）
```

5. 更新信息

```
update <table-name> set name = 'wangwu' where id = 1002;//将id是1002的行信息中的name全部改成 'wangwu'；
```

6. 增加一列

```
alter table <table-name> add column score float;//在<table-name>表名后面添加一列名: score属性为：float
```

7. 删除一列（sqlite3 不支持直接删除一列）

```
1-- 创建一张新表
	create table <new-table-name> as select id, name, score from <table-name>;//从<table-name>表名中选择指定的列（id，name，score）为基础创建<new-table-name>新的表
2-- 删除原有的表
	drop table <table-name>;
3-- 将新表的名字改成原有的旧表的名字
	alter table <new-table-name> rename to <table-name>;//将<table-name>新表明改成<table-name>旧表明
```
