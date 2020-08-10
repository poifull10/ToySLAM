
add_library(
  ${PROJECT_NAME}
  tiny_sfm.cpp
  camera_model/pinhole_camera.cpp
  initializer/pose_initializer.cpp
  matcher/image_matcher.cpp
  util/load_data.cpp
)

add_library(TSfM::TSfM ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_package(OpenCV REQUIRED core xfeatures2d imgcodecs)
find_package(Boost REQUIRED system)
find_package(Eigen3 REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} yaml-cpp Boost::system)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
