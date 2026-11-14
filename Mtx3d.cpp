#include "classes.hpp"

void clearMtx() noexcept
{
  if (mtx == nullptr) {
    return;
  }
  for (size_t i = 0; i < n; i++) {
    if (mtx[i] == nullptr) {
      continue;
    }
    for (size_t j = 0; j < m; j++) {
      delete[] mtx[i][j];
    }
    delete[] mtx[i];
  }
  delete[] mtx;
  mtx = nullptr;
}

Mtx3d::Mtx3d():
  k(1),
  m(1),
  n(1),
  mtx(nullptr)
{
  mtx = new int** [n]{};
  try
  {
    for (size_t i = 0; i < n; i++) {
      mtx[i] = new int* [m]{};
      for (size_t j = 0; j < m; j++) {
        mtx[i][j] = new int [k]{};
        for (size_t l = 0; l < k; l++) {
          mtx[i][j][l] = 0;
        }
      }
    }
  } catch (...) {
    clearMtx();
    throw;
  }
}

Mtx3d::Mtx3d(size_t n, size_t m, size_t k, int field):
n(n),
  m(m),
  k(k),
  mtx(nullptr)
{
  mtx = new int** [n]{};
  try
  {
    for (size_t i = 0; i < n; i++) {
      mtx[i] = new int* [m]{};
      for (size_t j = 0; j < m; j++) {
        mtx[i][j] = new int [k]{};
        for (size_t l = 0; l < k; l++) {
          mtx[i][j][l] = 0;
        }
      }
    }
  } catch (...) {
    clearMtx();
    throw;
  }
}

Mtx3d::Mtx3d(const Mtx3d & rhs):
  n(rhs.n),
  m(rhs.m),
  k(rhs.k),
  mtx(nullptr)
{
  mtx = new int** [n]{};
  try
  {
    for (size_t i = 0; i < n; i++) {
      mtx[i] = new int* [m]{};
      for (size_t j = 0; j < m; j++) {
        mtx[i][j] = new int [k]{};
        for (size_t l = 0; l < k; l++) {
          mtx[i][j][l] = 0;
        }
      }
    }
  } catch (...) {
    clearMtx();
    throw;
  }
}

Mtx3d::~Mtx3d():
{
  clearMtx();
}

Mtx3d & Mtx3d::operator=(const Mtx3d & rhs)
{
  Mtx3d res(rhs);
  std::swap(n, res.n);
  std::swap(m, res.m);
  std::swap(k, res.k);
  std::swap(mtx, res.mtx);
  return *this;
}

Mtx3d & Mtx3d::operator=(Mtx3d && rhs) noexcept
{
  if (this == &rhs) {
    return *this;
  }
  std::swap(n, rhs.n);
  std::swap(m, rhs.m);
  std::swap(k, rhs.k);
  std::swap(mtx, rhs.mtx);
  return *this;
}

int** Mtx3d::operator[](size_t i)
{
  return mtx[i];
}

Mtx3d Mtx3d::operator+(const Mtx3d & rhs) const
{
  Mtx3d res(*this);
  long long first = 0;
  long long second = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      for (size_t l = 0; l < k; l++) {
        first = res[i][j][l];
        second = rhs[i][j][l];
        if (first > INT_MAX - second || first < INT_MIN + second) {
          throw std::logic_error("Mtx3d::+: Overflow");
        }
        res[i][j][l] = (int)(first + second);
      }
    }
  }
  return res;
}


