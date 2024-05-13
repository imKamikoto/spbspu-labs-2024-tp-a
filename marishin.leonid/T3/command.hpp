#ifndef COMANDS_HPP
#define COMANDS_HPP

#include <iostream>
#include <vector>
#include "polygon.hpp"

namespace marishin
{
  void getArea(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
  void getCount(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
  void getMin(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
  void getMax(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
  void getRects(const std::vector< marishin::Polygon >& data, std::ostream& out);
  void getIntersections(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);

  double accumulateAreaIf(double result, const Polygon& polygon, bool value);
  double accumulateArea(double result, const Polygon& polygon);
  double accumulateAreaIfCount(double result, const Polygon& polygon, size_t count);
  bool isEven(const Polygon& polygon);
  bool isOdd(const Polygon& polygon);
  bool isProperSize(const Polygon& polygon, size_t number);
  bool comparePoints(const Polygon& first, const Polygon& second);
  bool compareArea(const Polygon& first, const Polygon& second);
  bool hasIntersection(const Polygon& first, const Polygon& second);
  bool checkRectangle(const Polygon& ptr);
  void getRects(const std::vector< Polygon >& data, std::ostream& out);
  void getIntersections(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out);
}

#endif
