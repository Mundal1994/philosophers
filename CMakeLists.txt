cmake_minimum_required(VERSION 3.12) # version can be different

project(philosopher_project) #name of your project

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

enable_testing() #to  discover tests in test explorer 

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(philo   src/main.cpp
                       src/ThreadSimulation.cpp
                       src/ThreadSimulation_test.cpp
                       src/Philosophers.cpp
) # add cpp files

target_link_libraries(philo PRIVATE gtest) # link google test to this executable

include(GoogleTest)
gtest_discover_tests(philo) # discovers tests by asking the compiled test executable to enumerate its tests
