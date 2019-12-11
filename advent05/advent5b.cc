#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void exec_intcode(vector<int> &intcode) {
  int i {0}, inst, * arg1, * arg2, * arg3, op;
  while (true) {
    inst = intcode[i];
    op = inst % 100;

    arg1 = (inst / 100 % 10) ? & intcode[i + 1] : & intcode[intcode[i + 1]];
    arg2 = (inst / 1000 % 10) ? & intcode[i + 2] : & intcode[intcode[i + 2]];
    arg3 = (inst / 10000) ? & intcode[i + 3] : & intcode[intcode[i + 3]];
/**
    int bla;
    cout << op << " " << *arg1 << " " << *arg2 << " " << *arg3 << endl;
    cin >> bla;
**/
    switch (op) {
      case 99: goto end;
      case 1: *arg3 = *arg1 + *arg2; i += 4; break;
      case 2: *arg3 = *arg1 * *arg2; i += 4; break;
      case 3: cin >> *arg1; i += 2; break;
      case 4: cout << "OUT: " << *arg1 << endl; i += 2; break;
      case 5: if (*arg1 != 0) i = *arg2; else i += 3; break;
      case 6: if (*arg1 == 0) i = *arg2; else i += 3; break;
      case 7: *arg3 = (*arg1 < *arg2) ? 1 : 0; i += 4; break;
      case 8: *arg3 = (*arg1 == *arg2) ? 1 : 0; i += 4; break;
    }
    //for (int i : intcode) cout << i << ", ";
    //cout << endl;
  }
end:;
}


int main() {
  string line;
  vector<int> intcode, curr_intcode;
  intcode.reserve(129);

  ifstream input {"input.txt"};
  while(getline(input, line, ',')) intcode.push_back(stoi(line));
  input.close();

  vector<int> test {3,9,8,9,10,9,4,9,99,-1,8};

  exec_intcode(intcode);

  return 0;
}
