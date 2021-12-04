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
  square->color(fl_rgb_color(200, 200, 200));
  file_image = &candy_d.find (color)->second[0];
  candy = new Candy(file_image);
  square->image(candy);
}


//void Cell::draw ()
//{
//
//}

string Cell::get_color(){
  return color;
}

void Cell ::set_color(string new_color){
  color = new_color;
}

void Cell ::set_center(Point new_center){
  center.x = new_center.x;
  center.y = new_center.y;
}

void Cell::mouseMove (Point mouseLoc)
{
  if (square->contains(mouseLoc)) {
      square->color(fl_rgb_color(255, 102, 102));
    } else {
      square->color(fl_rgb_color(200, 200, 200));
    }
}


void Cell::mouseClick (Point mouseLoc)
{
  if ((square->contains (mouseLoc)))
      selected = true;
}


void Cell::reposition (Point p)
{
  int x = p.x;
  int y = p.y;
  square->position (x,y);
  square->redraw();
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
  return center;
}


bool Cell::is_neighbor (Cell * cell) const
{
  return find (neighbors.begin(), neighbors.end(), cell) != neighbors.end();
}


void Cell::setNeighbors (const vector<Cell *> &newNeighbors)
{
  neighbors = newNeighbors;
}
vector<Cell *> Cell::get_Neighbors ()
{
  return neighbors;
}
void Cell::myNeighbors (Cell *c)
{
  for (auto &neighbor : neighbors)
    {
      auto n_tochange = neighbor->get_Neighbors();
      std::replace(n_tochange.begin(), n_tochange.end(), c, this);
      neighbor->setNeighbors (n_tochange);
    }

}
string Cell::get_color () const
{
  return color;
}
Cell::~Cell ()
{
  cout << "destruct" << endl;
}


