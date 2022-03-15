#include "testwindow.h"

testwindow::testwindow(IntVector pos)
{
    boardPosition = pos;
    CreateBoard();
}

void testwindow::CreateBoard()
{
    for(int i=0; i<boardSize; i++){
        for(int j=0; j<boardSize; j++){
                board[i][j] = OneCell();
            }
        }
}

void testwindow::ChangeType(IntVector pos, CellType type)
{
    board[pos.x()][pos.y()].type=type;
}

