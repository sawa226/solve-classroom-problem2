#include "classes.hpp"
#include <cmath>
#include <stdexcept>

Plot::Plot():
  data()
{}

Plot::Plot(size_t size, p_t point):
  data(size, point)
{};

void Plot::set(int x, int y)
{
  p_t point = {x, y};
  data.appendSort(point);
}

int Plot::calc(int x) const
{
  if (data.getVolume() == 0) {
    throw std::logic_error("Plot::calc: your massive too smal");
  }
  if (x < data.get(0).x || x > data.get(data.getVolume()-1).x) {
    throw std::out_of_range("Plot::calc: out of range");
  }
  size_t id_x1 = data.findSortY(x);
  p_t p1 = data.get(id_x1);
  if (p1.x == x) {
    return p1.y;
  }
  p_t p2 = data.get(id_x1 - 1);
  return (int)std::round((p2.y - p1.y) * 1.0 * (x - p1.x) / (p2.x - p1.x) + p1.y);
}

bool Plot::isDiffState(p_t pl, p_t pr, int y) const
{
  if (pl.y <= y && pr.y > y || pl.y > y && pr.y <= y) {
    return true;
  }
  return false;
}

size_t Plot::solve(int y, Ints& buff) const
{
  if (data.getVolume() == 0) {
    throw std::logic_error("Plot::solve: your massive too smal");
  }
  if (data.getVolume() == 1) {
    if (data.get(0).y == y) {
      buff.append(data.get(0).x);
      return 1;
    }
    return 0;
  }
  p_t pl = {0, 0};
  p_t pr = {0, 0};
  size_t cnt = 0;
  for (size_t i = 1; i < data.getVolume(); i++) {
    pr = data.get(i);
    pl = data.get(i-1);
    if (isDiffState(pl, pr, y) && pl.y != y && pl.y != pr.y) {
      buff.append((int)std::round((pr.x - pl.x) * 1.0 * (y - pl.y) / (pr.y - pl.y) + pl.x));
      cnt++;
    } else if (pr.y == y) {
      if (pr.y == pl.y) {
        for (int j = pl.x+1; j <= pr.x; j++) {
          buff.append(j);
          cnt++;
        }
      } else {
        buff.append(pr.x);
        cnt++;
      }
    }
  }
  return cnt;
}

Points Plot::append(p_t point)
{
  Points res(data);
  res = res.appendSort(point);
  return res;
}
