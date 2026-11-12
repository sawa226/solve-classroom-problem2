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
    throw std::logic_error("Ints::+: diff sizes");
  }
  Ints res(rhs);
  for (size_t i = 0; i < volume; i++) {
    if (res.data[i] > ULONG_MAX - data[i]) {
      throw std::logic_error("Ints::+: Overflow");
    }
    res.data[i] += data[i];
  }
  return res;
}

void Ints::setSave(size_t id, int i)
{
  if(id < 0 || id >= volume) {
    throw std::out_of_range("Ints::setSave: index out of range");
  }
  data[id] = i;
}

void Ints::getSave(size_t id)
{
  if(id < 0 || id >= volume) {
    throw std::out_of_range("Ints::getSave: index out of range");
  }
  return data[id];
}

size_t Ints::find(int i) const
{
  for (size_t j = 0; j < volume; j++) {
    if (data[j] == i) {
      return j;
    }
  }
  return volume;
}

size_t Ints::findSort(int j) const
{
  size_t l = 0;
  size_t r = volume;
  size_t m = (l + r) / 2;
  while (r > l) {
    if (data[m] > j) {
      r = m;
    } else {
      l = m;
    }
    m = (l + r) / 2;
  }
  return data[l];
}

void Ints::resize(size_t len)
{
  size_t new_volume = 0;
  if (!len) {
    if (volume > ULONG_MAX / 2) {
      throw std::logic_error("Ints::resize: Overflow");
    }
    new_volume = volume * 2;
  } else {
    if (volume > ULONG_MAX - len) {
      throw std::logic_error("Ints::resize: Overflow");
    }
    new_volume = len + volume;
  }
  int * res = new int[new_volume];
  for (size_t i = 0; i < volume; i++) {
    (*res)[i] = data[i];
  }
  std::swap(data, *res);
  size = volume*2;
  delete[] res;
}

Ints Ints::insert(int i, bool (*func)(int, int))
{
  Ints res(*this);
  int temp = 0;
  int buff = 0;
  size_t j = 0;
  for (; j < volume; j++) {
    if (func(res.data[i], i)) {
      temp = res.data[j];
      res.data[j] = i;
      break;
    }
  }
  for (; j < volume; j++) {
    buff = res.data[i];
    res.data[j] = temp;
    temp = buff;
  }
  std::swap(res.data, data);
  std::swap(res.volume, volume);
  std::swap(res.size, size);
  return *this; 
}

Ints Ints::insert(int i, Ints mas, int k, bool (*func)(int, int))
{
  Ints res(*this);
  int temp = 0;
  int buff = 0;
  size_t j = 0;
  for (; j < volume; j++) {
    if (func(mas.data[i], k)) {
      temp = res.data[j];
      res.data[j] = i;
      break;
    }
  }
  j++;
  for (; j < volume; j++) {
    buff = res.data[i];
    res.data[j] = temp;
    temp = buff;
  }
  std::swap(res.data, data);
  std::swap(res.volume, volume);
  std::swap(res.size, size);
  return *this; 
}
Ints Ints::append(int i)
{
  Ints res(*this);
  if (volume == size) {
    res.resize();
  }
  res.data[res.volume++] = i;
  std::swap(res.data, data);
  std::swap(res.volume, volume);
  std::swap(res.size, size);
  return *this;
}

Ints Ints::appendSort(int i, bool (*func)(int, int))
{
  Ints res(*this);
  if (volume == size) {
    res.resize();
  }
  res = res.insert(i, func);
  std::swap(res.data, data);
  std::swap(res.volume, volume);
  std::swap(res.size, size);
  return *this;
}

Ints Ints::append(Ints b)
{
  Ints res(*this);
  if (volume > ULONG_MAX - b.volume) {
    throw std::logic_error("Ints::append: Overflow");
  }
  if (volume + b.volume >= size) {
    res.resize(b.volume-volume);
  }
  for (size_t i = 0; i < b.volume; i++) {
    res.data[i] = b.data[i];
  }
  std::swap(res.data, data);
  std::swap(res.volume, volume);
  std::swap(res.size, size);
  return *this;
}

Ints Ints::appendSort(Ints b)
{
  Ints res(*this);
  if (volume > ULONG_MAX - b.volume) {
    throw std::logic_error("Ints::append: Overflow");
  }
  if (volume + b.volume >= size) {
    res.resize(b.volume-volume);
  }
  for (size_t i = 0; i < b.volume; i++) {
    res.data.appendSort(b.data[i]);
  }
  std::swap(res.data, data);
  std::swap(res.volume, volume);
  std::swap(res.size, size);
  return *this;
}
