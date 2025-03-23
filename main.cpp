#include <iostream>
#include "stream_guard.hpp"

namespace geom
{
  struct Point {
    int x, y;
  };
  std::ostream & operator<<(std::ostream & os, const Point & rhs);
  std::ostream & next_point_as_json(std::ostream & os);
}

int main()
{
  geom::Point p{1, 2};
  // (1 2)
  std::cout << p << "\n";
  // { "x": 1, "y": 2 }
  std::cout << geom::next_point_as_json << p << "\n";
  std::cout << p << "\n";
}

// geom.cpp
static const int next_point_as_json_data_id = std::ios::xalloc();

std::ostream & geom::next_point_as_json(std::ostream & os)
{
  os.iword(next_point_as_json_data_id) = 1;
  return os;
}

std::ostream & geom::operator<<(std::ostream & os, const Point & rhs)
{
  std::ostream::sentry s(os);
  if (!s)
  {
    return os;
  }
  if (os.iword(next_point_as_json_data_id) == 1)
  {
    os << "{ ";
    os << "\"x\": ";
    os << rhs.x;
    os << ", ";
    os << "\"y\": ";
    os << rhs.y;
    os << " }";
    os.iword(next_point_as_json_data_id) = 0;
  }
  else
  {
    os << "(" << rhs.x << " " << rhs.y << ")";
  }
  return os;
}
