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

Ints::Ints(const Ints & rhs):
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

Ints & Ints::operator=(const Ints & rhs)
{
  Ints res(rhs);
  std::swap(res.volume, volume);
  std::swap(res.data, data);
  std::swap(res.size, size);

  return *this;
}


Ints & Ints::operator=(Ints && rhs) noexcept
{
  std::swap(rhs.volume, volume);
  std::swap(rhs.size, size);
  std::swap(rhs.data, data);
  return *this;
}

Ints Ints::operator+(const Ints & rhs)
{
  if (rhs.volume != volume) {
    throw std::logic_error("Ints::+: diff sizes");
  }
  Ints res(rhs);
  long long sum = 0;
  for (size_t i = 0; i < volume; i++) {
  sum = (long long)(data[i]) + rhs.data[i];
    if (sum > INT_MAX || sum < INT_MIN) {
      throw std::logic_error("Ints::+: Overflow");
    }
    res.data[i] += data[i];
  }
  return res;
}

void Ints::setSave(size_t id, int i)
{
  if(id >= volume) {
    throw std::out_of_range("Ints::setSave: index out of range");
  }
  data[id] = i;
}

int Ints::getSave(size_t id)
{
  if(id >= volume) {
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
    if (data[m] >= j) {
      r = m;
    } else {
      l = m + 1;
    }
    m = (l + r) / 2;
  }
  return l;
}

void Ints::resize(size_t len)
{
  size_t new_size = 0;
  if (!len) {
    if (volume > (ULONG_MAX - size == 0) / 2) {
      throw std::logic_error("Ints::resize: Overflow");
    }
    new_size = volume * 2 + size == 0;
  } else {
    if (volume > ULONG_MAX - len) {
      throw std::logic_error("Ints::resize: Overflow");
    }
    new_size = len + volume;
  }
  int * res = new int[new_size];
  for (size_t i = 0; i < volume; i++) {
    res[i] = data[i];
  }
  delete[] data;
  size = new_size;
  data = res;
}

Ints Ints::insert(int i, bool (*func)(int, int))
{
  Ints res(*this);
  int temp = 0;
  int buff = 0;
  size_t j = 0;
  for (; j < res.getVolume(); j++) {
    if (func(res.data[j], i)) {
      temp = res.data[j];
      res.data[j] = i;
      break;
    }
  }
  if (j == res.getVolume()) {
    res.append(i);
  } else {
    j++;
    if (res.getVolume() == res.getSize()) {
      res.resize();
    }
    res.volume++;
  }
  for (; j < res.getVolume(); j++) {
    buff = res.data[j];
    res.data[j] = temp;
    temp = buff;
  }
  std::swap(res.data, data);
  std::swap(res.volume, volume);
  std::swap(res.size, size);
  return *this; 
}

Ints Ints::insert(int i, const Ints& mas, int k, bool (*func)(int, int))
{
  Ints res(*this);
  int temp = 0;
  int buff = 0;
  size_t j = 0;
  for (; j < res.getVolume(); j++) {
    if (func(mas.data[j], k)) {
      temp = res.data[j];
      res.data[j] = i;
      break;
    }
  }
  if (j == res.getVolume()) {
    res.append(i);
  } else {
    j++;
    res.volume++;
  }
  for (; j < res.getVolume(); j++) {
    buff = res.data[j];
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

Ints Ints::append(const Ints& b)
{
  Ints res(*this);
  if (volume > ULONG_MAX - b.volume) {
    throw std::logic_error("Ints::append: Overflow");
  }
  if (volume + b.volume >= size) {
    if (b.volume >= volume) {
      res.resize(b.volume-volume);
    } else {
      res.resize(volume - b.volume);
    }
  }
  for (size_t i = 0; i < b.volume; i++) {
    res.data[res.volume + i] = b.data[i];
  }
  std::swap(res.data, data);
  std::swap(res.volume + b.volume, volume);
  std::swap(res.size, size);
  return *this;
}

Ints Ints::appendSort(const Ints& b)
{
  Ints res(*this);
  if (volume > ULONG_MAX - b.volume) {
    throw std::logic_error("Ints::append: Overflow");
  }
  if (volume + b.volume >= size) {
    if (b.volume >= volume) {
      res.resize(b.volume-volume);
    } else {
      res.resize(volume - b.volume);
    }
  }
  for (size_t i = 0; i < b.volume; i++) {
    res.appendSort(b.data[i]);
  }
  std::swap(res.data, data);
  std::swap(res.volume, volume);
  std::swap(res.size, size);
  return *this;
}
