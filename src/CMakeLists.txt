
add_library(
  ${PROJECT_NAME}
  toy_sfm.cpp
  camera_model/pinhole_camera.cpp
  initializer/pose_initializer.cpp
  matcher/image_matcher.cpp
  ba/bundle_adjustment.cpp
  geo_primitive/pose.cpp
  util/load_data.cpp
  util/cv_primitive.cpp
  image/frame.cpp
)

add_library(TSfM::TSfM ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_package(OpenCV REQUIRED core xfeatures2d imgcodecs)
find_package(Boost REQUIRED filesystem)
find_package(Eigen3 REQUIRED)
find_package(Glog REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} yaml-cpp Boost::filesystem Glog::Glog)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
