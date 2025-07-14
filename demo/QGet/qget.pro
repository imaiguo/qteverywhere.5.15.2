QT = core network
CONFIG += cmdline

HEADERS   += DownloadManager.h

SOURCES += main.cpp DownloadManager.cc

# install
target.path = C:/QtProc/QGet
opessl.files = $$PWD/openssl/libcrypto-1_1-x64.dll
opessl.files += $$PWD/openssl/libssl-1_1-x64.dll
opessl.path = C:/QtProc/QGet
INSTALLS += target opessl
