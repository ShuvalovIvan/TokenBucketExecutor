
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(TEST_SOURCES
    test_main.cpp
)


add_executable(UnitTests ${TEST_SOURCES})

include_directories(../../src)

target_link_libraries(UnitTests PRIVATE 
    TokenBucketExecutor.lib
    GTest::gtest_main)

add_test(NAME UnitTests
    COMMAND UnitTests)

include(GoogleTest)
gtest_discover_tests(UnitTests)