#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <iostream>
using namespace std;



struct Point {
  int x, y;
};


class Square: public Fl_Box {
//  Point center;
//  int w, h;

 public:
  Square (Fl_Boxtype b, int x, int y, int w, int h, const char *l);
  Point get_position() const;

  bool contains (Point p) const;
};