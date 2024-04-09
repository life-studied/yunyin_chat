# yunyin_chat

​	一个全栈C++聊天项目。

## Run

​	本项目使用`cmake`构建：

```shell
cmake -S . -B build -G "MinGW Makefiles" && cmake --build build
cd build && yunyin_chat.exe
```

* 本项目依赖[CMake](https://cmake.org/)
* 本项目依赖[QT](https://www.qt.io/zh-cn/)
  * 使用QtCreater编译
  * 或者安装Qt后配置环境变量：
    * C:\Qt\6.5.1\mingw_64\bin
    * C:\Qt\6.5.1\mingw_64\lib
    * C:\Qt\Tools\mingw1120_64\bin

## Arch

​	

## Documents

​	本项目使用`doxygen`生成代码文档。

```shell
cd docs && doxygen
```

​	打开生成的`html/index.html`。