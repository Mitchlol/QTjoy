#include <QApplication>

#include "SRVjoy.h"

int main(int argc, char *argv[])
//int main(int argc, char** argv)
{
//   parse_args(argc, argv); // Parses command line arguments
   // Although it's not really necessary through this GUI
   // A GUI "argument modification tool" needs to be implemented!!!

   QApplication a(argc, argv);

   SRVjoy *joy = new SRVjoy;
   joy->show();

   return a.exec();
}