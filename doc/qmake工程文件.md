# 浅谈 qmake 之 pro、pri、prf、prl文件

## 1 示例qtwebengine.pro  

```shell
load(qt_parts)
load(configure)

runConfigure()

!isEmpty(skipBuildReason) {
    SUBDIRS =
    log($${skipBuildReason}$${EOL})
    log(QtWebEngine will not be built.$${EOL})
}

QMAKE_DISTCLEAN += .qmake.cache

OTHER_FILES = \
    tools/buildscripts/* \
    tools/scripts/* \
    config.tests/khr/* \
    config.tests/libcap/* \
    config.tests/libvpx/* \
    config.tests/snappy/* \
    config.tests/re2/* \
    mkspecs/features/*
```

load效果和CONFIG + qt_parts效果差不多  

```shell
./mkspecs/features/configure.prf
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/configure.prf
/usr/lib/x86_64-linux-gnu/qt5/mkspecs/features/qt_parts.prf
```

尽管每次和cmake对比起来，我们总是说qmake简单、功能少   
但是qmake仍然是一个非常复杂的东西  
不是太清楚CONFIG等变量到底如何起作用的  
用过的qmake内置变量和函数不超过20个  
看Qt Creator源码或者QtSolution等库中自己使用的 *.pro 文件就想看天书一样  
抓住一条线，简单介绍一下 "*.pro、*.pri、*.prf、*.prl"等四种文件:干嘛用的，如何用的  

## 2 *.pro

qmake 的工程(project)文件，这个大家肯定都非常熟悉了。那我就不费话了，上例子：

这是一个典型的Qt示例程序的.pro文件(propriprfprl.pro)：

```bash
TEMPLATE = app
CONFIG += QT
QT += core gui

TARGET = propriprfprl

SOURCES += main.cpp/
        widget.cpp
HEADERS  += widget.h
FORMS    += widget.ui
```

前面3行是qmake的默认值，我们都可以省略
TARGET 这行指定工程名，我们也可以省略  

## 3 *.pri  

i是什么东西？包含(include)的首字母。类似于C、C++中的头文件吧,  

我们可以*.pro文件内的一部分单独放到一个*.pri文件内，然后包含进来  

接前面的例子，我们将源文件的设置独立出来，放到propriprfprl.pri文件内：

```bash
SOURCES += main.cpp/
        widget.cpp
HEADERS  += widget.h
FORMS    += widget.ui
```

这时，我们的 propriprfprl.pro 文件就可以简化为：  

```bash
TEMPLATE = app
CONFIG += QT
QT += core gui

TARGET = propriprfprl
include(propriprfprl.pri)
```

这有什么用呢？对我们这个例子来说，确实没什么用，反而多了一个文件，更麻烦了。  
可是，如果一个大点的项目，含有多个*.pro文件呢，这些pro需要有些共同的设置或需要的文件，这时就很有必要了。

## 4 *.prf

f又是神马东东？特性(feature)的首字符  
和pri文件类似，该文件也是要被包含进pro文件的  
只是：它更隐蔽  
你经常和它打交道，可能却一直视而不见  
我们这个例子中其实已经用到了，这就是  
CONFIG+=QT  
当我们在CONFIG中指定一个东西时，qmake就会尝试去加载相应的feature文件  
Qt安装目录下的 mkspecs/features/qt.prf  
features 文件的文件名必须小写  
qmake 去哪些目录下搜索features文件呢？  
manual中有介绍，此处略  
暂时只知道前面提到的 $$QTDIR/mkspecs/features 就可以了  
写一个自己的features文件：propriprfprl.prf  

```bash
win32:CONFIG += console
```

为win32的程序添加控制台，有点多次一举哈。
将该文件放置到我们前面提到的目录中
然后在pro文件内添加

```bash
CONFIG += propriprfprl
```

看到和 CONFIG += console 同样的效果了吧？

注：我们也可以使用 load命令来加载prf文件，比如前面的命令可以认为等价于

```bash
load(propriprfprl)
```

## 5 *.prl

l这个东西容易理解，链接(link)的首字符。主要和生成与使用库密切相关(动态库也可以有该文件，去Qt安装目录下的lib目录下看看即可)。  
生库时，我们需要使用下列配置(进而生成和库文件同名的 *.prl 文件)

```bash
CONFIG += create_prl
```

当工程的TEMPLATE为app时，会自动添加如下指令(找库文件的时候，会尝试找相应的 *.prl 文件)

```bash
CONFIG += link_pri
```

那么该文件有什么用处呢？举一个大家可能熟悉的例子libQt5OpenGL这个库  
编译时，需要 libQt5OpenGL.so.5.11.3 这个库文件  
需要指定这几个库文件,如果有prl文件呢，该文件就会包含依赖信息了，我们看一下：  
/usr/lib/x86_64-linux-gnu/libQt5OpenGL.prl

```bash
QMAKE_PRL_BUILD_DIR = /build/qtbase-opensource-src-5.11.3.28/src/opengl
QMAKE_PRO_INPUT = opengl.pro
QMAKE_PRL_TARGET = libQt5OpenGL.so.5.11.3
QMAKE_PRL_CONFIG = lex yacc depend_includepath testcase_targets import_plugins import_qpa_plugin qt_build_extra file_copies qmake_use qt warn_on release link_prl incremental 
shared release linux unix posix gcc sse2 aesni sse3 ssse3 sse4_1 sse4_2 avx avx2 avx512f avx512bw avx512cd avx512dq avx512er avx512ifma avx512pf avx512vbmi avx512vl compile_e
xamples enable_new_dtags f16c largefile precompile_header rdrnd shani nostrip x86SimdAlways prefix_build force_independent utf8_source create_prl link_prl prepare_docs qt_doc
s_targets no_private_qt_headers_warning QTDIR_build qt_example_installs exceptions_off testcase_exceptions explicitlib warning_clean opengl relative_qt_rpath qmake_cache targ
et_qt c++11 strict_c++ c++14 c++1z hide_symbols bsymbolic_functions qt_install_headers need_fwd_pri qt_install_module create_cmake compiler_supports_fpmath create_pc create_l
ibtool have_target dll thread uic opengl moc resources
QMAKE_PRL_VERSION = 5.11.3
QMAKE_PRL_LIBS =  -lQt5Widgets -lQt5Gui -lQt5Core -lpthread
```

## 资料参考

浅谈 qmake 之 pro、pri、prf、prl文件  
    - https://blog.csdn.net/perfectguyipeng/article/details/10371603  
