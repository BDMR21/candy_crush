#include "Canvas.hpp"
#include <unistd.h>
#include <algorithm>

void Canvas::check_image(int x, int y){
  string color = colors_grid[x][y];
  int col = 0;
  int row = 0;
  std::vector <string> color_vect {"blue", "red", "orange", "yellow", "green", "purple"};
  std::string new_color = color;
  // horizontal vers la droite
  int i = x+1;
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
  int j = y+1;
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
    {
      new_color = color_vect[rand() % color_vect.size()];
    } 
  }
  if (new_color != color)
  {
    colors_grid[x][y] = new_color;
  }
  
}

void Canvas::cells_color(){
  for (int i = 0; i < 9; i++)
  {
    colors_grid.emplace_back ();
    for (int j = 0; j < 9; j++)
    {
      std::vector <string> color_vect {"blue", "red", "orange", "yellow", "green", "purple"};
      std::string color = color_vect[rand() % color_vect.size()];
      colors_grid[i].push_back(color);
    }}
    
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      check_image(i, j);
    }
  }
}

void Canvas::initialize ()
{
  cells_color();
  
  for (int x = 0; x < 9; x++)
  {
    cells.emplace_back ();
    for (int y = 0; y < 9; y++)
      {
        std::string color = colors_grid[x][y];
        
        cells[x].push_back ({{x * 80, y * 80}, 80, 80, color});
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

void Canvas::set_matrice(Cell c){
  int i = c.get_center().x/80;
  int j = c.get_center().y/80;
  cells[i][j] = c;
}

bool Canvas::are_aligned(Cell c){
  horizontally_aligned.push_back(c);
  vertically_aligned.push_back(c);
  int i = c.get_center().x/80;
  int j = c.get_center().y/80;
  string color_c = c.get_color();
  vector<Cell> horizontal_cells = cells[i];
  bool res = false;


  // vertical vers le haut
  j++;
  while (j < 9 && cells[i][j].get_color() == c.get_color())
  {
    vertically_aligned.push_back(cells[i][j]);
    j++;
  }
  j = c.get_center().y/80;

  // vertical vers le bas
  j--;
  while (j >= 0 && cells[i][j].get_color() == c.get_color())
  {
    vertically_aligned.push_back(cells[i][j]);
    j--;
  }

  j = c.get_center().y/80;
  // horizontal vers la droite
  i++;
  while (i < 9 && cells[i][j].get_color() == c.get_color())
  {
    horizontally_aligned.push_back(cells[i][j]);
    i++;
  }
  i = c.get_center().x/80;

  // horizontal vers la gauche
  i--;
  while (i >= 0 && cells[i][j].get_color() == c.get_color())
  {
    horizontally_aligned.push_back(cells[i][j]);
    i--;
  }

  return horizontally_aligned.size() >= 3 || vertically_aligned.size() >= 3;
  
}


void Canvas::delete_alignment(){
  int tmp = 0;
  vector<Cell> empty;
  vector<Point> points;
  if (vertically_aligned.size() >= 3)   // vertical
  {
    //cout << "v" << endl;
    for (int x = 0; x < vertically_aligned.size(); x++){
      int x_ = vertically_aligned[x].get_center().x;
      int y_ = vertically_aligned[x].get_center().y;
      // Cell *pointer = new Cell(cells[x_][y_]);
      // delete pointer;
      points.push_back({x_, y_});
      x_ = x_/80;
      y_ = y_/80;
      tmp = x_;
      cells[x_][y_].destroy();
      //cells[x_][y_].reposition({1000, 1000});
      cells[x_][y_].set_color("");
    }

    for (int i = 0; i < 9; i++)
    {
      if (cells[tmp][i].get_color() != ""){
        empty.push_back(cells[tmp][i]);
        cout << cells[tmp][i].get_color() << endl;
        cout << points.size() << endl;
      }
        //empty.push_back(cells[tmp][i]);  //vertically_aligned.pop_back();  //cout << cells[tmp][i].get_color() << endl;
      else
        break;
    }
    cout << "> " << empty.size() << endl;
    int k = empty.size();
    int t = 0;
    for (int i = 9; i > 0; i--)
    {
      if (cells[tmp][i-1].get_color() == "" && k > 0){
        //auto a = *min_element(points.begin(), points.end());
        empty[k-1].reposition(points[t]);
        empty[k-1].set_color("");
        k--;
        t++;
      }
    }
  }

  if (horizontally_aligned.size() >= 3)
  { 
    //cout << "h" << endl;
    for (int x = 0; x < horizontally_aligned.size(); x++){
      int x_ = horizontally_aligned[x].get_center().x;
      int y_ = horizontally_aligned[x].get_center().y;
      // Cell *pointer = new Cell(cells[x_][y_]);
      // delete pointer;
      points.push_back({x_, y_});
      x_ = x_/80;
      y_ = y_/80;
      tmp = x_;
      cells[x_][y_].destroy();
      //cells[x_][y_].reposition({1000, 1000});
      //cells[x_][y_].set_color("");
    }

    // for (int i = 0; i < 9; i++)
    // {
    //   if (cells[tmp][i].get_color() != ""){
    //     empty.push_back(cells[tmp][i]);
    //     cout << cells[tmp][i].get_color() << endl;
    //     cout << points.size() << endl;
    //   }
    //     //empty.push_back(cells[tmp][i]);  //vertically_aligned.pop_back();  //cout << cells[tmp][i].get_color() << endl;
    //   else
    //     break;
    // }
    // int k = 0;
    // for (int i = 0; i < 9; i++)
    // {
    //   if (cells[tmp][i].get_color() == "" && k < empty.size()){
    //     //auto a = *min_element(points.begin(), points.end());
    //     empty[k].reposition(points[k]);
    //     empty[k].set_color("");
    //     k++;
    //   }
    // }

  }    
  horizontally_aligned.clear();
  vertically_aligned.clear();
}

void Canvas::check (Cell * c)
{ 
    if (c->is_selected()){
      selected.push_back (c);
      c->unselect();
    }

    if ((selected.size() == 2) && (selected[0]->is_neighbor (selected[1]))){
        Point save_center{selected[0]->get_center().x, selected[0]->get_center().y};
        string save_color = selected[0]->get_color();
        selected[0]->reposition(selected[1]->get_center());
        selected[0]->set_center(selected[1]->get_center());
        //selected[0]->set_color(selected[1]->get_color());
        selected[1]->reposition(save_center);
        selected[1]->set_center(save_center);
        //selected[1]->set_color(save_color);

        int i1 = selected[1]->get_center().x/80;
        int j1 = selected[1]->get_center().y/80;
        
        int i0 = selected[0]->get_center().x/80;
        int j0 = selected[0]->get_center().y/80;

        Cell sauv = cells[i1][j1];
        cells[i1][j1] = cells[i0][j0];
        cells[i0][j0] = sauv;
        
      
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
        
        bool res_1 = are_aligned(cells[i0][j0]);
        delete_alignment();
        bool res_2 = are_aligned(cells[i1][j1]);
        delete_alignment();


        if (!res_1 && !res_2){
          Cell sauv = cells[i0][j0];
          cells[i0][j0] = cells[i1][j1];
          cells[i1][j1] = sauv;

          Point save_center_{selected[1]->get_center().x, selected[1]->get_center().y};
          string save_color = selected[1]->get_color();
          selected[1]->reposition(selected[0]->get_center());
          selected[1]->set_center(selected[0]->get_center());
          //selected[1]->set_color(save_color);
          selected[0]->reposition(save_center_);
          selected[0]->set_center(save_center_);
          //selected[0]->set_color(selected[1]->get_color());
        }
      selected.clear();

    }
    else if ((selected.size() == 2) && (!selected[0]->is_neighbor (selected[1]))){
      selected.clear();
    }
}
