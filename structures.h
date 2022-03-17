#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QString>
#include <QList>

enum CellType{Start, Target, Wall, Check, Empty, Path, Visited};

static const int cellSize = 10;
static const int boardSize = 31;
static const int screenWidth = 1050;
static const int screenHeight = 600;

struct IntVector
{
    int xNum; int yNum;

    IntVector(int x, int y)
    {
        this->xNum=x;
        this->yNum=y;
    }

    IntVector()
    {
        this->xNum=-1;
        this->yNum=-1;
    }

    int x()
    {
        return xNum;
    }

    int y()
    {
        return yNum;
    }
};

typedef std::pair<double, IntVector> Pair;

struct OneCell
{
  IntVector parentPosition = IntVector(0,0);
  CellType type = CellType::Empty;
  bool visited = false;
  float g=std::numeric_limits<float>().max(),h=std::numeric_limits<float>().max(),f=std::numeric_limits<float>().max();

  std::vector<IntVector> directions =
  {
      IntVector(0,-1),
      IntVector(1,0),
      IntVector(0,1),
      IntVector(-1,0)
  };

  OneCell(CellType type)
  {
      this->type = type;
  }

  OneCell(){}

  void ChangeGFH(float g, float f, float h)
  {
      this->g = g;
      this->h = h;
      this->f = f;
  }

  void CalculateF(float g, float h)
  {
      this->g = g;
      this->h = h;
      this->f = this->g + this->h;
  }
};

inline bool operator <(IntVector v1, IntVector v2)
{
    return v1.x() < v2.x() || v1.y() < v2.y();
}

inline bool operator >(IntVector v1, IntVector v2)
{
    return v1.x() > v2.x() || v1.y() > v2.y();
}

inline bool operator ==(IntVector v1, IntVector v2)
{
    return v1.x() == v2.x() && v1.y() == v2.y();
}

inline bool operator !=(IntVector v1, IntVector v2)
{
    return v1.x() != v2.x() || v1.y() != v2.y();
}

inline IntVector operator +(IntVector v1, IntVector v2)
{
    return IntVector(v1.x() + v2.x(),v1.y() + v2.y());
}

inline IntVector operator -(IntVector v1, IntVector v2)
{
    return IntVector(v1.x() - v2.x(),v1.y() - v2.y());
}

inline IntVector operator *(IntVector v1, int v2)
{
    return IntVector(v1.x() * v2,v1.y() * v2);
}

inline IntVector operator +(IntVector v1, int v2)
{
    return IntVector(v1.x() + v2,v1.y() + v2);
}
#endif // STRUCTURES_H
