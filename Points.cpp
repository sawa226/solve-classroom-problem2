#include "classes.hpp"

Points::Points():
  data()
{}

Points::Points(size_t size, p_t point):
  data(size*2, point.x)
{
  for (size_t i = 1; i < size; i+=2) {
    data.set(i, point.y);
}

void Points::set(size_t id, p_t point) noexcept
{
  id *= 2;
  data.set(id++, point.x);
  data.set(id, point.y);
}

void Points::setSave(size_t id, p_t point)
{
  if (id > ULONG_MAX / 2 - 1) {
    throw std::logic_error("Points::setSave: Overflow");
  }
  if (id < 0 || id > data.volume) {
    throw std::out_of_range("Points::setSave: out of range");
  }
  id *= 2;
  data.set(id++, point.x);
  data.set(id, point.y);
}

int Points::getSave(size_t id)
{
  if (id > ULONG_MAX / 2 - 1) {
    throw std::logic_error("Points::setSave: Overflow");
  }
  if (id < 0 || id > data.volume) {
    throw std::out_of_range("Points::setSave: out of range");
  }
  return data.get(id);
}

Points Points::append(p_t point)
{
  data.append(point.x);
  data.append(point.y);
}
