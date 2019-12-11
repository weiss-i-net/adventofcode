#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main() {
  string line;
  int op;
  vector<int> intcode;

  ifstream input {"advent2/input.txt"};
  while(getline(input, line, ',')) intcode.push_back(stoi(line));
  input.close();

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
