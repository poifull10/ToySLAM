
add_executable(
  TSfMTest
  main.cpp
  test_pinhole_camera.cpp
  test_vector.cpp
  test_pose.cpp
  test_load_data.cpp
  test_image_matcher.cpp
  test_pose_initializer.cpp
  test_cv_primitive.cpp
  test_bundle_adjustment.cpp
)

target_link_libraries(TSfMTest gtest TSfM::TSfM)
