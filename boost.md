# boost 相关API

### 多索引容器:`boost::multi_index::multi_index_container`

- 需要typedef来为新的容器提供对`Boost multi_index::multi_index_container`中类的方便的访问，优势在于对同一组同样的数据提供了多组访问接口。

- 每个容器定义都需要类`boost::multi_index::multi_index_container` 第一个参数是容器中存储的元素类型，在例子中为person,
  在第二个参数指明了容器所提供的所有索引类型。访问接口的具体细节都可以在定义容器的时候被指定。接口的定义必须由模板类`boost::multi_index::indexed_by`开实现，每个接口都作为参数传动给它。

```cpp
/*
例子中定义了两个 boost::multi_index::hashed_non_unique 类型的接口，
boost::multi_index::hashed_non_unique 是一个模板类， 他需要一个可计算 Hash 值的类型作为它的参数。 
因为接口需要访问 person 中的 name 和 age， 所以 name 和 age 都要是可计算 Hash 值的。
辅助模板类 boost::multi_index::member 来访问类中的属性。
指定了好几个参数来让 boost::multi_index::member 明白可以访问 person 中的哪些属性以及这些属性的类型。

person_multi可以分别通过其中的两个属性 name 和 age 来查询容器。
*/
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
 
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/shared_ptr.hpp>
 
 
using namespace std;
 
//定义学生信息，同理可以使用结构定义
class student {
public:
	student(int id, string name, int score, string remark) :id(id), name(name), score(score), remark(remark) {
	}
 
	void print() const {
		cout << "id:" << id << " name:" << name << " score:" << score << endl;
	}
	int id;
	string name;
	int score;
	string remark;
};
 
// 如果要把student某个属性字段设置为搜索引擎，则需要定义用于排序的空结构体对象
struct _id {};
struct _name{};
struct _score {};
 
// 定义一个multi_index_container（多索引容器）
using student_table =
boost::multi_index::multi_index_container<
	student,
	boost::multi_index::indexed_by<
		boost::multi_index::ordered_unique<boost::multi_index::tag<_id>, BOOST_MULTI_INDEX_MEMBER(student, int, id)>,   // ID为唯一索引，类似主键
		boost::multi_index::ordered_non_unique<boost::multi_index::tag<_name>, BOOST_MULTI_INDEX_MEMBER(student, string, name)>, // 非唯一索引
		boost::multi_index::ordered_non_unique<boost::multi_index::tag<_score>, BOOST_MULTI_INDEX_MEMBER(student, int, score)>
	>
>;
 
int main() {
	// initialize data.
	student_table allStu;
	allStu.insert(student(1, "lili", 85, "hello"));
	allStu.insert(student(2, "liming", 90, "hello"));
	allStu.insert(student(3, "xiaoming", 65, "hello"));
	allStu.insert(student(4, "ergou", 80, "hello"));
	allStu.insert(student(5, "dagou", 60, "hello"));
 
	// sort
	student_table::index<_id>::type& sort_id = allStu.get<0>();
	cout << "sort by student id:" << endl;
	student_table::index<_id>::type::iterator iter_id = sort_id.begin();
	for (; iter_id != sort_id.end(); iter_id++) {
		iter_id->print();
	}
	cout << "\n" << endl;
 
	student_table::index<_name>::type& sort_name = allStu.get<1>();
	cout << "sort by student name:" << endl;
	student_table::index<_name>::type::iterator iter_name = sort_name.begin();
	for (; iter_name != sort_name.end(); iter_name++) {
		iter_name->print();
	}
	cout << "\n" << endl;
 
	student_table::index<_score>::type& sort_score = allStu.get<2>();
	cout << "sort by student score:" << endl;
	student_table::index<_score>::type::iterator iter_score = sort_score.begin();
	for (; iter_score != sort_score.end(); iter_score++) {
		iter_score->print();
	}
	cout << "\n" << endl;
 
	// find
	student_table::index<_name>::type& find_name = allStu.get<_name>();
	student_table::index<_name>::type::iterator iter_ergou = find_name.find("ergou");
	if (iter_ergou != find_name.end()) {
		cout << "find a student named ergou:" << endl;
		iter_ergou->print();
		// modify ergou
		student ergou = *iter_ergou;
		ergou.id = 6;            // will be success. becasuse id 6 not in the table. otherwise failure
		ergou.name = "ergou_v2";
		ergou.score = 91;
		ergou.remark = "hello ergou";
		bool isSuc = find_name.replace(iter_ergou, ergou);
	}
	// 
	cout << "sort by student id after replace ergou:" << endl;
	student_table::index<_id>::type::iterator iter_id_v2 = sort_id.begin();
	for (; iter_id_v2 != sort_id.end(); iter_id_v2++) {
		iter_id_v2->print();
	}
	cout << "\n" << endl;
 
	system("pause");
}
```

### build boost headers

```
./bootstrap.sh --prefix=/path/to/prefix
./b2 --prefix=/path/to/prefix headers
```

### boost 结合共享内存构建数据库

```
# 官方介绍:The widely used Boost.MultiIndex library is compatible with Boost.Interprocess so we can construct pretty good databases in shared memory.
https://www.boost.org/doc/libs/1_48_0/doc/html/interprocess/allocators_containers.html#interprocess.allocators_containers.containers_explained.containers_of_containers
https://www.boost.org/doc/libs/1_87_0/doc/html/interprocess/additional_containers.html
```

### Boost.MultiIndex

```cpp
//!字符串类型定义
typedef  basic_string<char, std::char_traits<char>, char_allocator> _string;
typedef struct TableAValue {
public:
	TableAValue(const void_allocator &void_alloc)
        :key(DEFAUT_STR,void_alloc)
	{ }
	void dump() const { 
		std::cerr << key.c_str() <<std::endl;
	}
    uint64_t uid64;
	_string key;
}TableComYXValue ;

struct uid_index{};
struct key_index{};

typedef bmi::multi_index_container<
    TableAValue,
    bmi::indexed_by<
    bmi::hashed_unique
    <bmi::tag<uid_index>,  bmi::member<TableAValue,uint64_t,&TableAValue::uid64> >,
    bmi::hashed_non_unique
    <bmi::tag<key_index>,  bmi::member<TableAValue,_string,&TableAValue::key> > >,
    managed_shared_memory::allocator<TableAValue>::type
> TableAValue_index;

typedef bmi::nth_index<TableAValue_index,0>::type ordered__DataUID;
typedef bmi::nth_index<TableAValue_index,1>::type ordered__key;

// 定义迭代器类型别名
typedef TableAValue_index::index<key_index>::type::iterator key_iterator;

// 获取 key 索引
ordered__key& key_indexs = TableAValue_index->get<key_index>();

// 创建要查找的 key
_string key1("abc", alloc_inst);

// 查找单个元素
key_iterator it = key_indexs.find(key1);
if (it != key_indexs.end()) {
    std::cout << "Found: ";
    it->dump();
} else {
    std::cout << "Key not found." << std::endl;
}

// 查找所有匹配元素
std::pair<key_iterator, key_iterator> range = key_indexs.equal_range(key1);
for (key_iterator it = range.first; it != range.second; ++it) {
    it->dump();
}
```
