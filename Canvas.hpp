#include <vector>
//#include <iostream>
#include "Cell.hpp"

class Canvas {
//   Text textGameOver{"Game Over", {250, 250}, 90, fl_rgb_color(255, 0, 255)};
//   Text textYouWin{"You Win!", {250, 250}, 90, FL_GREEN};
  vector<vector<Cell> > cells;
  vector<Cell *> selected;
  void check(Cell * c);
  void initialize ();
 public:
  Canvas ()
  {
    initialize ();
  }

//  void draw ();   ##REUSE IF NECESSARY
  void mouseMove (Point mouseLoc);
  void mouseClick (Point mouseLoc);
  void keyPressed (int keyCode);
};
