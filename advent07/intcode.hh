#include <vector>
using namespace std;

class Intcode {
  int exit_code {-1}, i {0}, * arg1, * arg2, * arg3, op, inst, in_index {0};
  vector<int> intcode, input, output;

  void ParseInt() {
    inst = intcode[i];
    op = inst % 100;
    arg1 = (inst / 100 % 10) ? & intcode[i + 1] : & intcode[intcode[i + 1]];
    arg2 = (inst / 1000 % 10) ? & intcode[i + 2] : & intcode[intcode[i + 2]];
    arg3 = (inst / 10000) ? & intcode[i + 3] : & intcode[intcode[i + 3]];
  }
  void ExecIntcode() {
    input.reserve(100);
    while (true) {
      ParseInt();
      switch (op) {
        case 99:
          exit_code = 1;
          return;
        case 1:
          *arg3 = *arg1 + *arg2;
          i += 4;
          break;
        case 2:
          *arg3 = *arg1 * *arg2;
          i += 4;
          break;
        case 3:
          if (in_index == input.size()) {
            exit_code = 0;
            return;
            break;
          }
          *arg1 = input[in_index];
          in_index++;
          i += 2;
          break;
        case 4:
          output.push_back(*arg1);
          i += 2;
          break;
        case 5:
          if (*arg1 != 0)
            i = *arg2;
          else i += 3;
          break;
        case 6:
          if (*arg1 == 0)
            i = *arg2;
          else i += 3;
          break;
        case 7:
          *arg3 = (*arg1 < *arg2) ? 1 : 0;
          i += 4;
          break;
        case 8:
          *arg3 = (*arg1 == *arg2) ? 1 : 0;
          i += 4;
          break;
      }
    }
  }

public:
  Intcode() {}
  Intcode(vector<int> intcode_in)
    : intcode {intcode_in}
  { ExecIntcode(); }

  Intcode(vector<int> intcode_in, vector<int> vector_in)
    : intcode {intcode_in}
    , input {vector_in}
  { ExecIntcode(); }

  Intcode(vector<int> intcode_in, int int_in)
    : intcode {intcode_in}
    , input {int_in}
    { ExecIntcode(); }

  void IntInput(int in) {
    input.push_back(in);
    ExecIntcode();
  }

  bool IsFinished() {
    return (exit_code == 1) ? true : false;
  }
  int GetLastOutput() {
    return output.back();
  }
};
