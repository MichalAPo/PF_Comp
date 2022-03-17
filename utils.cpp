#include "utils.h"

IntVector utils::CalculateOnBoardPosition(IntVector pos, IntVector boardPosition)
{
    return IntVector(((pos.x() - boardPosition.x())/cellSize),
                     ((pos.y() - boardPosition.y())/cellSize));
}

IntVector utils::CalculateWorldPosition(IntVector pos, IntVector boardPosition)
{
    return IntVector((pos.x() * cellSize) + boardPosition.x(),
                     (pos.y() * cellSize) + boardPosition.y());
}

bool utils::IsInBounds(IntVector pos,IntVector boardPos)
{
    if(boardPos == IntVector(0,0))
        return pos.x() >= boardPos.x()
            && pos.x() <= boardPos.x()+boardSize-1
            && pos.y() >= boardPos.y()
            && pos.y() <= boardPos.y()+boardSize-1;
    else
        return pos.x() >= boardPos.x()
            && pos.x() <= boardPos.x()+(boardSize*cellSize)
            && pos.y() >= boardPos.y()
            && pos.y() <= boardPos.y()+(boardSize*cellSize);
}

std::list<IntVector> utils::ListRemove(std::list<IntVector> list, IntVector item)
{
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if(*it==item)
        {
            list.remove(*it);
            return list;
        }
    }
    return list;
}

bool utils::ListContains(std::list<IntVector> list, IntVector item)
{
    for (auto it = list.begin(); it != list.end(); it++)
    {
        if(*it==item)
            return true;
    }
    return false;
}
