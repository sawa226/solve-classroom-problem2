#pragma once

class Ints
{
private:
  int * resize(int * data);
  size_t volume;
  size_t size;
  int * data;
public:
  Ints();
  Ints(size_t size, int field);
  Ints(const Ints & rhs);
  Ints & operator=(const Ints & rhs);
  Ints & operator=(const Ints && rhs) noexcept;
  Ints operator+(const Ints & rhs);
  ~Ints();

  size_t getSize() const noexcept {return size};
  void set(size_t id, int i) noexcept {data[id] = i};
  void setSave(size_t id, int i);
  int get(size_t id) const noexcept {return data[id]};
  int getSave(size_t id) const;
  Ints append(int i);
  Ints append(Ints b);
};

class p_t
{
  int x;
  int y;
};

class Points
{
private:
  Ints data;
public:
  Points();
  Points(size_t size, p_t point);
  Points(const Points & rhs) = default;
  Points & operator=(const Points & rhs) = default;
  Points & operator=(const Points && rhs) noexcept = default;

  void set(size_t id, p_t point) noexcept;
  void setSave(size_t id, p_t point);
  int get(size_t id) const noexcept {return data[id];};
  int getSave(size_t id);
  Points append(p_t point);
};

class Plot
{
private:
  Ints data;
public:
  Plot();
  Plot(size_t size, p_t point);
  Plot(const Plot & rhs) = default;
  Plot & operator=(const Plot & rhs) = default;
  Plot & operator=(Plot && rhs) noexcept = default;

  void set(int x, int y);
  int calc(int x) const;
  void solve(int x, Ints& buff) const;
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

  Mtx sum(Mtx b);
  Mtx mul(Mtx b);
  Mtx transpose() const;
  int det() const;
  Mtx add_row(int init);
};
