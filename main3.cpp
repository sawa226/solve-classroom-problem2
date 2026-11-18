namespace zahovaev {
  enum Color { RED, GREEN, BLUE };
  class Colored;
  class Planar;
  class Point;
  class Vector;
  class ColoredPoint;
  class Brush;

  class Colored {
  public:
    virtual ~Colored() = default;
    virtual void setColor(Color color) = 0;
    virtual Color getColor() const = 0;
  };

  class Planar {
  public:
    virtual ~Planar() = default;
    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual abs_sqr() const = 0;
  };

  class Point: public Planar {
  private:
    int x_;
    int y_;
  public:
    Point(int x, int y):
      x_(x),
      y_(y)
    {}
    virtual ~Point();

    virtual int x() const override
    {
      return x;
    };
    virtual int y() const override
    {
      return y;
    };
    virtual abs_sqr() const override
    {
      return x * x + y * y;
    };
  };

  class Vector: public Planar {
  public:
    Vector(Point a, Point b):
      a_(a),
      b_(b)
    {}
    virtual ~Vector();

    virtual int x() const override
    {
      return b_.x - a_.x;
    };
    virtual int y() const override
    {
      return b_.y - a_.y;
    };
    virtual abs_sqr() const override
    {
      return x() * x() + y() * y();
    };
  private:
    Point a_;
    Point b_;
  };

  class ColoredPoint: public Planar, public Colored {
  public:
    ColoredPoint(Point a, Color c):
      a_(a),
      c_(c)
    {}
    virtual ~ColoredPoint();

    virtual int x() const override
    {
      return a_.x();
    };
    virtual int y() const override
    {
      return a_.y();
    };
    virtual abs_sqr() const override
    {
      return a_.abs_sqr();
    };
    virtual void setColor(Color color) override
    {
      c_ = color;
    };
    virtual Color getColor() const override
    {
      return c_;
    };
  private:
    Point a_;
    Color c_;
  };

  class Brush: public Collored {
  public:
    Brush(Color color):
      c_(color)
    {}
    virtual ~Brush();

    virtual void setColor(Color color) override
    {
      c_ = color;
    };
    virtual Color getColor() const override
    {
      return c_;
    };
  private:
    Color c_;
  };
};

int main()
{
  return 0;
}
