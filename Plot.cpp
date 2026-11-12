#include "classes.hpp"

Plot::Plot():
  data()
{}

void Plot::set(int x, int y)
{
  p_t point = {x, y};
  data.appendSort(point);
}

int Plot::calc(int x) const
{
  size_t id_x1 = data.findSortY(x);
  p_t p1 = data.get(id_x1);
  if (id_x1 == data.getVolume() || p1.x == x) {
    return p1.y;
  }
  size_t id_x2 = id_x1 + 1;
  p_t p2 = data.get(id_x2);
  return std::round((p2.y - p1.y) * 1.0 * (x - p1.x) / (p2.x - p1.x) + p1.y);
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
  p_t pl = data.get(0);
  p_t pr = data.get(1);
  size_t cnt = 0;
  for (size_t i = 1; i < data.getVolume(); i++) {
    if (isDiffState(pl, pr, y) && pl.y != y) {
      buff.append((pr.x - pl.x) * 1.0 * (y - p1.y) / (p2.y - p1.y) + p1.x);
      cnt++;
    } else if (pr.y == y) {
      if (pr.y == pl.y) {
        for (size_t j = pl.x+1; j <= pr.x; j++) {
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
  res = res.appendSort();
  std::swap(res, data);
  return *this;
}
