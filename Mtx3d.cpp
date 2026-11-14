#include "classes.hpp"
#include <algorithm>
#include <climits>
#include <stdexcept>

void Mtx3d::clearMtx() noexcept
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
    mtx[0] = new int* [m]{};
    mtx[0][0] = new int [k]{};
    mtx[0][0][0] = 0;
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
          mtx[i][j][l] = field;
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
          mtx[i][j][l] = rhs[i][j][l];
        }
      }
    }
  } catch (...) {
    clearMtx();
    throw;
  }
}

Mtx3d::~Mtx3d()
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

const int* const* Mtx3d::operator[](size_t i) const
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

Mtx3d Mtx3d::eraseX(size_t l, size_t r)
{
  if (r == 0) {
    r = l+1;
  }
  if (l >= r || r > m) {
    throw std::logic_error("");
  }
  if (m - r > ULONG_MAX - l) {
    throw std::logic_error("");
  }
  Mtx3d res(n, m - r + l, k);
  size_t jj = 0;
  for (size_t i = 0; i < n; i++) {
    jj = 0;
    for (size_t j = 0; j < m; j++) {
      if (j < r && j >= l) {
        continue;
      }
      for(size_t s = 0; s < k; s++) {
        res[i][jj][s] = mtx[i][j][s];
      }
      jj++;
    }
  }
  return res;
}

Mtx3d Mtx3d::eraseY(size_t l, size_t r)
{
  if (r == 0) {
    r = l+1;
  }
  if (l >= r || r > n) {
    throw std::logic_error("");
  }
  if (n - r > ULONG_MAX - l) {
    throw std::logic_error("");
  }
  Mtx3d res(n - r + l, m, k);
  size_t ii = 0;
  for (size_t i = 0; i < n; i++) {
    if (i < r && i >= l) {
      continue;
    }
    for (size_t j = 0; j < m; j++) {
      for (size_t s = 0; s < k; s++) {
        res[ii][j][s] = mtx[i][j][s];
      }
    }
    ii++;
  }
  return res;
}


Mtx3d Mtx3d::eraseZ(size_t l, size_t r)
{
  if (r == 0) {
    r = l+1;
  }
  if (l >= r || r > k) {
    throw std::logic_error("");
  }
  if (k - r > ULONG_MAX - l) {
    throw std::logic_error("");
  }
  Mtx3d res(n, m, k - r + l);
  size_t ss = 0;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      ss = 0;
      for (size_t s = 0; s < k; s++) {
        if (s < r && s >= l) {
          continue;
        }
        res[i][j][ss] = mtx[i][j][s];
      }
      ss++;
    }
  }
  return res;
}

Mtx3d Mtx3d::erase(size_t r, size_t l)
{
  if (r > ULONG_MAX - l || (r + l) > m || (r + l) > m || (r + l) > k) {
    throw std::logic_error("");
  }
  Mtx3d res = this->eraseX(m-r, m).eraseY(n-r, n).eraseZ(k-r, k);
  if (l) {
    res = res.eraseX(0, l).eraseY(0, l).eraseZ(0, l);
  }
  return res;
}

Mtx3d Mtx3d::insertX(const Mtx3d& mass, size_t id)
{
  if (id > m || mass.getN() != n || mass.getK() != k || mass.getM() > ULONG_MAX - m) {
    throw std::logic_error("");
  }
  Mtx3d res(n, mass.getM() + m, k);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < id; j++) {
      for (size_t l = 0; l < k; l++) {
        res[i][j][l] = mtx[i][j][l];
      }
    }
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < mass.getM(); j++) {
      for (size_t l = 0; l < k; l++) {
        res[i][j + id][l] = mass[i][j][l];
      }
    }
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = id; j < m; j++) {
      for (size_t l = 0; l < k; l++) {
        res[i][j + mass.getM()][l] = mtx[i][j][l];
      }
    }
  }
  return res;
}

Mtx3d Mtx3d::insertY(const Mtx3d& mass, size_t id)
{
  if (id > n || mass.getM() != m || mass.getK() != k || mass.getN() > ULONG_MAX - n) {
    throw std::logic_error("");
  }
  Mtx3d res(n + mass.getN(), m, k);
  for (size_t i = 0; i < id; i++) {
    for (size_t j = 0; j < m; j++) {
      for (size_t l = 0; l < k; l++) {
        res[i][j][l] = mtx[i][j][l];
      }
    }
  }
  for (size_t i = 0; i < mass.getN(); i++) {
    for (size_t j = 0; j < m; j++) {
      for (size_t l = 0; l < k; l++) {
        res[i + id][j][l] = mass[i][j][l];
      }
    }
  }
  for (size_t i = id; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      for (size_t l = 0; l < k; l++) {
        res[i + mass.getN()][j][l] = mtx[i][j][l];
      }
    }
  }
  return res;
}

Mtx3d Mtx3d::insertZ(const Mtx3d& mass, size_t id)
{
  if (id > k || mass.getM() != m || mass.getN() != n || mass.getK() > ULONG_MAX - k) {
    throw std::logic_error("");
  }
  Mtx3d res(n, m, k + mass.getK());
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      for (size_t l = 0; l < id; l++) {
        res[i][j][l] = mtx[i][j][l];
      }
    }
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      for (size_t l = 0; l < mass.getK(); l++) {
        res[i][j][l + id] = mass[i][j][l];
      }
    }
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      for (size_t l = id; l < k; l++) {
        res[i][j][l + mass.getK()] = mtx[i][j][l];
      }
    }
  }
  return res;
}


Mtx3d Mtx3d::insert(const Mtx3d& mass, size_t id)
{
  if (mass.getN() == n && mass.getK() == k) {
    return this->insertX(mass, id);
  } else if (mass.getM() == m && mass.getK() == k) {
    return this->insertY(mass, id);
  } else if (mass.getN() == n && mass.getM() == m) {
    return this->insertZ(mass, id);
  }
  throw std::logic_error("");
}

int Mtx3d::conv(int (*func)(int a, int b))
{
  int temp = mtx[0][0][0];
  for (size_t l = 1; l < k; l++) {
    temp = func(temp, mtx[0][0][l]);
  }
  for (size_t j = 1; j < m; j++) {
    for (size_t l = 0; l < k; l++) {
      temp = func(temp, mtx[0][j][l]);
    }
  }
  for (size_t i = 1; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      for (size_t l = 0; l < k; l++) {
        temp = func(temp, mtx[i][j][l]);
      }
    }
  }
  return temp;
}
