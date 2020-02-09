add_library(lib_obj OBJECT)

target_sources(
  lib_obj
  PRIVATE
  "lib.cpp"
)

target_include_directories(lib_obj PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(lib)

target_link_libraries(lib PUBLIC lib_obj)

add_library(
  lib::lib
  ALIAS
  lib
)

add_executable(lib_test)

target_sources(
  lib_test
  PRIVATE
  "main.test.cpp"
  "lib.test.cpp"
)

target_link_libraries(
  lib_test
  PRIVATE
    lib::lib
    ut
)

add_test(NAME lib::test COMMAND lib_test)
