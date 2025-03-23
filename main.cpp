#include <iostream>
#include "stream_guard.hpp"

namespace geom
{
  struct Point {
    int x, y;
  };
  std::ostream & operator<<(std::ostream & os, const Point & rhs);
}

int main()
{
  geom::Point p{1, 2};
  std::cout << p << "\n";
}

// geom.cpp
std::ostream & geom::operator<<(std::ostream & os, const Point & rhs)
{
  std::ostream::sentry s(os);
  if (!s)
  {
    return os;
  }
  os << "(" << rhs.x << " " << rhs.y << ")";
  return os;
}
