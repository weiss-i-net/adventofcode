#include <iostream>
#include <fstream>
#include "intcode.hh"
#include "permutations.hh"
using namespace std;

#define print(a) cout << a;

int main() {

  string line;
  vector<int> intcode, curr_intcode;
  ifstream input {"advent7/input.txt"};
  while(getline(input, line, ','))
    intcode.push_back(stoi(line));
  input.close();

  //for (int i : intcode) std::cout << i << " ";

  int phase_settings[] {0, 1, 2, 3, 4};
  int* phase_perm = permutations(phase_settings, 5);
  int perm_count = fac(5);

//a
  int out, max_out = 0;
  for (int perm = 0; perm < perm_count; perm++) {
    out = 0;
    for (int i {0}; i < 5; i++)
       out = Intcode (intcode, vector<int> {phase_perm[5 * perm + i], out}).GetLastOutput();
    if (out > max_out) max_out = out;
  }
  cout << max_out << endl;

//b
  int phase_settings_b[] {5, 6, 7, 8, 9};
  phase_perm = permutations(phase_settings_b , 5);

  vector<int> test {3, 52, 1001, 52, -5, 52, 3, 53, 1, 52, 56, 54, 1007, 54, 5, 55, 1005, 55, 26, 1001, 54, -5, 54, 1105, 1, 12, 1,  53, 54, 53, 1008, 54, 0, 55, 1001, 55, 1, 55, 2, 53, 55, 53, 4, 53, 1001, 56, -1, 56, 1005, 56, 6, 99, 0, 0, 0, 0, 10};

  max_out = 0;
  for (int perm = 0; perm < perm_count; perm++) {
    vector<Intcode> amps (5);
    for (int i {0}; i < 5; i++)
      amps[i] = Intcode (intcode, phase_perm[5 * perm + i]);
    amps[0].IntInput(0);
    for (int o {0};; o++) {
        amps[(o + 1) % 5].IntInput(amps[o % 5].GetLastOutput());
        if (amps[4].IsFinished()) {
          out = amps[(o + 1) % 5].GetLastOutput();
          break;
        }
    }
    if (out > max_out) {max_out = out;
    }
  }
  cout << max_out << endl;

  return 0;
}
