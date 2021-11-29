#include <vector>
#include <iostream>
#include <map>
#include "Square.hpp"
#include "Candy.hpp"


using namespace std;

class Cell {
  Point center;
  int w, h;

  Square *square = nullptr;
  Candy *candy = nullptr;

  std::string color;
  char *file_image = {};

  vector<Cell *> neighbors;


  // Private methods
 public:
  // Constructor
  Cell (Point center, int w, int h, std::string color);
  void initialize();

  // Methods that draw and handle events
  void draw ();
  void mouseMove (Point mouseLoc);
  void mouseClick (Point mouseLoc);
  void deleting();


  // Used to initalize neighbors after all cells are created
  void setNeighbors (const vector<Cell *> &newNeighbors)
  {
    neighbors = newNeighbors;
  }

};