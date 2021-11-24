#include <vector>
#include <iostream>
#include "Rectangle.hpp"

using namespace std;


class Cell {
  Rectangle r; 
  Candy ca;
  bool bomb;
  bool visible = true;
  vector <Cell *> neighbors;
//   Text textNeighborBombCount;

  // Private methods
  int neighborBombCount();
 public:
  // Constructor
   Cell(Point center, int w, int h, char *candy_image);
   Cell(const Cell &);
//  Cell(Point center, int w, int h);

  // Methods that draw and handle events
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);

  // Used to initalize neighbors after all cells are created
  void setNeighbors(const vector <Cell *>& newNeighbors) {
    neighbors = newNeighbors;
  }

  // Getters used by Canvas to see if the game is won/lost
  [[nodiscard]] bool isBomb() const {
    return bomb;
  }
  [[nodiscard]] bool isVisible() const {
    return visible;
  }

};