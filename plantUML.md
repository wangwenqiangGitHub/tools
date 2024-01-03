# 官网资料

- 官网服务器`http://www.plantuml.com/plantuml/uml/SyfFKj2rKt3CoKnELR1Io4ZDoSa70000`
- `https://plantuml.com/zh`

# 语法

- 类之间的关系: 聚合，组合`*__`，泛化`空心箭头实线<|--`, 依赖`<...`, 关联`<--`, 实现(关系的紧密程度，由小到大顺序是：依赖->关联->聚合->组合)
- 泛化关系: 泛化关系表示类之间的继承关系，其中一个类是另一个类的子类。is-a

```cpp
class Animal {
    public:
    virtual void makeSound() = 0;
};

class Dog : public Animal {
    public:
    void makeSound() override {
            std::cout << "Woof!" << std::endl;
                }
};

class Cat : public Animal {
    public:
    void makeSound() override {
            std::cout << "Meow!" << std::endl;
                }
};
```

- 组合关系:组合关系表示类之间的整体与部分的关系，其中一个类包含另一个类的对象作为其部分。在PlantUML中，组合关系使用带实心菱形的实线来表示。"has-a"关系

```cpp
class Engine {
    public:
    void start() {
            std::cout << "Engine started" << std::endl;
                }
};

class Car {
    private:
    Engine engine;

    public:
    void startCar() {
            engine.start();
            std::cout << "Car started" << std::endl;
                }
};
```

- 聚合关系:聚合关系也表示整体与部分的关系, 但它比组合关系更弱.在聚合关系中，部分对象可以属于多个整体对象，而在组合关系中，部分对象只能属于一个整体对象

```
class Department {
    public:
    std::vector<Employee> employees;
    void addEmployee(const Employee& emp) {
            employees.push_back(emp);
        }
};

class Employee {
    public:
    std::string name;
    int id;
    // 其他员工信息
};
```

- 依赖关系:就是通过传参的方式用到某个类中`<...`

```
class ImageLoader{
    loadImage(ImageInfo info)
}

class ImageInfo{

}
```

# plantUML

```
java 环境Zulu java8
brew install graphviz
apt-get install graphviz
#vim
if index(g:bundle_group, 'plantUML') >= 0
Plug 'aklt/plantuml-syntax'
Plug 'weirongxu/plantuml-previewer.vim'
Plug 'tyru/open-browser.vim'
endif
# 快捷键
:PlantumlOpen
:e diagram.puml
:PlantumlSave
:PlantumlSave diagram.png
:PlantumlSave diagram.svg
```
