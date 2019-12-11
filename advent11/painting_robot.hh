#include "intcode.hh"
#include <map>
#include <array>
#include <algorithm>
#include <stdlib.h>
#include <utility>

class Direction {
  unsigned int direction : 2 {0};
public:
  void SetDir(int i) {
    direction = i % 4;
  }
  array<int, 2> GetDir() {
    switch (direction) {
      case 0: return {0, 1};
      case 1: return {1, 0};
      case 2: return {0, -1};
      case 3: return {-1, 0};
    }
    return {0, 0};
  }
  array<int, 2> Turn(bool turn_right) {
    direction = (turn_right ? direction + 5 : direction + 3) % 4;
    return GetDir();
  }
};

class PaintingRobot {
  Intcode computer;
  map<array<int, 2>, int> panels;
  array<int, 2> curr_pos {0, 0};
  Direction dir;

  int GetCurrPanel() {
    if (panels.find(curr_pos) == panels.end())
      panels[curr_pos] = 0;
    return panels[curr_pos];
  }
  void RunRobot() {
    while (!computer.IsFinished()) {
      computer.IntInput(GetCurrPanel());
      panels[curr_pos] = *(++computer.GetOutput().rbegin());
      array<int, 2>  move = dir.Turn(computer.GetLastOutput());
      std::transform(curr_pos.begin(), curr_pos.end(), move.begin(), curr_pos.begin(), std::plus<int>());
    }
  }

public:
  PaintingRobot (const vector<bigint> & int_programm, int colour = 0)
    : computer(int_programm)
    , panels {{{0, 0}, colour}} {
    RunRobot();
    //for (auto&& [key, value] : panels)
    //  cout << key[0] << " " << key[1] << endl;
  }

  int GetPaintedPanelCount() {
    return panels.size();
  }

  void PrintResult() {
    const auto& [minx, miny] = panels.begin()->first;
    const auto& [maxx, maxy] = panels.rbegin()->first;
    for (int y = 0; y >= -5; --y) {
      for (int x = minx; x <= maxx; ++x) {
        auto pixel = panels.find({x, y});
        cout << (pixel == panels.end() ? "  " : (pixel->second ? "\u2592\u2592" : "  "));
        }
      cout << endl;
    }
  }
};
