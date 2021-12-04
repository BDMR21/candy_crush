#include <vector>
//#include <iostream>
#include "Cell.hpp"

class Canvas {
//   Text textGameOver{"Game Over", {250, 250}, 90, fl_rgb_color(255, 0, 255)};
//   Text textYouWin{"You Win!", {250, 250}, 90, FL_GREEN};
  vector<vector<Cell> > cells;
  vector<vector<string> > colors_grid;
  vector<Cell *> selected;
  vector<Cell> horizontally_aligned;
  vector<Cell> vertically_aligned;
  void check(Cell * c);
  void initialize ();
  void are_aligned(Cell c);
  void set_matrice(Cell);
 public:
  Canvas ()
  {
    initialize ();
  }

//  void draw ();   ##REUSE IF NECESSARY
  void mouseMove (Point mouseLoc);
  void cells_color();
  void mouseClick (Point mouseLoc);
  void keyPressed (int keyCode);
  void check_image(int x, int y);
};
