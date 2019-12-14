#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <array>
#define Point std::array<int,3>

Point operator+ (const Point & a, const Point & b) {
  return Point {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

class Moon {
public:
  Point pos, vel {0, 0, 0};
  Moon (const Point & point)
  : pos {point}
  {}
  void UpdateVel (const std::vector<Moon> & test) {
    for (const auto & moon : test) {
      vel = vel + Point {moon.pos[0] == pos[0] ? 0 : (moon.pos[0] > pos[0] ? 1 : -1),
                         moon.pos[1] == pos[1] ? 0 : (moon.pos[1] > pos[1] ? 1 : -1),
                         moon.pos[2] == pos[2] ? 0 : (moon.pos[2] > pos[2] ? 1 : -1)};
      //moon.vel = moon.vel + Point {moon.pos[0] == pos[0] ? 0 : moon.pos[0] > pos[0] ? -1 : 1,
      //                             moon.pos[1] == pos[1] ? 0 : moon.pos[1] > pos[1] ? -1 : 1,
      //                             moon.pos[2] == pos[2] ? 0 : moon.pos[2] > pos[2] ? -1 : 1};
    }
  }
  void UpdatePos () {
    pos = pos + vel;
  }
  int GetTotalEnergy () const {
    return (std::abs(pos[0]) + std::abs(pos[1]) + std::abs(pos[2])) * (std::abs(vel[0]) + std::abs(vel[1]) + std::abs(vel[2]));
  }
  void Print() const {
    std::cout << std::endl << "Pos: ";
    for (const auto & i : pos)
      std::cout << i << " ";
    std::cout << "   " << "Vel: ";
    for (const auto & i : vel)
      std::cout << i << " ";
  }
};

int main() {
  std::vector<Moon> moons {Point {-2,  9, -5},
                           Point {16, 19,  9},
                           Point { 0,  3,  6},
                           Point {11,  0, 11}};

  std::vector<Moon> test {Point {-1,   0,  2},
                          Point { 2, -10, -7},
                          Point { 4,  -8,  8},
                          Point { 3,   5, -1}};

  std::vector<Moon> test2 {Point {-8, -10,  0},
                           Point { 5,   5, 10},
                           Point { 2,  -7,  3},
                           Point { 9,  -8, -3}};

  auto & system = moons;

  std::vector<int> ini_x, ini_y, ini_z;
  for (auto & i : system) {
    ini_x.push_back(i.pos[0]);
    ini_x.push_back(i.vel[0]);
    ini_y.push_back(i.pos[1]);
    ini_y.push_back(i.vel[1]);
    ini_z.push_back(i.pos[2]);
    ini_z.push_back(i.vel[2]);
  }
  int done = 0;
  std::vector<int> curr_x, curr_y, curr_z;
  for (int o = 1;; ++o) {
    curr_x.clear();
    curr_y.clear();
    curr_z.clear();
    for (auto & i : system)
      i.UpdateVel(system);
    for (auto & i : system) {
      i.UpdatePos();
      curr_x.push_back(i.pos[0]);
      curr_x.push_back(i.vel[0]);
      curr_y.push_back(i.pos[1]);
      curr_y.push_back(i.vel[1]);
      curr_z.push_back(i.pos[2]);
      curr_z.push_back(i.vel[2]);
    }
    if (ini_x == curr_x) {
      //std::cout << o << std::endl;
      //break;
    }
    if (ini_y == curr_y) {
      //std::cout << o << std::endl;
      //break;
    }
    if (ini_z == curr_z) {
      std::cout << o << std::endl;
      break;
    }
  }
  // 186028 286332 96236

  //int system_energy = 0;
  //for (const auto & i : system)
  //  system_energy += i.GetTotalEnergy();

  // a
  //std::cout << system_energy << std::endl;

  // Periods: x: 186028   y: 286332   z: 96236
  std::cout << std::lcm(std::lcm(186028ll, 286332ll), 96236ll);



  return 0;
}
