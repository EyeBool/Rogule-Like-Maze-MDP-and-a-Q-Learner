# Rogule-Like-Maze-MDP-and-a-Q-Learner

A C++ implementation of a simple rogue-like maze game, and a q-learner to solve it.

## Game

A robot is placed on a rectangular grid, and is allowed to move up, down, left, or right. Each cell in the grid can be empty, a pit, a diamon, or the robot.

The robot is rewarded for moving on the grid as follows:
* in the direction of a wall: -10 points, the robot stays in place, and the game continues
* in the direction of a pit: -1000 points, the robot falls in the pit, and the game ends
* in the direction of an empty cell: -1 points, the robot moves to the empty cell, and the game continues
* in the direction of a diamon: +1000 points, the robot moves to the diamond cell, and the game ends

## RL

The maze is solved using the q-learning algorithm. Check the [Wikipedia entry](https://en.wikipedia.org/wiki/Q-learning#Algorithm) for more information.

## Program Structure

* `agent` class:
  - maintains the position of the robot
* `environment` class:
  - defines the cell types of the grid (will be refactored as an extensible class in a future version)
  - maintains the state of the grid
* `state` class:
  - a composition of `agent` and `environment`
  - represents a game state, and defines the game logic (will be refactored as an extensible class in a future version):
    - defines the actions that the robot can take, the corresponding reward, and the game state that follows
* `qlearner` class: self-explanatory
* `main.cpp`: driver

## Compilation

The whole program is self-contained, and written in vanilla C++. Compile it as usual.

## Sample Run

A sample run looks like this:

```
Starting position:

 r___
 xxx_
 _*x_
 _xx_
 ____

Action enum map:
 0 -> UP
 1 -> DOWN
 2 -> LEFT
 3 -> RIGHT

Starting q-learning with:
 number episodes: 2000
 number steps/episode: 100
 initial alpha: 1
 final alpha: 0.02
 gamma: 1
 epsilon (pr. of taking random action): 0.1

********** EPISODE: 1 **********

-- Step: 0 --

 r___
 xxx_
 _*x_
 _xx_
 ____

q function:
 action 0 -> 0
 action 1 -> 0
 action 2 -> 0
 action 3 -> 0

-- Step: 1 --

 r___
 xxx_
 _*x_
 _xx_
 ____

q function:
 action 0 -> -9.902
 action 1 -> 0
 action 2 -> 0
 action 3 -> 0

-- Step: 2 --

 ____
 rxx_
 _*x_
 _xx_
 ____

q function:
 action 0 -> 0
 action 1 -> 0
 action 2 -> 0
 action 3 -> 0

>> Episode 1: total reward = -1010 <<

********** EPISODE: 2 **********

-- Step: 0 --

 r___
 xxx_
 _*x_
 _xx_
 ____

q function:
 action 0 -> -9.902
 action 1 -> -980.4
 action 2 -> 0
 action 3 -> 0
 ```
 
 and it continues until it is done with all the episodes.
