#include <vector>
#include <iostream>
#include <map>
#include <memory>
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
  std::map<std::string , std::string> candy_d;


  // Private methods
 public:
  // Constructor
  Cell (Point center, int w, int h, std::string color);
  // Cell (Cell const &c){
  //   center.x = c.center.x;
  //   center.y = c.center.y;
  //   color = c.color;
  //   w = c.w;
  //   h = c.h;
  // };
  //Cell() = default;
  ~Cell(){};
  void initialize();
  string get_color();
  void set_color(string new_color);

  // Methods that draw and handle events
  void draw ();
  void mouseMove (Point mouseLoc);
  void mouseClick(Point mouseLoc);
  bool is_selected() const;
  void unselect();
//  void mouseClick (Point mouseLoc);
//  void deleting();
  void reposition(Point p);
  Point get_center() const;
  void set_center(Point new_center);


  // Used to initalize neighbors after all cells are created
  void setNeighbors (const vector<Cell *> &newNeighbors);
  void myNeighbors(Cell * c);

  vector<Cell *> get_Neighbors();

  bool is_neighbor(Cell * cell) const;
  void destroy();

};