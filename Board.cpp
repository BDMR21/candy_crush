#include "Board.hpp"

void Board::control_generation (int x, int y)
{
  string color = colors_grid[x][y];
  int col = 0;
  int row = 0;
  std::vector<string> color_vect{"blue", "red", "orange", "yellow", "green", "purple"};
  std::string new_color = color;

  // horizontal vers la droite
  int i = x + 1;
  while (i < 9 && color == colors_grid[i][y])
    {
      col++;
      i++;
    }

  // horizontal vers la gauche
  i = x;
  while (i >= 0 && color == colors_grid[i][y])
    {
      col++;
      i--;
    }

  // vertical vers le haut
  int j = y + 1;
  while (j < 9 && color == colors_grid[x][j])
    {
      row++;
      j++;
    }

  // vertical vers le bas
  j = y;
  while (j >= 0 && color == colors_grid[x][j])
    {
      if (color == colors_grid[x][j])
        {
          row++;
          j--;
        }
    }

  if (col > 2 || row > 2)
    {
      while (color == new_color)
        new_color = color_vect[rand () % color_vect.size ()];
      colors_grid[x][y] = new_color;
    }

}

void Board::gen_color_grid ()
{
  for (int i = 0; i < 9; i++)
    {
      colors_grid.emplace_back ();
      for (int j = 0; j < 9; j++)
        {
          std::vector<string> color_vect{"blue", "red", "orange", "yellow", "green", "purple"};
          std::string color = color_vect[rand () % color_vect.size ()];
          colors_grid[i].push_back (color);
        }
    }

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      control_generation (i, j);
}

void Board::initialize ()
{
  gen_color_grid (); //matrix of color for building board

  for (int x = 0; x < 9; x++)
    {
      cells.emplace_back ();
      for (int y = 0; y < 9; y++)
        {
          std::string color = colors_grid[x][y];
          auto p_cell = new Cell ({80 * x, 80 * y}, 80, 80, color);
          cells[x].push_back (p_cell);
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
              neighbors.push_back (cells[neighborx][neighbory]);
            cells[x][y]->setNeighbors (neighbors);
          }
      }
}


//##REUSE IF NECESSARY
//void Board::draw ()
//{
//  for (auto &v: cells)
//    for (auto &c: v)
//      {
//        c.draw ();
//      }
//}

void Board::mouseMove (Point mouseLoc)
{
  for (const auto& v: cells)
    for (auto c: v)
      if (c)
        c->mouseMove (mouseLoc);
}

void Board::mouseClick (Point mouseLoc)
{
  for (const auto &v: cells)
    for (auto c: v)
      {
        if (c)
          {
            c->mouseClick (mouseLoc);
            check (c);
          }
      }
}

void Board::keyPressed (int keyCode)
{
  switch (keyCode)
    {
      case ' ':initialize ();
      break;
      case 'q':exit (0);
    }
}

bool Board::vertical_align (Cell *c)
{
  int v_align = 1;
  int j = c->get_center ().y / 80 + 1;


  // vertical vers le haut
  while (j < 9 && cells[c->get_center ().x / 80][j]->get_color () == c->get_color ())
    {
      if (!cells[c->get_center ().x / 80][j]->is_selected())
        {
          cells[c->get_center ().x / 80][j]->select ();
//          printf ("%s", cells[c->get_center ().x / 80][j]->get_color ().c_str ());
          v_align++;
          j++;
        }
    }

  // vertical vers le bas
  j = c->get_center ().y / 80 - 1;
  while (j >= 0 && cells[c->get_center ().x / 80][j]->get_color () == c->get_color ())
    {
      if (!cells[c->get_center ().x / 80][j]->is_selected())
        {
          cells[c->get_center ().x / 80][j]->select ();
//          printf ("%s", cells[c->get_center ().x / 80][j]->get_color ().c_str ());
          v_align++;
          j--;
        }
    }

  if (v_align > 2)
    {
      c->select();
      current_color_to_delete = c->get_color();
    }

  return v_align > 2;
}

bool Board::horizontal_align (Cell *c)
{
  int h_align = 1;
  int i = c->get_center ().x / 80 + 1;

  // horizontal vers la droite
  while (i < 9 && cells[i][c->get_center ().y / 80]->get_color () == c->get_color ())
    {
      if (!cells[i][c->get_center ().y / 80]->is_selected())
        {
          cells[i][c->get_center ().y / 80]->select ();
//          printf ("%s", cells[i][c->get_center ().y / 80]->get_color ().c_str ());
          h_align++;
          i++;
        }
    }


  // horizontal vers la gauche
  i = c->get_center ().y / 80 - 1;
  while (i >= 0 && cells[i][c->get_center ().y / 80]->get_color () == c->get_color ())
    {
      if (!cells[i][c->get_center ().y / 80]->is_selected())
        {
          cells[i][c->get_center ().y / 80]->select ();
//          printf ("%s", cells[i][c->get_center ().y / 80]->get_color ().c_str ());
          h_align++;
          i--;
        }
    }

  if (h_align > 2)
    {
      c->select();
      current_color_to_delete = c->get_color();
    }

  return h_align > 2;
}

void Board::update ()
{
  auto center_0 = selected[0]->get_center ();
  auto center_1 = selected[1]->get_center ();

  selected[0]->reposition (center_1);
  selected[1]->reposition (center_0);

  vector<Cell *> save_neighbors0 = selected[0]->get_Neighbors ();
  vector<Cell *> save_neighbors1 = selected[1]->get_Neighbors ();

  replace (save_neighbors0.begin (), save_neighbors0.end (), selected[1], selected[0]);
  replace (save_neighbors1.begin (), save_neighbors1.end (), selected[0], selected[1]);

  selected[0]->setNeighbors (save_neighbors1);
  selected[1]->setNeighbors (save_neighbors0);

  selected[0]->myNeighbors (selected[1]);
  selected[1]->myNeighbors (selected[0]);

}

void Board::check (Cell *c)
{
  if (c->is_selected ())
    {
      if (find (selected.begin (), selected.end (), c) == selected.end ())
        selected.push_back (c);
      c->unselect ();
    }

  if ((selected.size () == 2) && (selected[0]->is_neighbor (selected[1])))
    {
      update ();

      if (vertical_align (selected[0]) || horizontal_align (selected[0]) ||
          vertical_align (selected[1]) || horizontal_align (selected[1]))
        {
          for (int x = 0; x < 9; x++)
            for (int y = 0; y < 9; y++)
              {
                if (cells[x][y]->is_selected () && cells[x][y]->get_color() == current_color_to_delete)
                  {
                    cells[x][y]->unselect ();

//                    cells[x][y]->reposition ({1000, 1000});
                    printf ("before: %s", cells[x][y]->get_color().c_str());
                    cells[x][y]->destroy();
                    printf ("after: %s", cells[x][y]->get_color().c_str());

                  }
              }
        }
//      else
//        {
//          printf ("waiting...\n");
//          sleep (2);
//          update ();
//        }

      selected.clear ();
      current_color_to_delete = "";

    }
  else if ((selected.size () == 2) && (!selected[0]->is_neighbor (selected[1])))
    {
      selected.clear ();
    }
}

