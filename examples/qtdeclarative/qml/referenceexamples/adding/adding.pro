QT = core qml
CONFIG += qmltypes console

QML_IMPORT_NAME = People
QML_IMPORT_MAJOR_VERSION = 1

SOURCES += main.cpp \
           person.cpp
HEADERS += person.h
RESOURCES += adding.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/qml/referenceexamples/adding
INSTALLS += target
