#include "classes.hpp"

Points::Points():
  datax(),
  datay()
{}

Points::Points(size_t size, p_t point):
  datax(size, point.x),
  datay(size, point.y)
{}

void Points::set(size_t id, p_t point) noexcept
{
  datax.set(id, point.x);
  datay.set(id, point.y);
}

void Points::setSave(size_t id, p_t point)
{
  if (id < 0 || id > data.volume) {
    throw std::out_of_range("Points::setSave: out of range");
  }
  datax.set(id, point.x);
  datay.set(id, point.y);
}

p_t Points::get(size_t id)
{
  return {datax.get(id), datay.get(id)}
}

p_t Points::getSave(size_t id)
{
  if (id < 0 || id > datax.volume) {
    throw std::out_of_range("Points::getSave: out of range");
  }
  return {datax.get(id), datay.get(id)};
}

size_t findSortX(int y)
{
  return datay.findSort();
}

Points Points::append(p_t point)
{
  Points res(*this);
  res.datax.append(point.x);
  res.datay.append(point.y);
  std::swap(res.datax, datax);
  std::swap(res.datay, datay);
  return *this;
}

Points Points::appendSort(p_t point)
{
  Points res(*this);
  res.datax.appendSort(point.x);
  res.datay.insert(point.y, res.datax, k, [] (int a, int b) {return a == b});
  std::swap(res.datax, datax);
  std::swap(res.datay, datay);
  return *this; 
}
