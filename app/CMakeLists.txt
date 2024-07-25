add_executable(app main.cpp)

target_link_libraries(app PUBLIC lib)

install(TARGETS app RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build)
target_compile_options(app PRIVATE -Wall -Wextra -pedantic -Wno-deprecated-enum-enum-conversion)
