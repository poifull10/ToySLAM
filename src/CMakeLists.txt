add_library(
  ${PROJECT_NAME}
  toy_sfm.cpp
  camera_model/pinhole_camera.cpp
  initializer/pose_initializer.cpp
  matcher/image_matcher.cpp
  util/load_data.cpp
  geo_primitive/pose.cpp
  util/cv_primitive.cpp
)

add_library(TSfM::TSfM ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Werror)

find_package(OpenCV REQUIRED core xfeatures2d imgcodecs)
find_package(Boost REQUIRED filesystem)
find_package(Eigen3 REQUIRED)
find_package(Glog REQUIRED)

target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<INSTALL_INTERFACE:src>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  PRIVATE
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS} yaml-cpp Boost::filesystem Glog::Glog)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT tsfm-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
