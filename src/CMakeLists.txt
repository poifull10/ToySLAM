
add_library(${PROJECT_NAME} tiny_sfm.cpp)
add_library(TSfM::TSfM ALIAS ${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
