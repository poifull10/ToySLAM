find_package(Boost REQUIRED program_options)

add_executable(track_sample main.cpp)
target_link_libraries(track_sample ToySLAM::ToySLAM Boost::program_options)
target_compile_features(track_sample PRIVATE cxx_std_17)
