#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
  {
  ostringstream filename;
  filename << "output";
  filename << setfill( '0' ) << setw( 3 ) << 42;
  filename << ".txt";

  ofstream f( filename.str().c_str() );
  f << "Hello world!\n";
  f.close();

  cout << "Wrote to \"" << filename.str() << "\"\n";
  return 0;
  }