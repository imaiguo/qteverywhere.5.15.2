
# QGet

Use QNetworkAccessManager to download file, url type include [http/https]

## 依赖

- enable ssl

should download openssl lib from https://slproweb.com/products/Win32OpenSSL.html

- windows is https://slproweb.com/download/Win64OpenSSL_Light-1_1_1t.exe

put dll files [ libcrpto-1_1-x64.dll libssl-1_1-x64.dll] to excutor file or %QtPath%\msvc20xx_64\bin

## MSVC

## Debian
1. install depends

```bashs
$ sudo apt-get install qt5-qmake qtbase5-dev
```


## 配置开发运行环境

```bash
> cmd
> "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
>
set QT_BUILDDIR=D:\devtools\Qt.5.15.2
set LD_LIBRARY_PATH=%QT_BUILDDIR%\lib;%LD_LIBRARY_PATH%
set QT_QPA_PLATFORM_PLUGIN_PATH=%QT_BUILDDIR%\plugins\platforms
set QT_PLUGIN_PATH=%QT_BUILDDIR%\plugin
set PKG_CONFIG_PATH=%QT_BUILDDIR%\lib\pkgconfig;%PKG_CONFIG_PATH%
set Path=%QT_BUILDDIR%\bin;D:\devtools\openssl.3.0.8\bin;%Path%
>
```
