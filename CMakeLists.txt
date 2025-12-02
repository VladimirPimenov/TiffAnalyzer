cmake_minimum_required (VERSION 3.8)
project (TiffAnalyzer)
cmake_policy(SET CMP0079 NEW)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(src)

target_link_libraries(TiffAnalyzer
Qt5::Widgets
Qt5::Gui
Qt5::QWindowsIntegrationPlugin
Qt5::PrintSupport)