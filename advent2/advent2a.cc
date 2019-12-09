#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  string line;
  int pos {-1}, last_pos, op;
  int intcode[129];

  ifstream advent2("advent2/input.txt");
  if(advent2.is_open()) {
    getline(advent2, line);
    advent2.close();
  }

  for(int& i : intcode) {
    last_pos = pos + 1;
    pos = line.find(",", last_pos);
    i = stoi(line.substr(last_pos, (pos == -1) ? line.size() : pos - last_pos));
  }

  intcode[1] = 12;
  intcode[2] = 2;

  for(int i = 0;; i += 4) {
    op = intcode[i];
    if(op == 99) break;
    if(op == 1) intcode[intcode[i + 3]] = intcode[intcode[i + 1]] + intcode[intcode[i + 2]];
    if(op == 2) intcode[intcode[i + 3]] = intcode[intcode[i + 1]] * intcode[intcode[i + 2]];
  }

  for(int i : intcode) cout << i << " ";
  return 0;
}
