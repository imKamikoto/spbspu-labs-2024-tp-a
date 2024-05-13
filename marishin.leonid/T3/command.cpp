#include "command.hpp"
#include <functional>
#include <numeric>
#include <string>
#include <iomanip>
#include <algorithm>
#include "polygon.hpp"

double marishin::accumulateAreaIf(double result, const Polygon& polygon, bool value)
{
  if (value == (polygon.points.size() % 2))
  {
    result += polygon.getArea();
  }
  return result;
}

double marishin::accumulateArea(double result, const Polygon& polygon)
{
  result += polygon.getArea();
  return result;
}

double marishin::accumulateAreaIfCount(double result, const Polygon& polygon, size_t count)
{
  if (polygon.points.size() == count)
  {
    result += polygon.getArea();
  }
  return result;
}

bool marishin::isEven(const Polygon& polygon)
{
  return (polygon.points.size() > 2) && (polygon.points.size() % 2 == 0);
}

bool marishin::isOdd(const Polygon& polygon)
{
  return !isEven(polygon);
}

bool marishin::isProperSize(const Polygon& polygon, size_t number)
{
  return (polygon.points.size() == number);
}

bool marishin::comparePoints(const Polygon& first, const Polygon& second)
{
  return (first.points.size() < second.points.size());
}

bool marishin::compareArea(const Polygon& first, const Polygon& second)
{
  return (first.getArea() < second.getArea());
}

void marishin::getArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  using namespace std::placeholders;
  std::function< double(double, const Polygon&) > area;
  if (name == "EVEN")
  {
    area = std::bind(accumulateAreaIf, _1, _2, false);
    out << std::accumulate(data.begin(), data.end(), 0.0, area);
  }
  else if (name == "ODD")
  {
    area = std::bind(accumulateAreaIf, _1, _2, true);
    out << std::accumulate(data.begin(), data.end(), 0.0, area);
  }
  else if (name == "MEAN")
  {
    if (data.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    area = std::bind(accumulateArea, _1, _2);
    out << std::accumulate(data.begin(), data.end(), 0.0, area) / data.size();
  }
  else
  {
    size_t count = 0;
    try
    {
      count = std::stoull(name);
    }
    catch (const std::invalid_argument&)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (count < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    area = std::bind(accumulateAreaIfCount, _1, _2, count);
    out << std::accumulate(data.begin(), data.end(), 0.0, area);
  }
}

void marishin::getCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  if (name == "EVEN")
  {
    out << std::count_if(data.begin(), data.end(), isEven);
  }
  else if (name == "ODD")
  {
    out << std::count_if(data.begin(), data.end(), isOdd);
  }
  else
  {
    size_t countVertex = 0;
    try
    {
      countVertex = std::stoull(name);
    }
    catch (const std::invalid_argument&)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (countVertex < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    std::function< bool(const Polygon&) > isRightCount = std::bind(isProperSize, _1, countVertex);
    out << std::count_if(data.begin(), data.end(), isRightCount);
  }
}

void marishin::getMin(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (data.empty())
  {
    throw std::logic_error("No polygons for this command");
  }
  else
  {
    if (argument == "AREA")
    {
      out << std::setprecision(1) << std::fixed;
      out << std::min_element(data.begin(), data.end(), compareArea)->getArea();
    }
    else if (argument == "VERTEXES")
    {
      out << std::min_element(data.begin(), data.end(), comparePoints)->points.size();
    }
    else
    {
      out << "<INVALID COMMAND>";
    }
  }
}

void marishin::getMax(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  std::string argument = "";
  in >> argument;
  if (data.empty())
  {
    throw std::logic_error("No polygons for this command");
  }
  else
  {
    if (argument == "AREA")
    {
      out << std::setprecision(1) << std::fixed;
      out << std::max_element(data.begin(), data.end(), compareArea)->getArea();
    }
    else if (argument == "VERTEXES")
    {
      out << std::max_element(data.begin(), data.end(), comparePoints)->points.size();
    }
    else
    {
      out << "<INVALID COMMAND>";
    }
  }
}

bool marishin::hasIntersection(const Polygon& first, const Polygon& second)
{
  marishin::Point minLhs = *std::min_element(first.points.cbegin(), first.points.cend());
  marishin::Point maxLhs = *std::max_element(first.points.cbegin(), first.points.cend());
  marishin::Point minRhs = *std::min_element(second.points.cbegin(), second.points.cend());
  marishin::Point maxRhs = *std::max_element(second.points.cbegin(), second.points.cend());

  bool firstCheck = (minLhs <= maxRhs) && (maxLhs >= minRhs);
  bool secondCheck = (minRhs <= maxLhs) && (maxRhs >= minLhs);
  return firstCheck || secondCheck;
}

bool marishin::checkRectangle(const Polygon& ptr)
{
  if (ptr.points.size() != 4)
  {
    return false;
  }
  marishin::RectangleVector firstSide(ptr.points[0], ptr.points[1]);
  marishin::RectangleVector secondSide(ptr.points[1], ptr.points[2]);
  marishin::RectangleVector thirdSide(ptr.points[2], ptr.points[3]);
  marishin::RectangleVector fourthSide(ptr.points[0], ptr.points[3]);
  return (firstSide.cos(secondSide) == 0) && (secondSide.cos(thirdSide) == 0) && (thirdSide.cos(fourthSide) == 0);
}

void marishin::getRects(const std::vector< Polygon >& data, std::ostream& out)
{
  out << std::count_if(data.begin(), data.end(), checkRectangle);
}

void marishin::getIntersections(const std::vector< marishin::Polygon >& data, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if ((polygon.points.empty()) || (!in) || (in.peek() != '\n'))
  {
    throw std::logic_error("Wrong argument");
  }
  using namespace std::placeholders;
  auto isIntersected = std::bind(hasIntersection, std::cref(polygon), _1);
  out << std::count_if(data.begin(), data.end(), isIntersected);
}
