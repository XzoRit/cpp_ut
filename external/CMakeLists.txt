add_subdirectory(boost)

add_library(ut INTERFACE)

target_include_directories(
  ut
  INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/ut/include"
)

target_compile_features(
  ut
  INTERFACE
  cxx_std_20
)
