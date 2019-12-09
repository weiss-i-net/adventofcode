#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int additional_fuel(int mass) {
  int fuel;
  fuel = (mass / 3 - 2);
  return (fuel <= 0) ? 0 : fuel + additional_fuel(fuel);
}

int main() {
  string line;
  vector<int> mass_list;

  ifstream advent1("advent1/advent1_input.txt");
  if (advent1.is_open()) {
    while(getline(advent1,line)) {
      mass_list.push_back(stoi(line));
    }
  }

  int mass_sum = 0;
  for (int mass : mass_list) mass_sum += additional_fuel(mass);
  cout << mass_sum;

  return 0;
}
