HEADERS   = message.h
SOURCES   = main.cpp \
            message.cpp
QT += widgets
CONFIG += console
# install
target.path = $$[QT_INSTALL_EXAMPLES]/corelib/tools/customtype
INSTALLS += target
