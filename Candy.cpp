#include "Candy.hpp"


Candy::Candy(Point center, int w, int h,
                     char *candy_image):
  center{center}, w{w}, h{h}, candy_image{candy_image} {
    candy_m = new Fl_PNG_Image (candy_image);
  }


void Candy::draw() {
  candy_m->draw(center.x - w/2 , center.y - h/2 , w+100, h+100);
}


bool Candy::contains(Point p) const {
  return p.x>=center.x-w/2 &&
         p.x<center.x+w/2 &&
         p.y>=center.y-h/2 &&
         p.y<center.y+h/2;
}