file(GLOB_RECURSE
    TESTS_SRC
    FooTests.cpp
)


Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0)
FetchContent_MakeAvailable(Catch2)

add_executable(test ${TESTS_SRC})
target_link_libraries(test PRIVATE Catch2::Catch2WithMain)


target_link_libraries(test PUBLIC lib)

install(TARGETS test RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build)

target_compile_options(test PRIVATE -Wall -Wextra -pedantic -Werror)

