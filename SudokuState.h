
#ifndef SUDOKUSTATE_H // include guard
#define SUDOKUSTATE_H
typedef char StateArray[9][9];
class SudokuState
{

private:
    int isSolved = -2;
    int isFinalSolution();

public:
    SudokuState();
    SudokuState(char currentState[9][9]);
    ~SudokuState();

    bool checkBox(int locationX, int locationY);
    bool verticalLinesCheck();
    bool horizontalLinesCheck();
    bool checkDash();
    int checkSolved();

    std::string print();
    std::string printColor(SudokuState initialState);

    char state[9][9];
};

#endif /* SUDOKUSTATE_H */