#include "Common.h"
#include "Driver.h"
#include <exception>
#include <iostream>

#include <filesystem>

// #include <gperftools/profiler.h>

int main(int argc, char **argv) {
  // ProfilerStart("perf.prof");
  if (argc < 2) {
    return -1;
  }
  // "rvlang/example.c"
  std::filesystem::path filePath(argv[1]);
  if (!std::filesystem::exists(filePath)) {
    return -1;
  }

  try {
    rvlang::Driver driver;
    driver.compile(filePath.string());
  } catch (std::exception &e) {
    std::cout << red() << "exception:\n" << e.what() << white() << "\n";
  }

  // ProfilerStop();

  return 0;
}