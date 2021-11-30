#include "Cell.hpp"

Cell::Cell (Point center, int w, int h, string color) :
    center{center}, w{w}, h{h}, color{color}
    {
      initialize();
    }


//Cell::Cell (Cell const &c): center (c.get_center()), w(c.w), h(c.h), color(c.color)
//{}

void Cell::initialize ()
{
  std::map<std::string , std::string> candy_d = {{"blue", "tile004.png",},
                                                 {"red", "tile000.png",},
                                                 {"green", "tile003.png",},
                                                 {"yellow", "tile002.png",},
                                                 {"orange", "tile001.png",},
                                                 {"purple", "tile005.png",}};


  square= new Square(FL_UP_BOX, center.x, center.y, w, h, "");
  square->selection_color(FL_BLUE);
  file_image = &candy_d.find (color)->second[0];
  candy = new Candy(file_image);
}


void Cell::draw ()
{

  square->image(candy);

}

void Cell::mouseMove (Point mouseLoc)
{
//  cout << mouseLoc.x << " , " << mouseLoc.y << endl;
}

//void Cell::mouseClick (Point mouseLoc)
//{
//  if (square->contains (mouseLoc))
//    deleting();
//}
//void Cell::deleting ()
//{
//  square->position (200, 100);
//}
void Cell::reposition (Point p)
{
  int x = p.x;
  int y = p.y;
  square->position (x,y);
  square->color(FL_BLUE);
//  square->redraw();
}
//Point Cell::get_position ()
//{
//  return {square->x(), square->y()};
////  return {square->x (), square->y ()};
//}

void Cell::mouseClick (Point mouseLoc)
{
  if (square->contains (mouseLoc)){
      cout << "CONTAINS";
      selected = true;
  }

}
bool Cell::is_selected () const
{
  return selected;
}
void Cell::unselect ()
{
  selected = false;
}

Point Cell::get_center() const
{
  return square->get_position();
}


