#include <camera_model/pinhole_camera.h>
#include <glog/logging.h>
#include <image/image.h>
#include <initializer/pose_initializer.h>
#include <matcher/image_matcher.h>
#include <util/load_data.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>
#include <utility>

int main(int argc, char** argv)
{
  using namespace boost::program_options;
  namespace fs = boost::filesystem;
  google::InitGoogleLogging(argv[0]);

  options_description description("Allowed options");
  description.add_options()                                                             //
    ("dir,d", value<fs::path>()->default_value("../data"), "dir path")                  //
    ("cam,c", value<fs::path>()->default_value("../data/cam.yaml"), "calibration file") //
    ("num,n", value<size_t>()->default_value(0), "# of images to be used")              //
    ("help,h", "help");

  variables_map vm;
  store(parse_command_line(argc, argv, description), vm);
  notify(vm);

  if (vm.count("help") > 0)
  {
    std::cerr << description << std::endl;
    exit(1);
  }

  const auto dataDir = vm["dir"].as<fs::path>();
  std::vector<fs::path> imageFiles;
  BOOST_FOREACH (const fs::path& p, std::make_pair(fs::directory_iterator(dataDir), fs::directory_iterator()))
  {
    if (!fs::is_directory(p) && p.extension() == ".png")
    {
      imageFiles.emplace_back(p);
    }
  }
  std::sort(imageFiles.begin(), imageFiles.end());

  size_t upperLimit = vm["num"].as<size_t>();
  size_t num = imageFiles.size();
  if (upperLimit > 0)
  {
    for (size_t i = 0; i < num - upperLimit; i++)
    {
      imageFiles.pop_back();
    }
  }

  LOG(INFO) << imageFiles.size() << " images to be load";

  const auto camYaml = vm["cam"].as<fs::path>();

  tsfm::PinholeCamera pinholeCamera;
  {
    tsfm::CalibrationLoader calibration(camYaml);
    const auto [_, calib] = calibration.load();
    pinholeCamera.setIntrinsic(calib);
  }

  tsfm::PoseInitializer pi;
  tsfm::ImageMaker maker;
  auto images = maker.make(imageFiles);

  for (auto& img : images)
  {
    img->load();
  }
  tsfm::ImageMatcher im(images);
  im.extractFeatures();
  im.match();
  im.drawMatch("result.png");

  for (auto& img : images)
  {
    img->unload();
  }

  std::ofstream ofs("run.log");
  for (size_t i = 0; i < images.size() - 1; i++)
  {
    images[i]->load();
    images[i + 1]->load();

    const auto pose = pi({images[i], images[i + 1]}, pinholeCamera);

    LOG(INFO) << i << " th estimation : ";
    LOG(INFO) << pose;

    ofs << pose.quat()[0] << " " << pose.quat()[1] << " " << pose.quat()[2] << " " << pose.quat()[3] << " " //
        << pose.trans()[0] << " " << pose.trans()[1] << " " << pose.trans()[2] << std::endl;

    images[i]->unload();
  }
}
