#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>

#define CALLBACK_SIGNATURE std::function<void(const char *)> callback

class Helper
{
public:
  Helper(CALLBACK_SIGNATURE);
  void SplitString(const char *str, const char *delimiters);
  int InputCounter = 0;
private:
  CALLBACK_SIGNATURE;
};

// ************************** FOR FUTURE USE **************
// point
struct point
{
  int x;
  int y;

  point(int x = 0, int y = 0)
      : x(x), y(y)
  {
  }

  point operator+(const point& a) const
  {
    return point(x + a.x, y + a.y);
  }

  point operator-(const point& a) const
  {
    return point(x - a.x, y - a.y);
  }

  point& operator=(const point& a)
  {
    x = a.x;
    y = a.y;
    return *this;
  }

  bool operator==(const point& a) const
  {
    return (x == a.x && y == a.y);
  }

  void Print() const
  {
    Serial.printf("[%d,%d]\n", x, y);
    return;
  }

  int Manhattan(const point& a) const
  {
    return abs(x - a.x) + abs(y - a.y);
  }
  
};

#endif