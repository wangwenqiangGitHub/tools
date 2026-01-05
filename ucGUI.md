# ucGUI控件基础

1.控件类型

- 基础控件:按钮, 文本标签, 输入框, 滑块, 进度条
- 容器控件: 窗口(Window), 框架(frame), 列表(ListBox), 下拉菜单(DropDown)
- 高级控件: 图标(Graph),表格(Table),滚动条(scrollBar)

2.控件属性

- 位置和尺寸:控件的坐标(X/Y)和大小(Width/Height)
- 样式(Style):字体,颜色，边框, 背景等.
- 事件回调:点击(click),长按(LongPress),输入(Input)等

# 模拟工程

1. 测试ucGUI参考:`https://github.com/hh115154/GladiatorLibrary/tree/master/SeggerEval_WIN32_MSVC_MinGW_GUI_V532`
2. 参考百度网盘emwin工程`emwin\SeggerEval_WIN32_MSVC_MinGW_GUI_V548`

# 参考浏览器框架的一点思考

1. 浏览器是采用html文件描述网页，得到对象模型，再对象模型布局，通过浏览器后端渲染render(dtk)
2.

# WM主要逻辑

1. \_DrawNext()是WM的重绘调度器, 他用`WM_FirstWin`这个全局的链表来依次检查哪些窗口需要重绘, 链表的构建是在创建窗口时由`_AddToLinList()`完成:

- 每个新建的`WM_Obj`都被挂到`WM_FirstWin`的hNextLin链条上。
- `_DrawNext()`每次触发时，会从上次停下来的NextDrawWin开始, 调用`_Paint(iWin, pWin)`,
  如果窗口仍有`WM_SF_INVALID`标记，就绘制并清掉标识。
- 无论是否实际绘制，`iWin = pWin->hNextLin`都会推进到下一节点，直到处理UpdataRem(默认5)个窗口或者链表结束,
  然后把当前位置保存到NextDrawWin,下一轮接着往后轮询，所以只要菜单窗口或者父窗口在`gui_menu_create()`,`MENU_CreateEx()`时成功加入WM链表，`_DrawNext()`就会被轮询到。如果菜单没有被显示，主要问题是:
  a. 菜单窗口没有设`WM_CF_SHOW`或者被`WM_HideWindow()`后未重新`WM_ShowWIndow()`; b.
  菜单的`WM_Obj->Status`没有`WM_SF_INVALID`,导致`_Paint()`直接跳过; c.
  菜单实际上被挂在父窗口/层上。位置超出屏幕，或者没有被`WM_BringToTop()`; d.
  xml的逻辑中由`active_flag`,`gui_menu_add_submenu`没有被执行。
