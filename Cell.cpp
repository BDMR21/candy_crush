#include "Cell.hpp"

// , const char candy_image
Cell::Cell (Point center, int w, int h, std::string color) :
    r (center, w, h, FL_BLACK, FL_WHITE),
    ca (center, w, h, color),
    bomb{rand () % 8 == 0}
{}
// textNeighborBombCount("", center, h/2)

Cell::Cell (const Cell &c) :
    r{c.r}, ca{c.ca}, bomb{rand () % 8 == 0}
{}

void Cell::draw ()
{
  r.setFillColor (FL_WHITE);
  r.draw ();
  ca.draw ();
  // textNeighborBombCount.setString(to_string(neighborBombCount()));
  // textNeighborBombCount.draw();

}

void Cell::mouseMove (Point mouseLoc)
{
  if (r.contains (mouseLoc))
    {
      r.setFrameColor (FL_RED);
    }
  else
    {
      r.setFrameColor (FL_BLACK);
    }
}

void Cell::mouseClick (Point mouseLoc)
{
  if (r.contains (mouseLoc))
    {
      // makeVisible();
    }
}

int Cell::neighborBombCount ()
{
  int bombCount = 0;
  for (auto &neighbor: neighbors)
    if (neighbor->isBomb ())
      bombCount++;
  return bombCount;
}

