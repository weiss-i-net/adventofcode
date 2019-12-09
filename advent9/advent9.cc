#include <iostream>
#include <fstream>
#include <string>
#include "intcode.hh"
using namespace std;

int main() {
  string line;
  vector<bigint> intcode;
  ifstream input {"input.txt"};
  while(getline(input, line, ','))
    intcode.push_back(stoi(line));
  input.close();
//                                  0   1    2    3   4   5    6    7  8    9  10 11 12   13  14  15
//Intcode a (std::vector<bigint> {109, -1, 22202, 10, 11, 12, 1105, 1, 13, 10, 10, 0, 0, 204, 12, 99});
  Intcode a (intcode, 2);
  for(bigint i : a.GetOutput())
    cout << i << " ";
  cout << endl;
  return 0;
}
