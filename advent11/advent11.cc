#include "painting_robot.hh"

int main(int argc, char **argv) {

  auto intc = ParseIntcode("input.txt");
  PaintingRobot bobby {intc}, julia {intc, 1, 1};
  //a
  cout << bobby.GetPaintedPanelCount() << endl;


  //b
  julia.PrintResult();

  return 0;
}
