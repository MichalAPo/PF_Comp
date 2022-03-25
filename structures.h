#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QString>
#include <QList>

enum CellType{Start, Target, Wall, Check, Empty, Path, Visited};

static const int cellSize = 4;
static const int boardSize = 61;
static const int spaceBetween = 25;
static const int screenWidth = 1050;
static const int screenHeight = 600;

struct IntVector
{
    int x; int y;

    IntVector(int x, int y)
    {
        this->x=x;
        this->y=y;
    }

    IntVector()
    {
        this->x=-1;
        this->y=-1;
    }
};

struct OneCell
{
  IntVector parentPosition = IntVector(0,0);
  CellType type = CellType::Empty;
  bool visited = false;
  float g=std::numeric_limits<float>().max(),h=std::numeric_limits<float>().max(),f=std::numeric_limits<float>().max();
  double travelCost;

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

  void ChangeFGH(float f, float g, float h)
  {
      this->g = g;
      this->h = h;
      this->f = f;
  }

  void ChangeCell(CellType type)
  {
      this->type = type;
      this->visited = false;
      this->f = std::numeric_limits<float>().max();
      this->g = std::numeric_limits<float>().max();
      this->h = std::numeric_limits<float>().max();
      this->directions =
        {
            IntVector(0,-1),
            IntVector(1,0),
            IntVector(0,1),
            IntVector(-1,0)
        };
  }
};

inline bool operator <(IntVector v1, IntVector v2)
{
    return v1.x < v2.x || v1.y < v2.y;
}

inline bool operator >(IntVector v1, IntVector v2)
{
    return v1.x > v2.x || v1.y > v2.y;
}

inline bool operator ==(IntVector v1, IntVector v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}

inline bool operator !=(IntVector v1, IntVector v2)
{
    return v1.x != v2.x || v1.y != v2.y;
}

inline IntVector operator +(IntVector v1, IntVector v2)
{
    return IntVector(v1.x + v2.x,v1.y + v2.y);
}

inline IntVector operator -(IntVector v1, IntVector v2)
{
    return IntVector(v1.x - v2.x,v1.y - v2.y);
}

inline IntVector operator *(IntVector v1, int v2)
{
    return IntVector(v1.x * v2,v1.y * v2);
}

inline IntVector operator +(IntVector v1, int v2)
{
    return IntVector(v1.x + v2,v1.y + v2);
}
#endif // STRUCTURES_H
