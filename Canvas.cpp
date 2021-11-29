#include "Canvas.hpp"

void Canvas::initialize ()
{
  // This is called by the constructor but also by keyPressed to
  // reset whenver spacebar is called.

  // Until the last step when we needed to reset, this would be the constructor

  cells.clear (); // Needed to remove the cells if we are starting again

  for (int x = 0; x < 9; x++)
    {
      cells.emplace_back ();
      for (int y = 0; y < 9; y++)
        {
//          char candy_img[] = "./png/tile001.png";
          std::vector <string> color_vect {"blue", "red", "orange", "yellow", "green", "purple"};
          std::string color = color_vect[rand() % color_vect.size()];

          cells[x].push_back ({{75 * x + 80, 75 * y + 80}, 75, 75, color});
        }
    }

  // This computes the (pointers to) neighbors of each cell
  for (int x = 0; x < 9; x++)
    for (int y = 0; y < 9; y++)
      {
        vector<Cell *> neighbors;
        for (auto &shift: vector<Point> ({
                                             {-1, 0}, // The 8 neighbors relative to the cell
                                             {-1, 1},
                                             {0, 1},
                                             {1, 1},
                                             {1, 0},
                                             {1, -1},
                                             {0, -1},
                                             {-1, -1},
                                         }))
          {
            int neighborx = x + shift.x;
            int neighbory = y + shift.y;
            if (neighborx >= 0 && // Check if the indicies are in range
                neighbory >= 0 &&
                neighborx < static_cast<int>(cells.size ()) &&
                neighbory < static_cast<int >(cells[neighborx].size ()))
              neighbors.push_back (&cells[neighborx][neighbory]);
            cells[x][y].setNeighbors (neighbors);
          }
      }
}

void Canvas::draw ()
{
  for (auto &v: cells)
    for (auto &c: v)
      {
        c.draw ();
      }
}

void Canvas::mouseMove (Point mouseLoc)
{
  for (auto &v: cells)
    for (auto &c: v)
      c.mouseMove (mouseLoc);
}

void Canvas::mouseClick (Point mouseLoc)
{
  for (auto &v: cells)
    for (auto &c: v)
      c.mouseClick(mouseLoc);
}

void Canvas::keyPressed (int keyCode)
{
  switch (keyCode)
    {
      case ' ':initialize ();
      break;
      case 'q':exit (0);
    }
}
vector<Cell *> Canvas::neighbors (int x, int y)
{
  return vector<Cell *> ();
}
