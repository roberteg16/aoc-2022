#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    std::cerr << "Expected invaction: <bin> <file>" << std::endl;
    return 1;
  }

  std::string_view file = argv[1];
  std::ifstream in(file.data(), std::ios::in);
  if (!in || !in.is_open()) {
    std::cerr << "Error opening file: " << file << std::endl;
    return 1;
  }

  std::string line;
  unsigned long maxEnergyOfSingleElf = 0;
  unsigned long currEnergyOfElf = 0;
  while (std::getline(in, line)) {
    if (line == "") {
      maxEnergyOfSingleElf = std::max(maxEnergyOfSingleElf, currEnergyOfElf);
      currEnergyOfElf = 0;
    } else {
      currEnergyOfElf += std::stoul(line);
    }
  }

  std::cout << "Max energy by a single elf: " << maxEnergyOfSingleElf
            << std::endl;
  return 0;
}
