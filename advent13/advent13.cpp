#include "intcode.hh"
#include <unistd.h>
#include <sstream>
#include <string>
#include <array>
#include <map>
#define pixel std::array<int, 2>

std::stringstream outstream;

class Arcade {
  Intcode cpu;
  std::vector<bigint> program;
  std::map<pixel, short> screen;
  int max_x {37}, max_y {20};

  void SaveCpuOutput () {
    const std::vector<int> & cpu_output {cpu.GetOutput().begin(), cpu.GetOutput().end()};
    for (auto it {cpu_output.begin()}; it < cpu_output.end(); it += 3) {
      screen[{*it, *(it+1)}] = *(it + 2);
    }
  }

public:
  Arcade (const std::vector<bigint> & program_in, bool IsCoinInserted = false)
  : program {program_in}
  {
    if (IsCoinInserted)
      program[0] = 2;
    cpu.SetProgram(program);
    SaveCpuOutput();
  }

  int GetBlockCount () const {
    int block_count {0};
    for (const auto & [key, value] : screen)
      //outstream << x << " " << y << ": " << value << std::endl;
      if (value == 2)
        ++block_count;
    return block_count;
  }

  void PrintScreen() {
    for (int y = 0; y <= max_y; ++y) {
      for (int x = 0; x <= max_x; ++x) {
        auto dot = screen.find({x, y});
        if (dot != screen.end()) {
          short pix = dot->second;
          if (pix == 4)
            outstream << "\u2593\u2593";
          else if (pix == 3)
            outstream << "\u2591\u2591";
          else if (pix == 2)
            outstream << "\u2592\u2592";
          else if (pix == 1)
            outstream << "\u2591\u2591";
          else
            outstream << "  ";
        } else
          outstream << "  ";
      }
      outstream << std::endl;
    }
    std::cout << outstream.str();
    outstream.str(std::string());
  }

  void InputKey (char key) {
    cpu.IntInput(key == 'a' ? -1 : (key == 's' ? 0 : 1));
    SaveCpuOutput();
    PrintScreen();
  }

  void Bot () {
    while (true) {
      usleep(33333);
      pixel ball, player;
      for (int y = 0; y <= max_y; ++y)
        for (int x = 0; x <= max_x; ++x) {
          auto dot = screen.find({x, y});
          if (dot != screen.end()) {
            if (dot->second == 4)
              ball = dot->first;
            else if (dot->second == 3)
              player = dot->first;
            }
          };
      //ClearScreen();
      outstream << " Player: " << player[0] << " " << player[1] << "    Ball: " << ball[0] << " " << ball[1] << "    Score: " << screen[{-1, 0}] << std::endl;
      //if (player[0] < ball[0])
      //  InputKey('d');
      //else if (player[0] == ball[0])
      //  InputKey('s');
      //else
      //  InputKey('a');
      cpu.IntInput(ball[0] - player[0]);
      SaveCpuOutput();
      PrintScreen();
    }
  }
  void Play() {
    char in;
    std::cin >> in;
    while (true) {
      std::cin >> in;
      InputKey(in);
    }
  }
};

int main(int argc, char** argv) {
  // a
  std::cout << "Number of Blocks: " << Arcade {ParseIntcode("input.txt")}.GetBlockCount() << std::endl;

  // b
  Arcade paul {ParseIntcode("input.txt"), true};
  //paul.Bot();
  //paul.Play();

  return 0;
}
