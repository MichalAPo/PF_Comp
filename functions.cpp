#include "functions.h"

functions::functions()
{

}

IntVector functions::CalculateOnBoardPosition(IntVector pos, IntVector boardPosition)
{
    return IntVector(((pos.x() - boardPosition.x())/cellSize),
                     ((pos.y() - boardPosition.y())/cellSize));
}

IntVector functions::CalculateWorldPosition(IntVector pos, IntVector boardPosition)
{
    return IntVector((pos.x() * cellSize) + boardPosition.x(),
                     (pos.y() * cellSize) + boardPosition.y());
}

bool functions::IsInBounds(IntVector pos,IntVector boardPos)
{
    if(boardPos == IntVector(0,0))
        return pos.x() >= boardPos.x()
            && pos.x() <= boardPos.x()+boardSize
            && pos.y() >= boardPos.y()
            && pos.y() <= boardPos.y()+boardSize;
    else
        return pos.x() >= boardPos.x()
            && pos.x() <= boardPos.x()+(boardSize*cellSize)
            && pos.y() >= boardPos.y()
            && pos.y() <= boardPos.y()+(boardSize*cellSize);
}
