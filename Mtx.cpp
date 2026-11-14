#include "classes.hpp"
#include <climits>
#include <stdexcept>
#include <utility>

Mtx::Mtx():
  n(1),
  m(1),
  data(1, 0)
{}

Mtx::Mtx(size_t n, size_t m):
  n(n),
  m(m)
{
  if (m != 0 && n > ULONG_MAX / m) {
    throw std::logic_error("Mts::Mtx(size_t n, size_t m): Overflow");
  }
  Ints res(n * m, 0);
  data = std::move(res);
}

Mtx Mtx::sum(const Mtx& b)
{
  Mtx res(*this);
  if (n != b.n || m != b.m) {
    throw std::logic_error("Mtx::sum: diff sizes");
  }
  res.data = res.data + b.data;
  return res;
}

Mtx Mtx::mul(int b)
{
  if (b == 0) {
    Mtx res(n, m);
    std::swap(res.data, data);
    return *this;
  }
  Mtx res(*this);
  long long temp = 0;
  for (size_t i = 0; i < n * m; i++) {
    temp = (long long)res.data.get(i) * b;
    if (temp > INT_MAX || temp < INT_MIN) {
      throw std::logic_error("Mtx::mul: Overflow");
    }
    res.data.set(i, res.data.get(i)*b);
  }
  return res;
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
  return res; 
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
  if (n != m)
    throw std::logic_error("Mtx::det: diff sizes");

  if (n == 0) return 1;

  Mtx res(*this);
  long long prev = 1;
  int sign = 1;

  for (size_t k = 0; k < n - 1; k++) {
    size_t p = k;

    while (p < n && res.data.get(p * n + k) == 0) {
      p++;
    }
    if (p == n) {
      return 0;
    }
    if (p != k) {
      for (size_t j = 0; j < n; j++) {
        int temp = res.data.get(k * n + j);
        res.data.set(k * n + j, res.data.get(p * n + j));
        res.data.set(p * n + j, temp);
        }
      sign = -sign;
    }

    long long pivot = res.data.get(k * n + k);

    for (size_t i = k + 1; i < n; i++) {
      for (size_t j = k + 1; j < n; j++) {
        long long value =
          (pivot * res.data.get(i * n + j) -
           (long long)res.data.get(i * n + k) *
           res.data.get(k * n + j)) / prev;

        if (value > INT_MAX || value < INT_MIN)
          throw std::logic_error("Mtx::det: Overflow");

        res.data.set(i * n + j, (int)value);
      }
      res.data.set(i * n + k, 0);
    }

    prev = pivot;
  }

  long long result = sign * (long long)res.data.get((n - 1) * n + n - 1);

  if (result > INT_MAX || result < INT_MIN)
    throw std::logic_error("Mtx::det: Overflow");

  return (int)result;
}

Mtx Mtx::add_row(int init)
{
  Ints row(m, init);
  data.append(row);
  n++;
  return *this;
}
