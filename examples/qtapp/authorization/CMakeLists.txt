
cmake_minimum_required(VERSION 3.5)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

project(${APPNAME} LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

set(APPNAME "Authorinzation")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS network REQUIRED)

message("---current Qt version is[" ${QT_VERSION_MAJOR}  "]-----")

set(SRC_CPU
        ./machineid/GetCpuIndex.cc
)

set(SRC_UI
        ./ui/mainwindow.cc
        ./ui/authorization.qrc
)

set (SRC_LIST
        main.cc
)

set (SRC_NETSERVICE
        ./netservice/DownloadManager.cc
        ./netservice/AuthHttpRequest.cc
)

add_executable(${APPNAME}
    ${SRC_LIST}
    ${SRC_UI}
    ${SRC_CPU}
    ${SRC_NETSERVICE}
)

target_link_libraries(${APPNAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Network
)


add_custom_target(copy_files ALL  
  VERBATIM 
  # COMMAND_EXPAND_LISTS 
  # COMMAND ${CMAKE_COMMAND} -E make_directory "lib" 
  COMMAND ${CMAKE_COMMAND} -E 
                  copy_directory  
                  "${CMAKE_CURRENT_SOURCE_DIR}/lib" 
                  "${CMAKE_BINARY_DIR}" 
) 
