include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

set(TEST_SOURCES 
    ${PROJECT_SOURCE_DIR}/tests/test.cpp
)

add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests PUBLIC abstract_algebra)
target_link_libraries(run_tests PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(run_tests)
