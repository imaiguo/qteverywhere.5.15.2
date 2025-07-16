
cmake_minimum_required(VERSION 3.31)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

set(CMAKE_BUILD_TYPE Release)
set(APPNAME "RoundLabel")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

project(${APPNAME} LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WebEngineWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WebChannel REQUIRED)

message("current Qt version is[" ${QT_VERSION_MAJOR}  "]")

set(SRC
    src/main.cpp
    src/browser.cpp
    src/browserwindow.cpp
    src/downloadmanagerwidget.cpp
    src/downloadwidget.cpp
    src/tabwidget.cpp
    src/webpage.cpp
    src/webpopupwindow.cpp
    src/webview.cpp
    data/simplebrowser.qrc
)

set(UILIST
    ui/certificateerrordialog.ui
    ui/downloadmanagerwidget.ui
    ui/downloadwidget.ui
    ui/passworddialog.ui
)

QT5_WRAP_UI(UIFILES ${UILIST} )

add_executable(${APPNAME}
    ${SRC}
    ${UIFILES}
)

target_link_libraries(${APPNAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
        Qt${QT_VERSION_MAJOR}::WebEngineWidgets
        Qt${QT_VERSION_MAJOR}::WebChannel
)
