#include "Square.hpp"

Square::Square (Fl_Boxtype b, int x, int y, int w, int h, const char *l) :
    Fl_Box (b, x, y, w, h, l), center{x, y}, w{w}, h{h}{}



bool Square::contains (Point p) const
{
  return p.x >= center.x - w / 2 &&
         p.x < center.x + w / 2 &&
         p.y >= center.y - h / 2 &&
         p.y < center.y + h / 2;
}
