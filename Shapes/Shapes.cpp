// Student ID: 20274909

#include <iostream>
#include <string>
#include <sstream>
#include "Shapes.h"

using namespace std;

//int main()
//{
//   
//   Screen canvas = Screen(11, 13);
//
//   canvas.clear();
//
//
//   Line test = Line(0, 0, 12, 15);
//   test.draw(canvas, 'V');
//   cout << canvas.to_string();
//
//}

Screen::Screen(size_t w, size_t h) {
   this->_h = h;
   this->_w = w;

   _pix.resize(h);
   for (size_t i = 0; i < h; i++) {
      _pix[i].resize(w);
   }
}

void Screen::fill(char c) {
   for (size_t i = 0; i < _h; i++) {
      for (size_t j = 0; j < _w; j++) {
         _pix[i][j] = c;
      }
   }
}

string Screen::to_string() const {
   string output = "";

   for (int i = (_h - 1); i >= 0; i--) { // TODO
      for (size_t j = 0; j < _w; j++) {
         output += _pix[i][j];
      }
      output += "\n";
   }

   return output;
}

bool Point::draw(Screen& screen, char c) {
   if (this->_y >= screen.get_h() || this->_y < 0 || this->_x >= screen.get_w() || this->_x < 0) {
      return false;
   }
   screen.get_pix()[this->_y][this->_x] = c;
   return true;
}

bool Line::draw_by_x(Screen& scr, char ch, size_t x1, size_t y1, size_t x2, size_t y2) {
   if (x1 > x2)
      return draw_by_x(scr, ch, x2, y2, x1, y1);

   double dy = ((double)y2 - y1) / ((double)x2 - x1);
   bool contained = true;
   double x = x1, y = y1;
   while (x <= x2) {
      contained &= Point((size_t)x, (size_t)y).draw(scr, ch);
      x += 1; y += dy;
   }
   return contained;
}

bool Line::draw_by_y(Screen& scr, char ch, size_t x1, size_t y1, size_t x2, size_t y2) {
   if (y1 > y2)
      return draw_by_y(scr, ch, x2, y2, x1, y1);

   double dx = ((double)x2 - x1) / ((double)y2 - y1);
   bool contained = true;
   double y = y1, x = x1;
   while (y <= y2) {
      contained &= Point((size_t)x, (size_t)y).draw(scr, ch);
      y += 1; x += dx;
   }
   return contained;
}

bool Line::draw(Screen& screen, char c) {
   int xdiff = this->_x2 - this->_x1;
   if (xdiff < 0)
      xdiff = -xdiff;
   int ydiff = this->_y2 - this->_y1;
   if (ydiff < 0)
      ydiff = -ydiff;
   if (xdiff > ydiff) {
      return draw_by_x(screen, c, this->_x1, this->_y1, this->_x2, this->_y2);
   }
   return draw_by_y(screen, c, this->_x1, this->_y1, this->_x2, this->_y2);
}

bool Quadrilateral::draw(Screen& screen, char c) {
   Line line1 = Line(this->_x1, this->_y1, this->_x2, this->_y2);
   Line line2 = Line(this->_x2, this->_y2, this->_x3, this->_y3);
   Line line3 = Line(this->_x3, this->_y3, this->_x4, this->_y4);
   Line line4 = Line(this->_x4, this->_y4, this->_x1, this->_y1);

   bool contained = true;

   contained &= line1.draw(screen, c);
   contained &= line2.draw(screen, c);
   contained &= line3.draw(screen, c);
   contained &= line4.draw(screen, c);

   return contained;

}

Stick_Man::Stick_Man(size_t x, size_t y, size_t w, size_t h) {
   _parts.clear();

   this->_x = x;
   this->_y = y;

   if (w == 0 || w == 1) {
      this->_w = DEFAULT_W;
   }
   else {
      this->_w = w;
   }

   if (h == 0 || h == 1) {
      this->_h = DEFAULT_H;
   }
   else {
      this->_h = h;
   }

   _parts.push_back(new Upright_Rectangle(x + 0, y + h / 2, x + w - 1, y + h - 1));
   _parts.push_back(new Line(x + w / 2, y + h / 2, x + w / 2, y + h / 4));
   _parts.push_back(new Line(x + w / 2, y + h / 2, x + w / 4, y + h / 4));
   _parts.push_back(new Line(x + w / 2, y + h / 2, x + 3 * w / 4, y + h / 4));
   _parts.push_back(new Line(x + w / 2, y + h / 4, x, y));
   _parts.push_back(new Line(x + w / 2, y + h / 4, x + w - 1, y));
}

bool Stick_Man::draw(Screen& screen, char c) {
   bool contained = true;
   for (size_t i = 0; i < _parts.size(); i++) {
      contained &= _parts[i]->draw(screen, c);
   }
   return contained;
}

Stick_Man::~Stick_Man() {
   size_t stick_size = _parts.size();
   for (size_t i = 0; i < stick_size; i++) {
      delete _parts[i];
   }
}