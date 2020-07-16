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
    //Empty template to use when creating a new Sudoku problem to be solved
    // char initialState[9][9] = {
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
    //creates three states from the inital sudoku problem
    SudokuState initialState = SudokuState(initstate);
    SudokuState state = SudokuState(initstate);
    SudokuState solvedState;

    /**
     * Three different place holders.
     * spot[0] = current x position
     * spot[1] = current y position
     * spot[2] = current x,
     */
    int spot[3] = {0, 0, 1};

    //Changed is used to see if the value has been changed since the original state
    bool changed = false;

    /**
     * for loop to find the first location location of -
     * and sets the x and y location to the location of -
     * in the 2D array 
     */
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (state.state[i][j] == '-' && changed == false)
            {
                spot[0] = i;
                spot[1] = j;
                changed = true;
            }

    //Begin of brute force. Repeat until solved;
    while (solvedState.checkSolved() != -1)
    {
        char aChar = '0' + spot[2]++;

        //Set the current - to a digit, and print it out
        state.state[spot[0]][spot[1]] = aChar;
        cout << state.print() << endl;

        //if solved, sets solvedState equal to current state
        if (state.checkSolved() == -1)
            solvedState = SudokuState(state.state);

        SudokuState newState;
        //If solved reponse is greater than 90, entry is valid; start algorithm
        if (state.checkSolved() > 90)
            newState = bruteForceAlgorithm(state, spot);

        //Check if newly generated state was a solved state
        if (newState.checkSolved() == -1)
            solvedState = SudokuState(newState.state);

        //Exit statement if no solutions are found
        if (spot[2] == 10 && newState.checkSolved() != -1)
        {
            cout << "No solution found." << endl;
            cout << "Double check input and please report input if error exists." << endl;
            exit(2);
        }
    }

    //Generic output when solution is found
    cout << "\n\n\nThis is the solved state\n\n";

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

        //Comment this line out for faster speed and to remove delay
        //this_thread::sleep_for(chrono::nanoseconds(5000000));

        SudokuState newState;
        if (state.checkSolved() < 90)
        {
            if (state.checkSolved() == -1)
            {
                return state;
            }
        }
        else
        {
            newState = bruteForceAlgorithm(state, location);
        }

        if (newState.checkSolved() == -1)
        {
            solvedState = SudokuState(newState.state);
            return solvedState;
        }
    }

    return currentState;
}