# qtwebengine 5.15.2

## 1 Debian

### 1.1 安装qtbase的依赖

```bash
>
> sudo apt build-dep qtbase-opensource-src
>
```

### 1.2 为应用编译准备环境

```bash
export QT_BUILDDIR=/opt/Qt.5.15.2
export LD_LIBRARY_PATH=$QT_BUILDDIR/lib:$LD_LIBRARY_PATH
export QT_QPA_PLATFORM_PLUGIN_PATH=$QT_BUILDDIR/plugins/platforms
export QT_PLUGIN_PATH=$QT_BUILDDIR/plugin
export PKG_CONFIG_PATH=$QT_BUILDDIR/lib/pkgconfig:$PKG_CONFIG_PATH
export PATH=$QT_BUILDDIR/bin:$PATH
```

### 1.3 编译

```bash
> cd qtwebengine
> mkdir & cd build
>
> qmake .. QT_BUILD_PARTS+=tests QMAKE_EXTRA_ARGS+="-proprietary-codecs -webengine-jumbo-build 0 -system-webp -webengine-kerberos -nomake tests"
>
> make -j `nproc`
> make install
```



## 2 Windows

### 2.1 安装perl [https://strawberryperl.com/download/5.32.1.1/strawberry-perl-5.32.1.1-64bit.msi]

### 2.2 安装python2/python3 [https://www.python.org/ftp/python/2.7.17/python-2.7.17.amd64.msi]

### 2.3 安装node [https://nodejs.org/dist/v18.14.2/node-v18.14.2-win-x64.zip] 已经包含在源码目录中[tools\nodejs\node.exe] 添加到Path

### 2.4 为应用编译准备环境
```bash
> cmd
> "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
>
> set QT_BUILDDIR=D:\devtools\Qt.5.15.2
> set LD_LIBRARY_PATH=%QT_BUILDDIR%\lib;%LD_LIBRARY_PATH%
> set QT_QPA_PLATFORM_PLUGIN_PATH=%QT_BUILDDIR%\plugins\platforms
> set QT_PLUGIN_PATH=%QT_BUILDDIR%\plugin
> set PKG_CONFIG_PATH=%QT_BUILDDIR%\lib\pkgconfig;%PKG_CONFIG_PATH%
> set Path=%QT_BUILDDIR%\bin;%QT_BUILDDIR%\gnuwin32\bin;D:\devtools\Strawberry\perl\bin;%Path%
> # 添加源码自带gperf工具
> # cp -r qteverywhere\gnuwin32\bin to D:\devtools\Qt.5.15.2
> set Path=D:\workspace\qteverywhere.5.15.2\gnuwin32\bin;D:\devtools\Python.2.7.17;%Path%
> 
```


### 2.5  编译Release版本[默认]

- 打开命令行提示符配置参数，此参数支持视频解码，网页视频可以通过ffmpeg解码播放

```bash
> mkdir build & cd build
> set CL=/MP
> # -webengine-jumbo-build 0: If this is added to the qmake command it will cause the 'Jumbo Build Merge Limit' to be reported as 'no' instead of 8. That turns off the jumbo build. Some distros do that to get a smaller build on some architectures such as MIPS. On x86_64 it might save a little space in the build, but the build time will increase by a very large amount.
> # -webengine-kerberos Enables Kerberos Authentication Support
> # -proprietary-codecs Enables the use of proprietary codecs such as h.264/h.265 and MP3.
> # 默认编译debug版本
> # qmake .. QMAKE_EXTRA_ARGS+="-proprietary-codecs -webengine-jumbo-build 0 -webengine-kerberos"
> qmake .. CONFIG+=release QMAKE_EXTRA_ARGS+="-proprietary-codecs -webengine-jumbo-build 0 -webengine-kerberos"
> nmake
> nmake install
```

### 2.6  编译Debug版本
```bash
> qmake .. CONFIG+=debug QMAKE_EXTRA_ARGS+="-proprietary-codecs -webengine-jumbo-build 0 -webengine-kerberos"
```

### 2.7 编译静态库Release版本
```bash
> qmake .. CONFIG+=static QMAKE_EXTRA_ARGS+="-proprietary-codecs -webengine-jumbo-build 0 -webengine-kerberos"
```

### 2.8 编译Core部分命令
```bash
> # 注意 使用 D:\devtools\Strawberry\perl\bin\ninja.exe编译代码会报错
> ninja -v  -C D:\workspace\qtwebengine.5.15.2\build\src\core\debug QtWebEngineCore
> D:\workspace\qtwebengine.5.15.2\build\src\3rdparty\ninja\ninja.exe -v  -C D:\workspace\qtwebengine.5.15.2\build\src\core\release QtWebEngineCore -k 100
```
