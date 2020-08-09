
add_library(
  ${PROJECT_NAME}
  tiny_sfm.cpp
  camera_model/pinhole_camera.cpp
  initializer/pose_initializer.cpp
  util/load_data.cpp
)

add_library(TSfM::TSfM ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED system)

target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} yaml-cpp Boost::system)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
