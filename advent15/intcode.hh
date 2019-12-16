#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <cassert>
#define bigint __int128

std::ostream& operator<<(std::ostream& os, const __int128 i) noexcept { // Overloading << for gccs __int128
  std::ostream::sentry s(os);
  if (s) {
    unsigned __int128 tmp = i < 0 ? -i : i;
    char buffer[128];
    char *d = std::end(buffer);
    do {
      --d;
      *d = "0123456789"[tmp % 10];
      tmp /= 10;
    } while (tmp != 0);
    if (i < 0) {
      --d;
      *d = '-';
    }
    int len = std::end(buffer) - d;
    if (os.rdbuf()->sputn(d, len) != len) {
      os.setstate(std::ios_base::badbit);
    }
  }
  return os;
}

std::vector<bigint> ParseIntcode(std::string in) {
  std::string line;
  std::vector<bigint> intcode;
  std::ifstream input {in};
  assert(input.is_open());
  while(getline(input, line, ','))
    intcode.push_back(stol(line));
  input.close();
  return intcode;
}

class Intcode {
  int exit_code {-1}, i {0}, op, in_index {0}, rel_base {0};
  bigint inst;
  size_t arg1, arg2, arg3;
  std::vector<bigint> intcode, input, output;

  void print_intcode() { // for debugging
    std::cout << "Intcode: ";
    for (auto i : intcode)
      std::cout << i << " ";
    std::cout << std::endl;
  }

  size_t arg_mode(int arg_num) {
    int mode = inst / int(pow(10, arg_num + 1)) % 10;
    size_t index;
    switch (mode) {
      case 0:
        index = intcode[i + arg_num];
        break;
      case 1:
        index = i + arg_num;
        break;
      case 2:
        index = intcode[i + arg_num] + rel_base;
        break;
    }

    if (index >= intcode.size())
      intcode.resize(index * 2, 0);
    //cout << "i: " << i << " Inst: " << inst << " Arg: " << arg_num << " Mode: " << mode << " Index: " << index << " intcode[index]: " << intcode[index] << endl;
    return index;
  }

  void ExecIntcode() {
    while (true) {
      inst = intcode[i];
      op = inst % 100;

      if (op != 99)
        arg1 = arg_mode(1);
      if ((5 <= op && op <= 8) || op <= 2)
        arg2 = arg_mode(2);
      if (op == 7 || op == 8 || op <= 2)
        arg3 = arg_mode(3);

      switch (op) {
        case 99: //end
          exit_code = 1;
          return;
        case 1: //add
          intcode[arg3] = intcode[arg1] + intcode[arg2];
          //cout << "Adding " << arg1 << ": " << intcode[arg1] << " " << arg2 << ": " << intcode[arg2] << " to " << arg3 << endl;
          i += 4;
          break;
        case 2: //multiply
          intcode[arg3] = intcode[arg1] * intcode[arg2];
          //cout << "Multiplying " << arg1 << ": " << intcode[arg1] << " " << arg2 << ": " << intcode[arg2] << " to " << arg3 << endl;
          i += 4;
          break;
        case 3: //input
          //for (auto i : intcode)
          //  cout << i << " ";
          //cout << endl << i << input.back() << endl;
          if (in_index == (int) input.size()) {
            exit_code = 0;
            return;
          }
          intcode[arg1] = input[in_index];
          in_index++;
          i += 2;
          break;
        case 4: //output
          output.push_back(intcode[arg1]);
          i += 2;
          break;
        case 5: //jump if true
          if (intcode[arg1] != 0)
            i = intcode[arg2];
          else i += 3;
          break;
        case 6: //jump if false
          if (intcode[arg1] == 0)
            i = intcode[arg2];
          else i += 3;
          break;
        case 7: //is smaller
          intcode[arg3] = (intcode[arg1] < intcode[arg2]) ? 1 : 0;
          i += 4;
          break;
        case 8: //is equal
          intcode[arg3] = (intcode[arg1] == intcode[arg2]) ? 1 : 0;
          i += 4;
          break;
        case 9: //rel. base offset
          rel_base += intcode[arg1];
          i += 2;
          //cout << "New rel_base = " << rel_base << endl;
          break;
      }
    }
  }

public:
  Intcode() {}

  Intcode(const std::string & intcode_in)
    : intcode {ParseIntcode(intcode_in)}
  { ExecIntcode(); }

  Intcode(const std::vector<bigint> & intcode_in)
    : intcode {intcode_in}
  { ExecIntcode(); }

  Intcode(const std::vector<int> & intcode_in)
    : intcode {intcode_in.begin(), intcode_in.end()}
  { ExecIntcode(); }

  Intcode(const std::vector<bigint> & intcode_in, int int_in)
    : intcode {intcode_in}
    , input {int_in}
  { ExecIntcode(); }

  Intcode(const std::vector<bigint> & intcode_in, const std::vector<bigint> & vector_in)
    : intcode {intcode_in}
    , input {vector_in}
  { ExecIntcode(); }

  void SetProgram (const std::vector<bigint> program_in) {
    exit_code = -1;
    i = 0;
    in_index = 0;
    rel_base = 0;
    input.clear();
    output.clear();
    intcode.assign(program_in.begin(), program_in.end());
    ExecIntcode();
  }

  void IntInput(int in) {
    input.push_back(in);
    ExecIntcode();
  }
  bool IsFinished() {
    return (exit_code == 1) ? true : false;
  }
  const std::vector<bigint> & GetOutput() {
    return output;
  }
  const bigint & GetLastOutput() {
    return output.back();
  }
};
