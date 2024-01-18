cmake_minimum_required(VERSION 3.18)

project(Coverage-Finder)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(SRCS
    src/CoverageApp.cpp
)

set(CINDER_DIR "C:/tools/Cinder")
include_directories(${CINDER_DIR}/include)
link_directories(${CINDER_DIR}/lib/msw/x64)
link_directories(${CINDER_DIR}/lib/msw/x64/Debug/v143)

add_executable(coverageFinder WIN32 ${SRCS})
target_link_libraries(coverageFinder cinder)
target_compile_features(coverageFinder PRIVATE cxx_std_17)
target_include_directories(coverageFinder PUBLIC "include/")