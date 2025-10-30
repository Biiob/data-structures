include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Prevent GoogleTest from forcing its own C++ standard
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(DataStructure_test LinkedListTest.cpp)
target_link_libraries(DataStructure_test
    PRIVATE
        DataStructure
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(DataStructure_test)
