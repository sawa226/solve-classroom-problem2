#include "classes.hpp"

Mtx::Mtx():
  n(1),
  m(1),
  data(1, 0)
{}

Mtx::Mtx(size_t n, size_t m):
  n(n),
  m(m),
{
  if ( n > ULONG_MAX - m) {
    throw std::logic_error("Mts::Mtx(size_t n, size_t m): Overflow");
  }
  data(n * m, 0);
}

Mtx Mtx::sum(const Mtx& b)
{
  Mtx res(*this);
  if (n != b.n || m != b.m) {
    throw std::logic_error("Mtx::sum: diff sizes");
  }
  res.data = res.data + b.data;
  std::swap(res.data, data);
  return *this;
}

Mtx Mtx::mul(int b)
{
  Mtx res(*this);
  int max_size_el = INT_MAX / b;
  for (size_t i = 0; i < n * m; i++) {
    if (res.data.get(i) > max_size_el) {
      throw std::logic_error("Mtx::mul: Overflow");
    }
    res.data[i] *= b;
  }
  std::swap(res.data, data);
  return *this;
}

Mtx Mtx::mul(const Mtx& b)
{
  if (m != b.n) {
    throw std::logic_error("Mtx::mul: diff sizes");
  }
  Mtx res(n, b.m);
  long long loc_sum = 0;
  long long first_el = 0;
  long long second_el = 0;
  for (size_t k = 0; k < b.m; k++) {
    for (size_t s = 0; s < n; s++) {
      loc_sum = 0;
      for (size_t i = 0; i < b.n; i++) {
        first_el = data.get(s * m + i);
        second_el = b.data.get(i * b.m + k);
        loc_sum += first_el * second_el;
        if (loc_sum > INT_MAX || loc_sum < INT_MIN) {
          throw std::logic_error("Mtx::mul: Overflow");
        }
      }
      res.data.set(s * b.m + k, (int)loc_sum);
    }
  }
  std::swap(res.data, data);
  std::swap(res.n, n);
  std::swap(res.m, m);
  return *this; 
}

Mtx Mtx::transpose() const
{
  Mtx res(m, n);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      res.data.set(j * n + i, data.get(i * m + j));
    }
  }
  return res;
}

int Mtx::det() const
{
  if (n ! = m) {
    throw std::logic_error("Mtx::det: diff sizes");
  }
  Mtx res(*this);
  int a = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (i != j) {
        a = hi();
        for (size_t k = 0; k < m; k++) {
          res.data.set(j * m + k, res.data.get(j * m + k) - a);
        }
      }
    }
  }
  int cnt = 1;
  for (size_t i = 0; i < n; i++) {
    cnt * = res.data.get(i * m + i);
  }
  return cnt;
}

Mtx Mtx::add_row(int init)
{
  Ints row(m, init);
  data.append(row);
  return *this;
}
