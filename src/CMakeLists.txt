add_library(
  ${PROJECT_NAME}
  camera_model/pinhole_camera.cpp
  initializer/pose_initializer.cpp
  matcher/image_matcher.cpp
  util/load_data.cpp
  math/pose.cpp
  util/cv_primitive.cpp
)

add_library(TSfM::TSfM ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic>
  $<$<CXX_COMPILER_ID:GCC>:-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused>
  ${CMAKE_CXX_FLAGS}
)

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
