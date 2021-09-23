#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QString>
#include <QVector2D>
#include <QList>

enum CellType{Start, Goal, Wall, Check, Empty, Path, Visited};

constexpr inline bool operator <(QVector2D v1, QVector2D v2) noexcept
    {
        return v1.x() < v2.x() || v1.y() < v2.y();
    }

static int cellSize = 10;
static int screenWidth = 1050;
static int screenHeight = 600;

struct OneCell
{
  QVector2D position;
  QVector2D parentPosition = QVector2D(0,0);
  CellType type;
  bool visited = false;
  float g,h,f;

  QList<QVector2D> directions =
  {
      QVector2D(0,-1),
      QVector2D(1,0),
      QVector2D(0,1),
      QVector2D(-1,0)
  };

  OneCell(QVector2D position = QVector2D(0,0), CellType type = CellType::Empty)
  {
      this->position = position;
      this->type = type;
  }

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

  bool operator ==(const OneCell r)
  {
      return this->position.x() == r.position.x() && this->position.y() == r.position.y();
  }
};

#endif // STRUCTURES_H
