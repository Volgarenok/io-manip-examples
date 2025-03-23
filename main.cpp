#include <iostream>
#include "stream_guard.hpp"

namespace geom
{
  struct Point {
    int x, y;
  };
  struct JsonPoint {
    const Point & p;
    const char * xname;
    const char * yname;
  };
  std::ostream & operator<<(std::ostream & os, const Point & rhs);
  std::ostream & operator<<(std::ostream & os, const JsonPoint & rhs);
  std::ostream & next_point_as_json(std::ostream & os);
  std::ostream & next_x_as_a(std::ostream & os);
  std::ostream & next_x_as_coord1(std::ostream & os);
}

int main()
{
  geom::Point p{1, 2};
  // (1 2)
  std::cout << p << "\n";
  // { "x": 1, "y": 2 }
  std::cout << geom::next_point_as_json;
  std::cout << geom::next_x_as_coord1 << p << "\n";
  std::cout << p << "\n";

  std::cout << geom::JsonPoint{p, "coord1", "coord2"} << "\n";
}

// geom.cpp
std::ostream & geom::operator<<(std::ostream & os, const JsonPoint & rhs)
{
  std::ostream::sentry s(os);
  if (!s)
  {
    return os;
  }
  os << "{ ";
  os << "\"" << rhs.xname;
  os << "\": " << rhs.p.x;
  os << ", ";
  os << "\"" << rhs.yname;
  os << "\": " << rhs.p.y;
  os << " }";
  return os;
}

static const int next_point_as_json_data_id = std::ios::xalloc();
static const int next_x_with_name_data_id = std::ios::xalloc();

std::ostream & geom::next_point_as_json(std::ostream & os)
{
  os.iword(next_point_as_json_data_id) = 1;
  return os;
}
std::ostream & geom::next_x_as_a(std::ostream & os)
{
  os.pword(next_x_with_name_data_id) = const_cast< char * >("a");
  os.iword(next_x_with_name_data_id) = 1;
  return os;
}
std::ostream & geom::next_x_as_coord1(std::ostream & os)
{
  os.pword(next_x_with_name_data_id) = const_cast< char * >("coord1");
  os.iword(next_x_with_name_data_id) = 1;
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
    if (os.iword(next_x_with_name_data_id) == 1)
    {
      os << "\"";
      os << static_cast< const char * >(os.pword(next_x_with_name_data_id));
      os << "\": ";
      os.iword(next_x_with_name_data_id) = 0;
    }
    else
    {
      os << "\"x\": ";
    }
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
