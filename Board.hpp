#include <vector>
//#include <iostream>
#include "Cell.hpp"
#include <unistd.h>

class Board {
  vector<vector<Cell*>> cells;
  vector<Cell *> selected;
  vector<vector<string>> colors_grid;
  string current_color_to_delete;

  void check (Cell *c);
  void control_generation (int x, int y);
  void gen_color_grid ();
  bool vertical_align (Cell *c);
  bool horizontal_align (Cell *c);
  void initialize ();
 public:
  Board ()
  {
    initialize ();
  }

//  void draw ();   ##REUSE IF NECESSARY
  void mouseMove (Point mouseLoc);
  void mouseClick (Point mouseLoc);
  void keyPressed (int keyCode);
  void update ();
};
