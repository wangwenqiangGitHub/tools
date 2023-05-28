# 官网资料

- 官网服务器`http://www.plantuml.com/plantuml/uml/SyfFKj2rKt3CoKnELR1Io4ZDoSa70000`
- `https://plantuml.com/zh`

# 语法

- 类之间的关系: 聚合，组合，泛化

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
