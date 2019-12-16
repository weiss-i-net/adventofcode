#include <map>
#include <array>
#include <vector>
#include "intcode.hh"

#define offset point{-50, -50}

struct point {
  int x, y;
  point& operator+= (const point & rhs) { x += rhs.x; y += rhs.y; return *this; }
};
point operator+ (const point & lhs, const point & rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }
point operator- (const point & lhs, const point & rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y}; }
bool operator== (const point & lhs, const point & rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
bool operator!= (const point & lhs, const point & rhs) { return !(lhs == rhs); }
bool operator< (const point & lhs, const point & rhs) { if (lhs.x == rhs.x) return lhs.y < rhs.y; else return lhs.x < rhs.x; }
bool operator>= (const point & lhs, const point & rhs) { return !(lhs < rhs); }
bool operator> (const point & lhs, const point & rhs) { if (lhs.x == rhs.x) return lhs.y > rhs.y; else return lhs.x > rhs.x; }
bool operator<= (const point & lhs, const point & rhs) { return !(lhs > rhs); }

class RepairDroid {
  std::map<point, short> maze_map;
  std::vector<point> curr_best_path;
  point oxygen_pos, curr_pos {offset};
  Intcode cpu;
  unsigned dir : 2 {0};
  std::map<short, point> delta {{0, {0, 1}}, {1, {1, 0}}, {2, {0, -1}}, {3, {-1, 0}}};
  std::map<short, short> inp_transl {{0, 1}, {2, 2}, {3, 3}, {1, 4}};


public:
  RepairDroid (const std::string & intcode_location)
  : cpu {intcode_location}
  {}

  int LeftWalking (const point & destin, bool in_max_mode = 0) {
    point starting_pos = curr_pos;
    bool not_moved = true;
    int cpu_out, step_count {0}, max_step {0};
    while ((curr_pos != starting_pos && curr_pos != destin) || not_moved) {
      cpu.IntInput(inp_transl[dir]); // walk forward
      cpu_out = cpu.GetLastOutput();
      if (cpu_out == 0) { // if not possible
        maze_map[curr_pos + delta[dir]] = 0; // mark forward pos wall
        ++dir; // turn right
        not_moved = true;
      } else {
        curr_pos += delta[dir];
        if (maze_map.find(curr_pos) != maze_map.end()) --step_count; // if pos was already visited --step_count
        else {
          if (cpu_out == 1)
            maze_map[curr_pos] = 1;
          else {
            maze_map[curr_pos] = 2;
            oxygen_pos = curr_pos;
          }
          ++step_count;
        }
        --dir; // turn left
        not_moved = false;
        if (step_count > max_step) max_step = step_count;
      }
    }
    return in_max_mode ? max_step : step_count;
  }

  void PrintMap () {
    auto min_x = maze_map.begin()->first.x, max_x = (--maze_map.end())->first.x, min_y = maze_map.begin()->first.y, max_y = min_y;
    for (const auto & [key, value] : maze_map) {
      if (key.y > max_y) max_y = key.y;
      else if (key.y < min_y) min_y = key.y;
    }
    std::cout << "    ";
    for (auto x = min_x; x <= max_x; ++x)
      std::cout << (x % 2 == 0
        ? std::to_string(x)
        : x + 1 > -1 && x + 1 < 10
          ? "   "
          : x + 1 < -9
            ? " "
            : "  ");
    std::cout << std::endl;
    for (auto y = max_y; y >= min_y; --y) {
      std::cout << (y > -1 && y < 10 ? "  " : (y < -9 ? "" : " ")) << y << " ";
      for (auto x = min_x; x <= max_x; ++x)
        if (point {x, y} == curr_pos) std::cout << "**";
        else std::cout << (maze_map.find({x, y}) != maze_map.end()
                          ? maze_map[{x, y}] > 0
                            ? maze_map[{x, y}] == 2
                              ? "XX"
                              : "  "
                            : "\u2592\u2592"
                          : "\u2592\u2592");
      std::cout << std::endl;
    }
    std::cout << "\nCPU Output:\n";
    for (const auto & n : cpu.GetOutput())
      std::cout << n << " ";
  }

  int MinStepsToOxygen() {
    LeftWalking({offset});
    maze_map.clear();
    return LeftWalking(oxygen_pos);
  }

  int MaxStepsFromOxygen() {
    MinStepsToOxygen();
    maze_map.clear();
    return LeftWalking(oxygen_pos, true);
  }
};

int main() {
  RepairDroid test {"input.txt"};
  //a
  std::cout << test.MinStepsToOxygen() << std::endl;

  //b
  std::cout << test.MaxStepsFromOxygen() << std::endl;

  test.PrintMap();

  return 0;
}
