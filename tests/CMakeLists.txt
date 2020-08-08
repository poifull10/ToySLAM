
add_executable(
  TSfMTest
  main.cpp
  test_pinhole_camera.cpp
  test_vector.cpp
  test_pose.cpp
)

target_link_libraries(TSfMTest gtest TSfM::TSfM)