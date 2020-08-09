
add_executable(
  TSfMTest
  main.cpp
  test_pinhole_camera.cpp
  test_vector.cpp
  test_pose.cpp
  test_load_data.cpp
)

target_link_libraries(TSfMTest gtest TSfM::TSfM)