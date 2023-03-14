#  The best way to use installed libraries with CMake is via the toolchain file scripts\buildsystems\vcpkg.cmake
#  To use this file, you simply need to add it onto your CMake command line as;
#    -DCMAKE_TOOLCHAIN_FILE=vcpkg root\scripts\buildsystems\vcpkg.cmake

# Define VCPKG_CMAKE environment variable
set(VCPKG_CMAKE "/home/edubez/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Use 'VcPkg' installed libs with CMake via its toolchain file
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_CMAKE}" CACHE STRING "")
