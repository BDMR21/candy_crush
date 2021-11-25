#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include "view.cpp"

int main (int argc, char *argv[])
{
  srand (time (0));
  MainWindow window;
  window.end ();
  window.show (argc, argv);
  return Fl::run ();
}