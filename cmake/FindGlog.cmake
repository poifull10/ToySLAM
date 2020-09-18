unset(GLOG_FOUND)

find_path(GLOG_INCLUDE_DIR NAMES glog/logging.h)
find_library(GLOG_LIBRARY NAMES glog)

include(FindPackageHandleStandardArgs)

add_library(Glog::Glog UNKNOWN IMPORTED)
set_target_properties(
  Glog::Glog PROPERTIES
  IMPORTED_LOCATION "${GLOG_LIBRARY}"
  INTERFACE_INCLUDE_DIRECTORIES "${GLOG_INCLUDE_DIR}"
)

find_package_handle_standard_args(Glog REQUIRED_VARS GLOG_INCLUDE_DIR GLOG_LIBRARY)
