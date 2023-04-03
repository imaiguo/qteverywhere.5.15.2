
# QGet

Use QNetworkAccessManager to download file,url type include [http/https]

# Build

- windows

1. prepare vc cmd env

  execute bat "x:\Program Files\Microsoft Visual Studio\20xx\Community\VC\Auxiliary\Build\vcvars64.bat"

2. set qt env

\> set "LIB=x:\Qt\Qtx.x.x\x.x.x\msvc20xx_64\bin;%LIB%"

\> set "Path=%Path%;C:\Qt\Qtx.x.x\x.x.x\msvc20xx_64\bin"

- linux

1. install depends

$ sudo apt-get install qt5-qmake qtbase5-dev


# Install
enable ssl,should download openssl lib from https://slproweb.com/products/Win32OpenSSL.html

windows is https://slproweb.com/download/Win64OpenSSL_Light-1_1_1t.exe

put dll files [ libcrpto-1_1-x64.dll libssl-1_1-x64.dll] to excutor file or %QtPath%\msvc20xx_64\bin