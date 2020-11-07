#include <camera_model/pinhole_camera.h>
#include <glog/logging.h>
#include <image/frame.h>
#include <image/image.h>
#include <matcher/image_matcher.h>
#include <tracker/tracker.h>
#include <util/load_data.h>

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
  {
    boost::program_options::options_description description("Allowed options");
    description.add_options()                                                                                             //
        ("dir,d", boost::program_options::value<fs::path>()->default_value("../data"), "data path")                       //
        ("cam,c", boost::program_options::value<fs::path>()->default_value("../data/cam.yaml"), "calibration file path")  //
        ("num,n", boost::program_options::value<size_t>()->default_value(0), "# of images to be used")                    //
        ("help,h", "show help");

    boost::program_options::store(parse_command_line(argc, argv, description), vm);
    boost::program_options::notify(vm);

    if (vm.count("help") > 0) {
      std::cerr << description << std::endl;
      exit(1);
    }
  }

  std::vector<fs::path> imageFiles;
  {
    const auto dataDir = vm["dir"].as<fs::path>();
    BOOST_FOREACH (const fs::path& p, std::make_pair(fs::directory_iterator(dataDir), fs::directory_iterator())) {
      if (!fs::is_directory(p) && p.extension() == ".png") {
        imageFiles.emplace_back(p);
      }
    }
    std::sort(imageFiles.begin(), imageFiles.end());
  }

  {
    int numOfLoading = vm["num"].as<size_t>();
    int num = imageFiles.size();
    std::optional<size_t> numOfRemoval = numOfLoading == 0 ? std::nullopt : std::make_optional<size_t>(std::max(0, num - numOfLoading));
    if (numOfRemoval.has_value()) {
      for (size_t i = 0; i < numOfRemoval.value(); i++) {
        imageFiles.pop_back();
      }
    }
    LOG(INFO) << imageFiles.size() << " images to be load";
  }

  tsfm::PinholeCamera pinholeCamera;
  {
    const auto& camYaml = vm["cam"].as<fs::path>();
    tsfm::CalibrationLoader calibration(camYaml);
    const auto [_, calib] = calibration.load();
    pinholeCamera.setIntrinsic(calib);
  }

  tsfm::Tracker tracker;
  tsfm::FrameMaker maker;
  auto frames = maker.make(imageFiles);

  std::ofstream ofs("run.log");
  for (size_t i = 0; i < frames.size() - 1; i++) {
    const auto pose = tracker(frames[i], frames[i + 1], pinholeCamera);

    LOG(INFO) << i << " th estimation : ";
    LOG(INFO) << pose;

    ofs << pose.quat()[0] << " " << pose.quat()[1] << " " << pose.quat()[2] << " " << pose.quat()[3] << " "  //
        << pose.trans()[0] << " " << pose.trans()[1] << " " << pose.trans()[2] << std::endl;
  }
}
