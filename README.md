# VisualKeyboard
-------------
使用 Qt 编写的一款键盘/按键/鼠标可视化工具，实时显示您的键盘、鼠标输入。

[![pVwbUVf.png](https://s21.ax1x.com/2025/08/14/pVwbUVf.png)](https://imgse.com/i/pVwbUVf)

[![pVwbtqP.png](https://s21.ax1x.com/2025/08/14/pVwbtqP.png)](https://imgse.com/i/pVwbtqP)

> 可以拖动显示的位置，如果需要调整开始位置（每次启动时的位置），可以双击“开始位置”。（为什么要设计这么逆天的操作呢？主要是当时找不到加新按钮的位置了，加上去不美观）

简单美观的键盘可视化工具，方便数码、科技、电子等领域的视频UP主们在视频中进行操作演示。
<br>
A simple and useful tools for digital video makers or so.
- 目前仅支持 Windows系统
- Only $Windows$ Supported

## Synopsis

### 环境依赖
- Desktop Qt 5.9.9 MinGW 32bit
- 支持C++14

仅在 Desktop Qt 5.9.9 MinGW 32bit下编译通过，其它未知。

#### Process of Building
**qmake**
`qmake.exe VisualKeyboard.pro -spec win32-g++`


**Make**
`mingw32-make.exe -j8 in Your_Path\build-VisualKeyboard-Desktop_Qt_5_9_9_MinGW_32bit-Release`

#### Process of Cleaning
**Make**
`mingw32-make.exe clean -j8 in Your_Path\build-VisualKeyboard-Desktop_Qt_5_9_9_MinGW_32bit-Release`

### 目录结构
不会写，自己看着办

### 1.0 更新内容
这是第一个版本呢

> 注：本项目同样为学习性项目，可能存在很多 bug，一般情况也不会继续维护，不保证兼容性，可供学习参考。
