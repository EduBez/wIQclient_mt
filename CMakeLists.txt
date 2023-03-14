###
#  Supporting 'VcPkg' on Linux
#
#  Install 'VcPkg' and hook up user-wide integration
#    cd vcpkg
#    ./bootstrap-vcpkg.sh
#    ./vcpkg integrate install
#
#  Find VcPkg Library with the help of 'CMAKE_TOOLCHAIN_FILE' defined in 'PreLoad.cmake'
#
###

# Project supports 'Visual Studio 2019 CMake'
#
# Configurations available:
#   Linux
#   WSL 2.0

cmake_minimum_required(VERSION 3.8)

project(wIQclient_mt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror")

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find 'VcPkg::Boost'
find_package(Boost REQUIRED)

# Add 'VcPkg::Boost' include directory
include_directories(${Boost_INCLUDE_DIR})

# Add 'VcPkg::Boost' libraries directory
link_directories(${Boost_LIBRARY_DIRS})

add_executable(
    ${PROJECT_NAME}
    "${PROJECT_SOURCE_DIR}/sockets/SimpleSocket.h"
    "${PROJECT_SOURCE_DIR}/sockets/SocketMsg.cpp"
    "${PROJECT_SOURCE_DIR}/sockets/SocketMsg.h"
    "${PROJECT_SOURCE_DIR}/sockets/SocketWait.h"
    "${PROJECT_SOURCE_DIR}/utf-8/utf8.cpp"
    "${PROJECT_SOURCE_DIR}/utf-8/utf8.h"
    ClientMt.cpp
    ClientMt.h
    CommandLine.cpp
    CommandLine.h
    Common.h
    FileParse.cpp
    FileParse.h
    Log.cpp
    Log.h
    wIQClientMain.cpp
    wIQClientMain.h
    XMLProtocol.cpp
    XMLProtocol.h
)

# Add 'include' directories to target
target_include_directories(
    ${PROJECT_NAME} PRIVATE
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/sockets"
    "${PROJECT_SOURCE_DIR}/utf-8"
)

# Links must be in that order
target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    boost_program_options
    boost_thread
    pthread
)