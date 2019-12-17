#include "intcode.hh"
#include "point.hh"

#include <map>

std::array<point, 2> GetDimensions(const std::map<point, short> & m) {
  auto min_x = m.begin()->first.x, max_x = (--m.end())->first.x, min_y = m.begin()->first.y, max_y = min_y;
  for (const auto & [key, value] : m) {
    if (key.y > max_y) max_y = key.y;
    else if (key.y < min_y) min_y = key.y;
  }
  return {point {min_x, min_y}, point {max_x, max_y}};
}

int main() {
  std::vector<bigint> out { Intcode {"input.txt"}.GetOutput() };
  std::map<point, short> image;

  int x {0}, y {0};
  for (const auto & i : out) {
    if (i == 10) {
      x = 0;
      ++y;
    } else {
      image[{x, y}] = i;
      ++x;
    }
  }

  auto dim = GetDimensions(image);

  int ali_sum {0};
  for (x = dim[0].x + 1; x < dim[1].x; ++x)
    for (y = dim[0].y + 1; y < dim[1].y; ++y)
      if (image [{x, y}] == 35 && image [{x + 1, y}] == 35 && image [{x - 1, y}] == 35 && image [{x, y + 1}] == 35 && image [{x, y - 1}] == 35)
        ali_sum += x * y;

  std::cout << ali_sum << std::endl;


  // A: R08 L04 R04 R10 R08  B: L12 L12 R08 R08  C: R10 R04 R04
  // A A B C B C B C C A (see output.txt)

  Intcode Horst {"input2.txt"};

  std::vector<int> in_vector;
  for (char i : "A,A,B,C,B,C,B,C,C,A\nR,8,L,4,R,4,R,10,R,8\nL,12,L,12,R,8,R,8\nR,10,R,4,R,4\nn\n")
    in_vector.push_back((int) i);
  Horst.Input(in_vector);

  for (const auto &i : Horst.GetOutput())
    std::cout << (char) i;

  std::cout << std::endl << Horst.GetLastOutput();



  return 0;
}
