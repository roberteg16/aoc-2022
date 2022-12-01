#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>

using energy_t = unsigned long;

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

  std::priority_queue<energy_t, std::vector<energy_t>, std::greater<energy_t>>
      top3EnergyCarriedByElfs;
  std::string line;
  energy_t currEnergyOfElf = 0;
  while (std::getline(in, line)) {
    if (line == "") {
      top3EnergyCarriedByElfs.push(currEnergyOfElf);
      if (top3EnergyCarriedByElfs.size() == 4) {
        top3EnergyCarriedByElfs.pop();
      }
      currEnergyOfElf = 0;
    } else {
      currEnergyOfElf += std::stoul(line);
    }
  }

  if (top3EnergyCarriedByElfs.size() != 3) {
    std::cerr << "Expected to found at least three elfs" << std::endl;
  }

  energy_t totalEnergyCarriedByAllThreeElfs = top3EnergyCarriedByElfs.top();
  std::cout << "3rd elf most carrying energy: "
            << totalEnergyCarriedByAllThreeElfs << std::endl;
  top3EnergyCarriedByElfs.pop();
  totalEnergyCarriedByAllThreeElfs += top3EnergyCarriedByElfs.top();
  std::cout << "2nd elf most carrying energy: " << top3EnergyCarriedByElfs.top()
            << std::endl;
  top3EnergyCarriedByElfs.pop();
  totalEnergyCarriedByAllThreeElfs += top3EnergyCarriedByElfs.top();
  std::cout << "1st elf most carrying energy: " << top3EnergyCarriedByElfs.top()
            << std::endl;
  top3EnergyCarriedByElfs.pop();

  std::cout << "\nTotal carried by all three elfs: "
            << totalEnergyCarriedByAllThreeElfs << std::endl;

  return 0;
}
