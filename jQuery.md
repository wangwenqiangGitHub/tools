# jQuery基础

- `$`等同于jQuery

- jQuery一个是对象，一个是函数

## 核心函数

```js
// 执行jquery核心函数
// 1.参数为函数:当DOM加载完成后，执行此回调函数
$(function(){

     // 2.参数为选择器字符串:查找所有匹配的标签，并将它们封装成jQuery对象
     $('#btn').click(function(){
             //3. 参数为DOM对象:将dom对象封装成jQuery对象;
             alert($(this).html()); //this代表的是dom $(this)传递dom对象,或者jquery对象
             //4. 参数为html标签字符串(用的少):创建标签对象,并封装成jQuery对象
             $('<input type="text" name="msg2"/>').appendTo('.wrap')
     })
})
```

## 核心对象

- jquery中的$("#id")和document.getElementById("id")得到的效果并不是相同的。
- `alart($("div"))`得到的是[object object]
- `alert(document.getElementById("di v"))` 得到的是[object HTMLDivElement]
- `alert($("#div")[0])`或者`alert($('#div').get(0))`得到的是`[object HTMLDivElement]`

---

主要原因是document.getElementById()返回的是DOM对象，而$()返回的是jQuery对象

```js
//当作对象使用 遍历数组
var arr=[4,7,5,1];
$.each(arr, function(index, item){
        console.log(index, item)
        })

//去掉字符串两端的空格
var str = ' my atjdsj hh     '
console.log($.trim(str)):

<script type="text/javascript">
var $btn = $('button')
console.log($btn.length)
console.log($btn[1].html())
console.log($btn[1].innerHTML)
// $btn[1]取出来的是DOM
// 按钮是所有按钮的第几个----查找的是同级的
console.log($('#btn3').index())
</script>
```

- DOM对象与jQuery对象互转
  - **jQuery对象转成DOM对象:** var &v = $("#v") //jQuery对象; var v = $v[0] //DOM对象
  - **jQuery本身提供.get(index)方法，得到相应的的DOM对象**

# 选择器
