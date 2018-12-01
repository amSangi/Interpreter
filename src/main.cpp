#include <iostream>
#include <string>
#include "interpreter.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "File path required" << std::endl;
    return 0;
  }
  std::string filename = argv[1];
  double ret = Interpreter::Interpet(filename);
  std::cout << ret << std::endl;
}