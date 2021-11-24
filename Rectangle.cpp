#include "Rectangle.hpp"

Rectangle::Rectangle (Point center, int w, int h,
                      Fl_Color frameColor,
                      Fl_Color fillColor) :
    center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor}
{}

void Rectangle::draw ()
{
  fl_draw_box (FL_FLAT_BOX, center.x - w / 2, center.y - h / 2, w, h, fillColor);
  fl_draw_box (FL_BORDER_FRAME, center.x - w / 2, center.y - h / 2, w, h, frameColor);
}

void Rectangle::setFillColor (Fl_Color newFillColor)
{
  fillColor = newFillColor;
}

void Rectangle::setFrameColor (Fl_Color newFrameColor)
{
  frameColor = newFrameColor;
}

bool Rectangle::contains (Point p)
{
  return p.x >= center.x - w / 2 &&
         p.x < center.x + w / 2 &&
         p.y >= center.y - h / 2 &&
         p.y < center.y + h / 2;
}
