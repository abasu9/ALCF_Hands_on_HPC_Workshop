#include "argparse.hpp"
#include <sycl/sycl.hpp>

int main(int argc, char **argv) {

  //  _                ___
  // |_) _. ._ _  _     |  ._  ._     _|_
  // |  (_| | _> (/_   _|_ | | |_) |_| |_
  //                           |
  argparse::ArgumentParser program("5_copy_device_to_host");

  program.add_argument("-g", "--global")
      .help("Global Range")
      .default_value(1)
      .action([](const std::string &value) { return std::stoi(value); });

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    exit(0);
  }

  const auto global_range = program.get<int>("-g");

  //    _                ___               _
  //   | \  _. _|_  _.    | ._ _. ._   _ _|_ _  ._
  //   |_/ (_|  |_ (_|    | | (_| | | _>  | (/_ |
  //
  sycl::queue Q;
  std::cout << "Running on " << Q.get_device().get_info<sycl::info::device::name>() << "\n";

  // Allocate Device Memory
  int *A = sycl::malloc_device<int>(global_range, Q);
  // Submit blocking kernel who use the memory
  Q.parallel_for(global_range, [=](auto id) { A[id] = id; }).wait();
  // Allocate Host Memory
  std::vector<int> A_host(global_range);
  // Copy the device memory to the host
  Q.copy<int>(A, A_host.data(), global_range).wait();
  sycl::free(A, Q);

  for (size_t i = 0; i < global_range; i++)
    std::cout << "A_host[ " << i << " ] = " << A_host[i] << std::endl;
  return 0;
}
