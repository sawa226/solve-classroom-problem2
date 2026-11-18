#include <cstddef>

class Ints {
private:
  void resize(size_t len = 0);
  size_t size;
  size_t volume;
  int* data;
public:
  Ints();
  Ints(size_t size, int field);
  Ints(size_t size);
  Ints(const Ints& rhs);
  ~Ints();
  Ints& operator=(const Ints& rhs);
  Ints& operator=(Ints&& rhs) noexcept;
  Ints operator+(const Ints& rhs);

  size_t getSize() const noexcept
  {
    return size;
  };
  size_t getVolume() const noexcept
  {
    return volume;
  };
  void set(size_t id, int i) noexcept
  {
    data[id] = i;
  };
  void setSave(size_t id, int i);
  int get(size_t id) const noexcept
  {
    return data[id];
  };
  int getSave(size_t id) const;
  size_t find(int i) const;
  size_t findSort(int i) const;
  Ints insert(
      int i,
      bool (*func)(int, int) =
          [](int a, int b)
      {
        return a > b;
      });
  Ints insert(
      int i, const Ints& mas, int k,
      bool (*func)(int, int) =
          [](int a, int b)
      {
        return a > b;
      });
  Ints append(int i);
  Ints appendSort(
      int i,
      bool (*func)(int, int) =
          [](int a, int b)
      {
        return a > b;
      });
  Ints append(const Ints& b);
  Ints appendSort(
      const Ints& i,
      bool (*func)(int, int) =
          [](int a, int b)
      {
        return a > b;
      });
};

struct p_t {
  int x;
  int y;
};

class Points {
private:
  Ints datax;
  Ints datay;
public:
  Points();
  Points(size_t size, p_t point);
  ~Points() = default;
  Points(const Points& rhs) = default;
  Points& operator=(const Points& rhs) = default;
  Points& operator=(Points&& rhs) noexcept = default;

  size_t getVolume() const noexcept
  {
    return datax.getVolume();
  };
  void set(size_t id, p_t point) noexcept;
  void setSave(size_t id, p_t point);
  p_t get(size_t id) const noexcept;
  p_t getSave(size_t id) const;
  size_t findSortY(int x) const;
  Points append(p_t point);
  Points appendSort(p_t point);
};

class Plot {
private:
  Points data;
  bool isDiffState(p_t pl, p_t pr, int y) const;
public:
  Plot();
  Plot(size_t size, p_t point);
  Plot(const Plot& rhs) = default;
  Plot& operator=(const Plot& rhs) = default;
  Plot& operator=(Plot&& rhs) noexcept = default;

  void set(int x, int y);
  int calc(int x) const;
  size_t solve(int y, Ints& buff) const;
  Points append(p_t point);
};

class Mtx {
private:
  size_t n;
  size_t m;
  Ints data;
public:
  Mtx();
  Mtx(size_t n, size_t m);
  Mtx(const Mtx& rhs) = default;
  Mtx& operator=(const Mtx& rhs) = default;
  Mtx& operator=(Mtx&& rhs) noexcept = default;

  size_t getVolume() const
  {
    return n * m;
  };
  Mtx sum(const Mtx& b);
  Mtx mul(int b);
  Mtx mul(const Mtx& b);
  Mtx transpose() const;
  int det() const;
  Mtx add_row(int init);
};

class Mtx3d {
private:
  size_t n;
  size_t m;
  size_t k;
  int*** mtx;
  void clearMtx() noexcept;
public:
  Mtx3d();
  Mtx3d(size_t n, size_t m, size_t k, int field = 0);
  Mtx3d(const Mtx3d& rhs);
  ~Mtx3d();
  Mtx3d& operator=(const Mtx3d& rhs);
  int** operator[](size_t i);
  const int* const* operator[](size_t i) const;
  Mtx3d& operator=(Mtx3d&& rhs) noexcept;
  Mtx3d operator+(const Mtx3d& rhs) const;

  size_t getN() const
  {
    return n;
  };
  size_t getM() const
  {
    return m;
  };
  size_t getK() const
  {
    return k;
  };
  Mtx3d eraseX(size_t l, size_t r = 0);
  Mtx3d eraseY(size_t l, size_t r = 0);
  Mtx3d eraseZ(size_t l, size_t r = 0);
  Mtx3d erase(size_t r, size_t l = 0);
  Mtx3d insertX(const Mtx3d& mass, size_t id);
  Mtx3d insertY(const Mtx3d& mass, size_t id);
  Mtx3d insertZ(const Mtx3d& mass, size_t id);
  Mtx3d insert(const Mtx3d& mass, size_t id);
  int conv(int (*func)(int a, int b));
};
