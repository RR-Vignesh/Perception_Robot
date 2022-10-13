add_executable(shell-app main.cpp camera.cpp detector.cpp humanTracker.cpp tracker.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
)
