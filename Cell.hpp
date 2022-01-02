#include <vector>
#include <iostream>
#include <map>
#include <mutex>
#include <unistd.h>
#include "Square.hpp"
#include "Candy.hpp"

using namespace std;

class Cell {
  Point center;
  int w, h;
  bool selected = false;

  Square *square = nullptr;
  Candy *candy = nullptr;

  std::string color;
  char *file_image = {};

  vector<Cell *> neighbors;
  std::map<std::string, std::string> candy_d;


  // Private methods
 public:
  // Constructor
  Cell (Point center, int w, int h, std::string color);
  void initialize ();

  // Methods that draw and handle events
//  void draw ();
  void mouseMove (Point mouseLoc);
  void mouseClick (Point mouseLoc);
  [[nodiscard]] bool is_selected () const;
  void select ();
  void unselect ();
  string get_color ();
  void reposition (Point p);
  [[nodiscard]] Point get_center () const;

  // Used to initalize neighbors after all cells are created
  void setNeighbors (const vector<Cell *> &newNeighbors);
  void myNeighbors (Cell *c);

  vector<Cell *> get_Neighbors ();

  bool is_neighbor (Cell *cell) const;
  void destroy();

};