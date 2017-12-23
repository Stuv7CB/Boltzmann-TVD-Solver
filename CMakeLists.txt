cmake_minimum_required(VERSION 3.7)
set(PROJECT Boltzmann-TVD-Solver)
project(${PROJECT})
message("Start configuring project")

add_definitions(-DDESKTOP)

set(EXECUTABLE ${PROJECT})
set(SOURCE_ROOT ./src)
set(FILES_DIR ${CMAKE_BINARY_DIR})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(EXTERNAL_PROJECTS_DIR "./cmake_externalprojects")

if(DEFINED USE_GTEST)
# Download and unpack googletest at configure time
message("Configure google test")
configure_file(${EXTERNAL_PROJECTS_DIR}/GoogleTest.cmake googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()
endif()

aux_source_directory(${SOURCE_ROOT} SOURCES)
file (GLOB_RECURSE SUB_SOURCES "${SOURCE_ROOT}/classes/*.c*")

set(SOURCES ${SOURCES} ${SUB_SOURCES})

file (GLOB_RECURSE HEADERS "${SOURCE_ROOT}/headers/*.h*")

source_group(Classes FILES ${SUB_SOURCES})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${EXECUTABLE} ${SOURCES} ${HEADERS})

find_package(Threads)

target_link_libraries(${EXECUTABLE} ${CMAKE_THREAD_LIBS_INIT})

###############################Add tests##########################################################
if(DEFINED USE_GTEST)
    set(TEST_ROOT ${SOURCE_ROOT}/tests)
    aux_source_directory(${TEST_ROOT} TEST_SOURCES)
    file (GLOB TEST_MOCKS "${TEST_ROOT}/Mocks/*.hpp")
    file (GLOB TEST_HEADERS "${TEST_ROOT}/headers/*.hpp")
    add_executable(unit_test ${TEST_SOURCES} ${SUB_SOURCES} ${TEST_MOCKS} ${TEST_HEADERS})
    target_link_libraries(unit_test gtest gmock_main ${CMAKE_THREAD_LIBS_INIT})
    add_test(NAME unit_test COMMAND unit)
endif()
##################################################################################################
