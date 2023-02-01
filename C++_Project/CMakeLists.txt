cmake_minimum_required(VERSION 3.24)
project(notyhelper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(notyhelper client/client.cpp client/gui/AppWidget.cpp client/gui/AppWidget.h client/gui/NotificationControlWidget.cpp client/gui/NotificationControlWidget.h client/gui/LoginDialog.cpp client/gui/LoginDialog.h client/gui/Noty.cpp client/gui/Noty.h server/util/Socket.h client/defines.h)
add_executable(server server/server.cpp server/server.cpp server/util/RuntimeThread.cpp server/util/RuntimeThread.h server/util/defines.h)

target_link_libraries(notyhelper
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

target_link_libraries(server pthread)

