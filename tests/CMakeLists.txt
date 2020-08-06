
add_executable(
  TSfMTest
  main.cpp
  test_pinhole_camera.cpp
)

target_link_libraries(TSfMTest gtest TSfM::TSfM)