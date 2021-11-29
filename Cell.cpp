#include "Cell.hpp"

Cell::Cell (Point center, int w, int h, string color) :
    center{center}, w{w}, h{h}, color{color}
    {
      initialize();
    }

void Cell::initialize ()
{
  std::map<std::string , std::string> candy_d = {{"blue", "tile004.png",},
                                                 {"red", "tile000.png",},
                                                 {"green", "tile003.png",},
                                                 {"yellow", "tile002.png",},
                                                 {"orange", "tile001.png",},
                                                 {"purple", "tile005.png",}};


  square= new Square(FL_BORDER_BOX, center.x, center.y, w, h, "");
  file_image = &candy_d.find (color)->second[0];
  candy = new Candy(file_image);
}


void Cell::draw ()
{

  square->image(candy);

}

void Cell::mouseMove (Point mouseLoc)
{

}

void Cell::mouseClick (Point mouseLoc)
{
  if (square->contains (mouseLoc))
    deleting();
}
void Cell::deleting ()
{
  square->position (200, 100);
}

