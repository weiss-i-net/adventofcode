#include "painting_robot.hh"

int main() {
  auto intc = ParseIntcode("advent11/input.txt");
  PaintingRobot bobby {intc}, julia {intc, 1};
  //a
  cout << bobby.GetPaintedPanelCount() << endl;

  //b
  julia.PrintResult();

  return 0;
}
