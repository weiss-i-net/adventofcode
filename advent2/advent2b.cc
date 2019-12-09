#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void exec_intcode(vector<int> &intcode) {
  int i {0}, inst, mode1, mode2, mode3, op;
  while (True) {
    inst = 
    mode1 = intcode[i] / 100;
    op = intcode[i] % 100;
    if(op == 99) break;
    if(op == 1) intcode[intcode[i + 3]] = intcode[intcode[i + 1]] + intcode[intcode[i + 2]];
    if(op == 2) intcode[intcode[i + 3]] = intcode[intcode[i + 1]] * intcode[intcode[i + 2]];
  }
}


int main() {
  string line;
  vector<int> intcode, curr_intcode;
  intcode.reserve(129);

  ifstream input {"advent2/input.txt"};
  while(getline(input, line, ',')) intcode.push_back(stoi(line));
  input.close();

  for(int verb = 0; verb <= 99; verb++) for(int noun = 0; noun <= 99; noun++) {
    curr_intcode = intcode;
    curr_intcode[1] = noun;
    curr_intcode[2] = verb;
    exec_intcode(curr_intcode);
    if(curr_intcode[0] == 19690720) {
      cout << 100 * noun + verb << " ";
      break;
    }
  }

  return 0;
}
