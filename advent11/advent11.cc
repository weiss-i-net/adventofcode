#include "painting_robot.hh"

int main(int argc, char **argv) {

  auto intc = ParseIntcode("input.txt");
  PaintingRobot bobby {intc}, julia {intc, 1, 1};
  //a
  std::cout << bobby.GetPaintedPanelCount() << std::endl;


  //b
  julia.PrintResult();

  return 0;
}
