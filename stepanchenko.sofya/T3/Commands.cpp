#include "Commands.hpp"

#include <map>
#include <functional>
#include <algorithm>
#include <iomanip>
#include "Polygon.hpp"
#include "Utilities.hpp"
#include "StreamGuard.hpp"

void stepanchenko::areaCmd(const std::vector< Polygon > & polygons, std::istream& in, std::ostream& out)
{
  std::map< std::string, std::function< double() > > cmdArea;
  {
    using namespace std::placeholders;
    cmdArea["EVEN"] = std::bind(areaEven, polygons);
    cmdArea["ODD"] = std::bind(areaOdd, polygons);
    cmdArea["MEAN"] = std::bind(areaMean, polygons);
  }
    std::string arg;
    in >> arg;
    if ((arg == "MEAN") && polygons.empty())
    {
      throw std::logic_error("No figures");
    }
    StreamGuard stream(out);
    out << std::fixed << std::setprecision(1);
    try
    {
      out << cmdArea.at(arg)() << '\n';
    }
    catch (const std::out_of_range&)
    {
      int num = std::stoull(arg);
      if (num < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
      out << areaNum(polygons, num) << '\n';
    }
}

void stepanchenko::maxCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out)
{
  std::map< std::string, std::function< void(std::ostream&) > > cmdMax;
  {
    using namespace std::placeholders;
    cmdMax["AREA"] = std::bind(maxArea, polygons, _1);
    cmdMax["VERTEXES"] = std::bind(maxVertexes, polygons, _1);
  }
  std::string arg;
  in >> arg;
  StreamGuard stream(out);
  out << std::fixed << std::setprecision(1);
  try
  {
    cmdMax.at(arg)(out);
    out << '\n';
  }
  catch (const std::logic_error& e)
  {
    out << e.what() << '\n';
  }
}

void stepanchenko::minCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out)
{
  std::map< std::string, std::function< void(std::ostream&) > > cmdMin;
  {
    using namespace std::placeholders;
    cmdMin["AREA"] = std::bind(minArea, polygons, _1);
    cmdMin["VERTEXES"] = std::bind(minVertexes, polygons, _1);
  }
  std::string arg;
  in >> arg;
  StreamGuard stream(out);
  out << std::fixed << std::setprecision(1);
  try
  {
    cmdMin.at(arg)(out);
    out << '\n';
  }
  catch (const std::logic_error& e)
  {
    out << e.what() << '\n';
  }
}

void stepanchenko::countCmd(std::vector< Polygon > polygons, std::istream& in, std::ostream& out)
{
  std::map  < std::string, std::function< size_t() > > cmdCount;
  {
    using namespace std::placeholders;
    cmdCount["EVEN"] = std::bind(countEven, polygons);
    cmdCount["ODD"] = std::bind(countOdd, polygons);
  }
  std::string arg;
  in >> arg;
  try
  {
    out << cmdCount.at(arg)() << '\n';
  }
  catch (const std::out_of_range&)
  {
    int num = std::stoull(arg);
    if (num < 3)
    {
      throw std::invalid_argument("NOT A FIGURE");
    }
    out << countNum(polygons, num) << '\n';
  }
}
