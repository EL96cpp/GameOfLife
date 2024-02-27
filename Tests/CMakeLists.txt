cmake_minimum_required(VERSION 3.5)

project(game_of_life_tests LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if ($ENV{GOOGLETEST_DIR})
    get_filename_component(_GTEST_BASE $ENV{GOOGLETEST_DIR} REALPATH)
elseif (EXISTS "") # set by QC
    get_filename_component(_GTEST_BASE "" REALPATH) # set by QC
endif()

if (NOT GTEST_ROOT)
    if (_GTEST_BASE)
        message("Setting GTEST_ROOT to ${_GTEST_BASE}")
        set(GTEST_ROOT ${_GTEST_BASE})
    else()
        message("No GTEST_ROOT specified - using system defaults.")
    endif()
endif()

find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
    message (FATAL_ERROR "No GTest Found")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(game_of_life_tests main.cpp
               tst_game_of_life_fixture_tests.cpp
               tst_game_of_life_parameterized_tests.cpp
               ../game.cpp
               ../game.h
               gamefixture.cpp
               gamefixture.h
               gameparameterized.h
)
add_test(NAME game_of_life_tests COMMAND game_of_life_tests)

target_link_libraries(game_of_life_tests PRIVATE GTest::GTest Qt${QT_VERSION_MAJOR}::Widgets)
if (GMock_FOUND)
    target_link_libraries(game_of_life_tests INTERFACE GTest::GMock)
endif()

file(COPY "${CMAKE_SOURCE_DIR}/../customview.h" DESTINATION "${CMAKE_BINARY_DIR}/game_of_life_tests_autogen/include")
