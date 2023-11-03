cmake_minimum_required(VERSION 3.14)

project(dbus LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools DBus)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools DBus)

set(PROJECT_HEADERS_DIR include)
set(PROJECT_SOURCES_DIR src)
file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

qt_add_dbus_adaptor( GENERATED_SOURCES
        ru.mishenko.maksim.dbus.xml
        main.cpp
        DBusListner )

#target_sources(dbus
#  PRIVATE
#    ru.mishenko.maksim.dbus.xml
#)

add_executable(dbus
  main.cpp
  ${HEADERS}
  ${SOURCES}
)
target_link_libraries(dbus Qt${QT_VERSION_MAJOR}::Core)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include(GNUInstallDirs)
install(TARGETS dbus
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
set_property(SOURCE main.cpp PROPERTY SKIP_AUTOMOC ON)
