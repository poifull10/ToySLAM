#include <glog/logging.h>
#include <toy_slam.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <optional>
#include <utility>

int main(int argc, char** argv) {
  namespace fs = boost::filesystem;
  google::InitGoogleLogging(argv[0]);

  boost::program_options::variables_map vm;
  boost::program_options::options_description description("Allowed options");
  description.add_options()                                                                        //
      ("dir,d", boost::program_options::value<fs::path>()->default_value("../data"), "data path")  //
      ("help,h", "show help");

  boost::program_options::store(parse_command_line(argc, argv, description), vm);
  boost::program_options::notify(vm);

  if (vm.count("help") > 0) {
    std::cerr << description << std::endl;
    exit(1);
  }

  return 0;
}
