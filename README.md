# SudokuSolver

SudokuSolver Verizon 1.0

CPP Program that automatically solves any Sudoku Problem in seconds.

This program uses a brute force algorithm to check all possible cases
until a solution is found.

Here is the program solving a "Hard" Sudoku problem without any delays.

<img src = "https://media.giphy.com/media/h8ZcdDt40orSeXaJKk/giphy.gif" />

Here is the same program but with a small delay to show each cycles change.
<img src = "https://media.giphy.com/media/eiMhIztRZ6xBfnZaOM/giphy.gif" />

Right now, the input for the Sudoku Problem to be solved requires hard code.
(this will be updated in the next iteration)

All you have to do is input the correct characters in the initialState 2D
array at the top of main, compile and run.

This program also requires c++11 or later.<br>
Use this command to compile:<br>
g++ -o main main.cpp SudokuState.cpp -std=c++11

Use this command to run:<br>
./main
