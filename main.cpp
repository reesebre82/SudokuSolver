#include <stdlib.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "SudokuState.h"

using namespace std;

void bruteForceSearch(char initstate[9][9]);
SudokuState bruteForceAlgorithm(SudokuState currentState, const int spot[3]);

int main(int argc, char const *argv[])
{

    // char solved[9][9] = {
    //     {'8', '2', '7', '1', '5', '4', '3', '9', '6'},
    //     {'9', '6', '5', '3', '2', '7', '1', '4', '8'},
    //     {'3', '4', '1', '6', '8', '9', '7', '5', '2'},

    //     {'5', '9', '3', '4', '6', '8', '2', '7', '1'},
    //     {'4', '7', '2', '5', '1', '3', '6', '8', '9'},
    //     {'6', '1', '8', '9', '7', '2', '4', '3', '5'},

    //     {'7', '8', '6', '2', '3', '5', '9', '1', '4'},
    //     {'1', '5', '4', '7', '9', '6', '8', '2', '3'},
    //     {'2', '3', '9', '8', '4', '1', '5', '6', '7'}};
    // char template[9][9] = {
    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'},

    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'},

    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'},
    //     {'-', '-', '-', '-', '-', '-', '-', '-', '-'}};

    char initialState[9][9] = {
        {'8', '-', '2', '4', '9', '-', '-', '-', '7'},
        {'7', '-', '-', '2', '-', '8', '3', '-', '6'},
        {'-', '9', '6', '7', '-', '-', '-', '-', '-'},

        {'-', '-', '-', '8', '-', '7', '-', '-', '-'},
        {'-', '5', '-', '-', '4', '-', '-', '-', '-'},
        {'9', '-', '4', '5', '-', '-', '-', '-', '-'},

        {'3', '-', '-', '9', '-', '-', '-', '1', '-'},
        {'5', '6', '-', '3', '-', '-', '-', '2', '-'},
        {'-', '2', '-', '-', '-', '-', '-', '6', '3'}};

    bruteForceSearch(initialState);

    return 0;
}

void bruteForceSearch(char initstate[9][9])
{
    SudokuState initialState = SudokuState(initstate);
    SudokuState state = SudokuState(initstate);
    SudokuState solvedState;

    int spot[3] = {0, 0, 1};
    bool changed = false;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (state.state[i][j] == '-' && changed == false)
            {
                spot[0] = i;
                spot[1] = j;
                changed = true;
            }
    cout << "Starting location " << spot[0] << ", " << spot[1] << endl;
    while (solvedState.checkSolved() != -1)
    {
        char aChar = '0' + spot[2]++;

        state.state[spot[0]][spot[1]] = aChar;
        cout << state.print() << endl;
        cout << state.checkSolved() << endl;
        if (state.checkSolved() == -1)
            solvedState = SudokuState(state.state);

        SudokuState newState;
        if (state.checkSolved() > 90)
            newState = bruteForceAlgorithm(state, spot);

        // cout << newState.print() << endl
        //      << endl;

        if (newState.checkSolved() == -1)
            solvedState = SudokuState(newState.state);

        if (spot[2] == 10 && newState.checkSolved() != -1)
        {
            cout << "Fuck" << endl;
            exit(2);
        }
    }

    cout << endl
         << endl
         << endl;
    cout << "This is the solved state"
         << endl
         << endl;

    if (solvedState.checkSolved() == -2)
    {
        cout << state.print() << endl;
    }
    else
    {
        cout << solvedState.printColor(initialState) << endl;
    }
}

SudokuState bruteForceAlgorithm(SudokuState currentState, const int spot[3])
{
    SudokuState state = currentState;
    SudokuState solvedState;

    int location[3] = {spot[0], spot[1], 1};
    bool changed = false;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (state.state[i][j] == '-' && changed == false)
            {
                location[0] = i;
                location[1] = j;
                changed = true;
            }
    cout << location[0] << ", " << location[1] << endl;

    while (state.checkSolved() != -1)
    {
        char aChar = '0' + location[2]++;
        if (location[2] == 11)
            return currentState;
        SudokuState pureState = state;
        state.state[location[0]][location[1]] = aChar;
        cout << "Top of alogrithm" << endl;
        cout << location[0] << ", " << location[1] << endl;
        cout << state.printColor(pureState) << endl;
        // this_thread::sleep_for(chrono::nanoseconds(50000000));
        SudokuState newState;
        if (state.checkSolved() < 90)
        {
            if (state.checkSolved() == -1)
            {
                cout << "DID IT" << endl;
                return state;
            }
        }
        else
        {
            newState = bruteForceAlgorithm(state, location);
        }

        if (newState.checkSolved() == -1)
        {
            cout << "Solved" << endl;
            solvedState = SudokuState(newState.state);
            return solvedState;
        }
    }

    return currentState;
}