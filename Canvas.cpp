#include "Canvas.hpp"

void Canvas::initialize ()
{
  // This is called by the constructor but also by keyPressed to
  // reset whenver spacebar is called.

  // Until the last step when we needed to reset, this would be the constructor

//  cells.clear (); // Needed to remove the cells if we are starting again

  for (int x = 0; x < 9; x++)
  {
    cells.emplace_back ();
    for (int y = 0; y < 9; y++)
      {
        std::vector <string> color_vect {"blue", "red", "orange", "yellow", "green", "purple"};
        std::string color = color_vect[rand() % color_vect.size()];

        cells[x].push_back ({{80 * x, 80 * y}, 80, 80, color});
      }
  }

  // This computes the (pointers to) neighbors of each cell
  for (int x = 0; x < 9; x++)
    for (int y = 0; y < 9; y++)
    {
      vector<Cell *> neighbors;
      for (auto &shift: vector<Point> ({
                                           {-1, 0}, // The 4 neighbors relative to the cell
                                           {0, 1},
                                           {1, 0},
                                           {0, -1},
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


//##REUSE IF NECESSARY
//void Canvas::draw ()
//{
//  for (auto &v: cells)
//    for (auto &c: v)
//      {
//        c.draw ();
//      }
//}

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
      {
        c.mouseClick (mouseLoc);
        check(&c);
      }
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


void Canvas::check (Cell * c)
{
    if (c->is_selected()){
      selected.push_back (c);
      c->unselect();
    }

    if ((selected.size() == 2) && (selected[0]->is_neighbor (selected[1]))){
        Point save_center{selected[0]->get_center().x, selected[0]->get_center().y};
        selected[0]->reposition(selected[1]->get_center());
        selected[1]->reposition(save_center);

        vector<Cell *> save_neighbors0 = selected[0]->get_Neighbors();
        vector<Cell *> save_neighbors1 = selected[1]->get_Neighbors();

        save_neighbors0.push_back (selected[0]);
        save_neighbors0.erase (remove (save_neighbors0.begin(), save_neighbors0.end(), selected[1]), save_neighbors0.end());

        save_neighbors1.push_back (selected[1]);
        save_neighbors1.erase (remove (save_neighbors1.begin(), save_neighbors1.end(), selected[0]), save_neighbors1.end());

        selected[0]->setNeighbors (save_neighbors1);
        selected[1]->setNeighbors (save_neighbors0);

        selected[0]->myNeighbors (selected[1]);
        selected[1]->myNeighbors (selected[0]);

        selected.clear();

    }
    else if ((selected.size() == 2) && (!selected[0]->is_neighbor (selected[1]))){
      selected.clear();
    }
}
