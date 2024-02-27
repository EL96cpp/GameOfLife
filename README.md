# GameOfLife
## Description
This project is an implementation of Horton Conway's cellular automaton Game of Life. The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves.

## Rules
The universe of the Game of Life is (an infinite by default, but in this project limited by $170\times220$ cells rectangle), two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead (or populated and unpopulated, respectively). Every cell interacts with its eight neighbors, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

* Any live cell with fewer than two live neighbors dies, as if by underpopulation.
* Any live cell with two or three live neighbors lives on to the next generation.
* Any live cell with more than three live neighbors dies, as if by overpopulation.
* Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed, live or dead. Births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick. Each generation is a pure function of the preceding one. The rules continue to be applied repeatedly to create further generations. 

## Game speed
In this project you can change game's speed. Game's speed represented by the integer value, it varies from 1 to 5. Game's speed is determined by QTimer signals, the intervals of which are in the following dependence on the integer speed variable: $\frac{1000}{speed^{2}}$ milliseconds.
Corresponding intervals for each integer value:
| Integer value | Interval in milliseconds |
| :---: | :---: |
| 1 | 1000 |
| 2 | 250 |
| 3 | 111.1 |
| 4 | 62.5 |
| 5 | 40 |

## Saving and loading game
You can save and load game scenes, created in game redactor. Each game scene is saved in .txt file, in project build's subdirectory 'Game saves'. Correct file consists of 170 lines with 220 numeric values in each. 1 encodes alive cell, 0 - dead. 

## Tests 
Tests are written in GoogleTest framework as a separate Qt project and check Game class functionality.


