file(GLOB_RECURSE
    SRC
    src/IFrameScaler.cpp
    src/IFrameConverter.cpp
    src/IMediaPlayer.cpp
)

#Include(FetchContent)
#FetchContent_Declare(
#    OpenCV
#    GIT_REPOSITORY https://github.com/opencv/opencv
#    GIT_TAG 4.9.0)
#FetchContent_MakeAvailable(OpenCV)
#
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_library(lib STATIC ${SRC})



target_link_libraries( lib ${OpenCV_LIBS} )

##target_link_libraries(lib PUBLIC OpenCV)

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
