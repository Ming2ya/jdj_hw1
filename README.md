# algebra

硬件技术团队编程基础作业

## 开发日志（应该叫这个吗？）

## ver. 半成品

####	 	函数部分

没什么好说的，主要完成了几个简单的（5分的）函数，即add，sub，scale，mul，trace与trans



#### Cmake部分

遇到了挺多的问题

1. 在build文件夹下使用` cmake ..`语句，报错

  ```` c
   'nmake' '-?'
  
    failed with:
  
     no such file or directory
  
  
  CMake Error: CMAKE_C_COMPILER not set, after EnableLanguage
  CMake Error: CMAKE_CXX_COMPILER not set, after EnableLanguage
  -- Configuring incomplete, errors occurred!
  ````

  之后搜了一下，在CMakeLists里加入的CMAKE_C_COMPILER和CMAKE_CXX_COMPILER的地址，

  ````c
  set(CMAKE_C_COMPILER "C:/Program Files (x86)/Dev-Cpp/MinGW64/bin/gcc.exe")
  
  set(CMAKE_CXX_COMPILER "C:/Program Files (x86)/Dev-Cpp/MinGW64/bin/c++.exe")
  ````

  但是\`nmake\`这里还是报错。

  （后经过搜索发现还是应该用语句指定编译器` cmake -G "MinGW Makefiles" ..`但这是后来的故事了）

2. 因为一时不知道怎么改，就换用cmake插件来编译，

	报错，大概意思是编译器不支持在for循环内定义变量，并给出了note

	`note: use option -std=c99, -std=gnu99, -std=c11 or -std=gnu11 to compile your code`

	我第一此直接搜这个note没有出什么有用的结果，搜了很多cmake语法，最终也没找到该用哪个，

	后来又搜了一次note，找到了对应的语句`add_compile_options()`然后成功生成了main.exe

3. 因为终端里一直报要我指定最低cmake版本，所以我也加上了

这是最终的CMakeLists：

````cmake
cmake_minimum_required(VERSION 3.15)

project (main)

add_compile_options(-std=c11 -w)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

aux_source_directory (src SRC_LIST)

include_directories (inc)

add_executable (main ${SRC_LIST})
````

