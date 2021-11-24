#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <string>
#include <FL/Fl_Button.H>

using namespace std;


struct Point {
  int x, y;
};


class Candy {
  Point center;
  int w, h;
  char *candy_image;
//  bool drawn = false;
  Fl_PNG_Image *candy_m = nullptr;
  
  
 public:
  Candy(Point center, int w, int h, char *candy_image);
  void draw();

  [[nodiscard]] bool contains(Point p) const;
  Point getCenter() {
    return center;
  }
}; 