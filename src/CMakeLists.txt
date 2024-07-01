# add dependencies
include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME thread-pool
  GITHUB_REPOSITORY DeveloperPaul123/thread-pool
  GIT_TAG 0.6.0 # change this to latest commit or release tag
  OPTIONS
    "TP_BUILD_TESTS OFF"
    "TP_BUILD_BENCHMARKS OFF"
    "TP_BUILD_EXAMPLES OFF"  
)


set(SOURCES
    executor.cpp
    executor.h
    thread_pool_executor.cpp
)

add_library(TokenBucketExecutor.lib ${SOURCES})

target_link_libraries(TokenBucketExecutor.lib dp::thread-pool)
