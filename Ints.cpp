#include "classes.hpp"
#include <climits>
#include <cstddef>
#include <stdexcept>
#include <utility>


Ints::Ints():
  volume(0),
  size(0),
  data(nullptr)
{}
Ints::Ints(size_t size, int field):
  size(size),
  volume(size),
  data(new int[size])
{
  for (size_t i = 0; i < size; i++) {
    data[i] = field;
  }
}

Ints::Ints(size_t size):
  size(size),
  volume(size),
  data(new int[size])
{}

Inst::Ints(const Ints::Ints & rhs):
  size(rhs.size),
  volume(rhs.volume),
  data(new int[rhs.size])
{
  for (size_t i = 0; i < size; i++) {
    data[i] = rhs.data[i];
  }
}

Ints::~Ints()
{
  delete[] data;
}

Ints::Ints & operator=(const Ints::Ints & rhs)
{
  Ints res(rhs);
  std::swap(res.volume, volume);
  std::swap(res.data, data);
  std::swap(res.size, size);

  return *this;
}


Ints::Ints & operator=(Ints::Ints && rhs) noexcept
{
  if (*this == rhs) {
    return *this;
  }
  std::swap(rhs.volume, volume);
  std::swap(rhs.size, size);
  std::swap(rhs.data, data);
  return *this;
}

Ints::Ints operator+(const Ints::Ints & rhs)
{
  if (rhs.volume != volume) {
    throw std::logic_error("Hz cho napisat");
  }
  Ints res(rhs);
  for (size_t i = 0; i < volume; i++) {
    if (res.data[i] > ULONG_MAX - data[i]) {
      throw std::logic_error("Overflow");
    }
    res.data[i] += data[i];
  }
  return res;
}
