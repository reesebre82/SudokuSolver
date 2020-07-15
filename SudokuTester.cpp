#include <stdlib.h>
#include "SudokuTester.h"
#include "SudokuState.h"

#include <iostream>

bool SudokuTester::testStateSquare(int location, int state)
{
    SudokuState s = SudokuState();
    switch (state)
    {
    case 1:
        s = SudokuState(grid1);
        return (s.checkSolved() != location);
    case 2:
        s = SudokuState(grid2);
        return (s.checkSolved() != location);
    case 3:
        s = SudokuState(grid3);
        return (s.checkSolved() != location);
    case 4:
        s = SudokuState(grid4);
        return (s.checkSolved() != location);
    default:
        break;
    }

    exit(EXIT_FAILURE);
    return false;
}