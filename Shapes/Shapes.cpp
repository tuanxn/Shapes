// Student ID: 20274909

#include <iostream>
#include <string>
#include <sstream>
#include "Shapes.h"

using namespace std;

int main()
{
   Screen test = Screen(4, 6);
}

Screen::Screen(size_t w, size_t h) {
   _pix.resize(h);
   for (size_t i = 0; i < h; i++) {
      _pix[i].resize(w);
   }
}
