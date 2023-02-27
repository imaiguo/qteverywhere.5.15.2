HOW TO BUILD QT5
================

   Debian
   -----------


安装qtbase的依赖
```
$ sudo apt build-dep qtbase-opensource-src
```

配置准备
```
$ cd qt-everywhere.5.15.2

$ ./configure -prefix /opt/qt/qteverywhere.5.15.2 -opensource -confirm-license -nomake tests
or
$ mkdir & cd build
$ ../configure -prefix /opt/qt/qteverywhere.5.15.2/ -release -opensource -confirm-license -plugin-sql-mysql -plugin-sql-sqlite -no-sql-sqlite2 -plugin-sql-tds -system-sqlite -system-harfbuzz -system-zlib -system-libpng -system-libjpeg -system-doubleconversion -system-pcre -openssl -no-rpath -verbose -optimized-qmake -dbus-linked -no-strip -no-separate-debug-info -qpa wayland -xcb -glib -icu -accessibility -no-directfb -no-use-gold-linker -recheck-all -nomake examples -make-tool make

$ make -j `nproc`
$ make install
```

为应用编译准备环境
```
export QT_BUILDDIR=/opt/qt/qteverywhere.5.15.2
export LD_LIBRARY_PATH=$QT_BUILDDIR/lib:$LD_LIBRARY_PATH
export QT_QPA_PLATFORM_PLUGIN_PATH=$QT_BUILDDIR/plugins/platforms
export QT_PLUGIN_PATH=$QT_BUILDDIR/plugin
export PKG_CONFIG_PATH=$QT_BUILDDIR/lib/pkgconfig:$PKG_CONFIG_PATH
export PATH=$QT_BUILDDIR/bin:$PATH
```




   Windows
   ----------
打开命令行提示符.

Ensure that the following tools can be found in the path

* Supported compiler (Visual Studio 2012 or later, MinGW-builds gcc 4.9 or later)
* Perl version 5.12 or later   [ http://www.activestate.com/activeperl/ ]
* Python version 2.7 or later  [ http://www.activestate.com/activepython/ ]
* Ruby version 1.9.3 or later  [ http://rubyinstaller.org/ ]

```
> cd qt-everywhere.5.15.2
> mkdir build & cd build
> set CL=/MP
> ..\configure.bat -prefix D:\Qt\qteverywhere.5.15.2 -release -opensource -confirm-license -no-sql-sqlite2 -no-rpath -verbose -optimized-qmake -no-strip -no-separate-debug-info -qpa wayland -accessibility -no-directfb -no-use-gold-linker -recheck-all -nomake examples

> nmake
> nmake install
```

To accelerate the bootstrap of qmake with MSVC, it may be useful to pass "-make-tool jom"

on the configure command line. If you do not use jom,adding "/MP" to the CL environment variable is a good idea.