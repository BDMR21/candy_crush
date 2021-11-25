#include "Candy.hpp"
#include<string.h>

Candy::Candy (Point center, int w, int h,
              std::string color) :
    center{center}, w{w}, h{h}, color{color}
{
  std::map<std::string , std::string> candy_d = {{"blue", "tile004.png",},
                                                 {"red", "tile000.png",},
                                                 {"green", "tile003.png",},
                                                 {"yellow", "tile002.png",},
                                                 {"orange", "tile001.png",},
                                                 {"purple", "tile005.png",}};

  candy_image = &candy_d.find (color)->second[0];
  candy_m = new Fl_PNG_Image (candy_image);
}

void Candy::draw ()
{
  candy_m->draw (center.x - w / 2, center.y - h / 2, w + 100, h + 100);
}

bool Candy::contains (Point p) const
{
  return p.x >= center.x - w / 2 &&
         p.x < center.x + w / 2 &&
         p.y >= center.y - h / 2 &&
         p.y < center.y + h / 2;
}