cmake_minimum_required(VERSION 3.5)

project(kahut LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Threads REQUIRED)

if(ANDROID)
  add_library(kahut SHARED
    main_app.cpp
    ClientWindow.cpp
    ClientWindow.h
    mainwindow.ui
  )
else()
  add_executable(kahut
    main_app.cpp
    ClientWindow.cpp
    ClientWindow.h
    mainwindow.ui
    Client.cpp
    Client.hpp
    Question.cpp
    Question.hpp
    Server.cpp
    Server.hpp
    UserConnection.cpp
    UserConnection.hpp
    User.cpp
    User.hpp
    serverwindow.cpp
    serverwindow.h
    serverwindow.ui
  )
endif()

target_link_libraries(kahut PRIVATE Qt5::Widgets)
target_link_libraries(kahut PRIVATE Threads::Threads)