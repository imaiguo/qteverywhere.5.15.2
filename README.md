# QT5.15.2

## 依赖项

## 1. Debian环境

### 安装qtbase的依赖
```
$ sudo apt build-dep qtbase-opensource-src
```

### 配置准备
```
$ cd qt-everywhere.5.15.2

$ ./configure -prefix /opt/qt/qteverywhere.5.15.2 -opensource -confirm-license -nomake tests
or
$ mkdir & cd build
$ ../configure -prefix /opt/qt/qteverywhere.5.15.2/ -release -opensource -confirm-license -plugin-sql-mysql -plugin-sql-sqlite -no-sql-sqlite2 -plugin-sql-tds -system-sqlite -system-harfbuzz -system-zlib -system-libpng -system-libjpeg -system-doubleconversion -system-pcre -openssl -no-rpath -verbose -optimized-qmake -dbus-linked -no-strip -no-separate-debug-info -qpa wayland -xcb -glib -icu -accessibility -no-directfb -no-use-gold-linker -recheck-all -nomake examples -make-tool make

$ make -j `nproc`
$ make install
```

### 为应用编译准备环境
```
export QT_BUILDDIR=/opt/qt/qteverywhere.5.15.2
export LD_LIBRARY_PATH=$QT_BUILDDIR/lib:$LD_LIBRARY_PATH
export QT_QPA_PLATFORM_PLUGIN_PATH=$QT_BUILDDIR/plugins/platforms
export QT_PLUGIN_PATH=$QT_BUILDDIR/plugin
export PKG_CONFIG_PATH=$QT_BUILDDIR/lib/pkgconfig:$PKG_CONFIG_PATH
export PATH=$QT_BUILDDIR/bin:$PATH
```

## 2. Windows Build with MSVC

查看编译帮助 [ qtbase\config_help.txt ]

```bash
> .\configure.bat -help
```
##
- Supported compiler (Visual Studio 2012 or later, MinGW-builds gcc 4.9 or later)
- Perl version 5.12 or later   [ http://www.activestate.com/activeperl/ ] We recommend Strawberry Perl, available from <http://strawberryperl.com/> 
- Python version 2.7 or later  [ https://www.python.org/ftp/python/2.7.17/python-2.7.17.amd64.msi ]

### 编译Release
```
> cmd
> mkdir build & cd build
> "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
> set CL=/MP
> ..\configure.bat -prefix D:\devtools\Qt.5.15.2 -release -opensource -confirm-license  -no-sql-sqlite2 -no-rpath -verbose -no-strip -no-separate-debug-info -accessibility -no-directfb -no-use-gold-linker -recheck-all -nomake examples -nomake tests -openssl-linked OPENSSL_INCDIR=D:\devtools\openssl.3.0.8\include OPENSSL_LIBDIR=D:\devtools\openssl.3.0.8\lib
> nmake
> nmake install
```

### 调试Debug
```bash
> ..\configure.bat -prefix D:\devtools\Qt.5.15.2 -debug -opensource -confirm-license  -no-sql-sqlite2 -no-rpath -verbose -no-strip -accessibility -no-directfb -no-use-gold-linker -recheck-all -nomake examples -nomake tests -openssl-linked OPENSSL_INCDIR=D:\devtools\openssl.3.0.8\debug\include OPENSSL_LIBDIR=D:\devtools\openssl.3.0.8\debug\lib
```

### 编译Static Release
```bash
> ..\configure.bat -prefix D:\devtools\Qt.5.15.2\static -release -static -opensource -confirm-license  -no-sql-sqlite2 -no-rpath -verbose -no-strip -no-separate-debug-info -accessibility -no-directfb -no-use-gold-linker -recheck-all -nomake examples -nomake tests -openssl-linked OPENSSL_INCDIR=D:\devtools\openssl.3.0.8\include OPENSSL_LIBDIR=D:\devtools\openssl.3.0.8\lib
```

### 编译Static Debug
```bash
> ..\configure.bat -prefix D:\devtools\Qt.5.15.2\static -debug -static -opensource -confirm-license  -no-sql-sqlite2 -no-rpath -verbose -no-strip -no-separate-debug-info -accessibility -no-directfb -no-use-gold-linker -recheck-all -nomake examples -nomake tests -openssl-linked OPENSSL_INCDIR=D:\devtools\openssl.3.0.8\debug\include OPENSSL_LIBDIR=D:\devtools\openssl.3.0.8\debug\lib
```

## 源码下载 [https://download.qt.io/]
