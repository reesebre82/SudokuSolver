#include <iostream>
#include "SudokuState.h"
#include <string>

SudokuState::SudokuState(char currentState[9][9])
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            state[i][j] = currentState[i][j];
    isSolved = isFinalSolution();
}
SudokuState::SudokuState()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            state[i][j] = '-';
}
SudokuState::~SudokuState()
{
    // delete state;
}

int SudokuState::isFinalSolution()
{
    //Check each box
    //Top left box
    if (!checkBox(1, 1))
        return 1;

    //Top Middle box
    if (!checkBox(1, 2))
        return 2;

    //Top Right box
    if (!checkBox(1, 3))
        return 3;

    //Middle Left box
    if (!checkBox(2, 1))
        return 4;

    //Middle Box
    if (!checkBox(2, 2))
        return 5;

    //Middle Right
    if (!checkBox(2, 3))
        return 6;

    //Bottom Left
    if (!checkBox(3, 1))
        return 7;

    //Bottom Middle
    if (!checkBox(3, 2))
        return 8;

    //Bottom Right
    if (!checkBox(3, 3))
        return 9;

    //Check each Vertical line
    if (!verticalLinesCheck())
        return 10;
    //Check each Horizontal line
    if (!horizontalLinesCheck())
        return 11;

    if (checkDash())
        return 99;

    return -1;
}

bool SudokuState::checkDash()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (state[i][j] == '-')
                return true;
    return false;
}

bool SudokuState::checkBox(int locationX, int locationY)
{
    char currentSection[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
    int spot = 0;

    int startX = (locationX - 1) * 3;
    int startY = (locationY - 1) * 3;

    for (int i = startX; i < startX + 3; i++)
        for (int j = startY; j < startY + 3; j++)
            if (state[i][j] != '-')
                currentSection[spot++] = state[i][j];

    for (int i = 0; i < spot; i++)
        for (int j = i + 1; j < spot; j++)
            if (currentSection[i] == currentSection[j])
                return false;
    return true;
}

bool SudokuState::verticalLinesCheck()
{
    for (int i = 0; i < 9; i++)
    {
        char currentSection[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
        int spot = 0;
        for (int j = 0; j < 9; j++)
            if (state[j][i] != '-')
                currentSection[spot++] = state[j][i];

        for (int i = 0; i < spot; i++)
            for (int j = i + 1; j < spot; j++)
                if (currentSection[i] == currentSection[j])
                    return false;
    }
    return true;
}

bool SudokuState::horizontalLinesCheck()
{
    for (int i = 0; i < 9; i++)
    {
        char currentSection[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
        int spot = 0;

        for (int j = 0; j < 9; j++)
            if (state[i][j] != '-')
                currentSection[spot++] = state[i][j];
        for (int i = 0; i < spot; i++)
            for (int j = i + 1; j < spot; j++)
                if (currentSection[i] == currentSection[j])
                    return false;
    }
    return true;
}

int SudokuState::checkSolved()
{
    isSolved = isFinalSolution();
    return isSolved;
}

std::string SudokuState::print()
{
    std::string returnString = "";

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            returnString += state[i][j];
            returnString += "  ";
            if (j % 3 == 2)
            {
                returnString += " ";
            }
        }
        returnString += "\n";
        if (i % 3 == 2)
        {
            returnString += "\n";
        }
    }

    return returnString;
}

std::string SudokuState::printColor(SudokuState initialState)
{
    std::string returnString = "";
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (state[i][j] == initialState.state[i][j])
                returnString += state[i][j];
            else
            {
                returnString += "\033[1;32m";
                returnString += state[i][j];
                returnString += "\033[0m";
            }
            returnString += "  ";
            if (j % 3 == 2)
            {
                returnString += " ";
            }
        }
        returnString += "\n";
        if (i % 3 == 2)
        {
            returnString += "\n";
        }
    }
    return returnString;
}