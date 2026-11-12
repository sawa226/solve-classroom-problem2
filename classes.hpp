#pragma once
#include <cstddef>

class Ints
{
private:
  void resize(size_t len = 0);
  size_t volume;
  size_t size;
  int * data;
public:
  Ints();
  Ints(size_t size, int field);
  Ints(size_t size);
  Ints(const Ints & rhs);
  ~Ints();
  Ints & operator=(const Ints & rhs);
  Ints & operator=(Ints && rhs) noexcept;
  Ints operator+(const Ints & rhs);

  size_t getSize() const noexcept {return size;};
  size_t getVolume() const noexcept {return volume;};
  void set(size_t id, int i) noexcept {data[id] = i;};
  void setSave(size_t id, int i);
  int get(size_t id) const noexcept {return data[id];};
  int getSave(size_t id) const;
  size_t find(int i) const;
  size_t findSort(int i) const;
  Ints insert(int i, bool (*func)(int, int) [] (int a, int b) {return a > b;});
  Ints insert(int i, const Ints& mas, int k, bool (*func)(int, int) = [] (int a, int b) {return a > b;});
  Ints append(int i);
  Ints appendSort(int i, bool (*func)(int, int) = [] (int a, int b) {return a > b;});
  Ints append(const Ints& b);
  Ints appendSort(const Ints& i);
};

struct p_t
{
  int x;
  int y;
};

class Points
{
private:
  Ints datax;
  Ints datay;
public:
  Points();
  Points(size_t size, p_t point);
  ~Points() = default;
  Points(const Points & rhs) = default;
  Points & operator=(const Points & rhs) = default;
  Points & operator=(const Points && rhs) noexcept = default;

  size_t getVolume() {return datax.getVolume();};
  void set(size_t id, p_t point) noexcept;
  void setSave(size_t id, p_t point);
  p_t get(size_t id) const noexcept;
  p_t getSave(size_t id) const;
  size_t findSortY(int x) const;
  Points append(p_t point);
  Points appendSort(p_t point);
};

class Plot
{
private:
  Points data;
  bool isDiffState(p_t pl, p_t pr, int y);
public:
  Plot();
  Plot(size_t size, p_t point);
  Plot(const Plot & rhs) = default;
  Plot & operator=(const Plot & rhs) = default;
  Plot & operator=(Plot && rhs) noexcept = default;

  void set(int x, int y);
  int calc(int x) const;
  size_t solve(int y, Ints& buff) const;
  Points append(p_t point);
};

class Mtx
{
private:
  size_t n;
  size_t m;
  Ints data;
public:
  Mtx();
  Mtx(size_t n, size_t m);
  Mtx(const Mtx & rhs) = default;
  Mtx & operator=(const Mtx & rhs) = default;
  Mtx & operator=(Mtx && rhs) noexcept = default;

  size_t getVolume() const {return n * m};
  Mtx sum(const Mtx& b);
  Mtx mul(int b);
  Mtx mul(const Mtx& b);
  Mtx transpose() const;
  int det() const;
  Mtx add_row(int init);
};

class Mtx3d
{
private:
  size_t n;
  size_t m;
  size_t k;
  int *** mtx;
public:
  Mtx3d();
  Mtx3d(size_t n, size_t m, size_t k, int field);
  Mtx3d(const Mtx3d & rhs);
  ~Mtx3d();
  Mtx3d & operator=(const Mtx3d & rhs);
  Mtx3d & operator=(Mtx3d && rhs) noexcept;
  Mtx3d & operator[](const Mtx3d & rhs, size_t state = 10000000);
  Mtx3d & operator[](const Mtx3d & rhs, int state);
  Mtx3d & operator[](const Mtx3d & rhs, short state);
  Mtx3d & operator+(const Mtx3d & rhs);


}
