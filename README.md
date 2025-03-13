# Tic-Tac-Toe (C++)

This is a simple Tic-Tac-Toe game implemented in C++ that supports both single-player mode (vs a computer opponent) and multiplayer mode (two players).

## Features
- Play against another player or a computer opponent.
- Uses the **Minimax algorithm** for optimal moves.
- Simple text-based interface.
- Supports player selection of `X` or `O` in single-player mode.

## How to Play
1. Compile the code using a C++ compiler (e.g., g++).
2. Run the executable.
3. Choose the mode:
   - `1` for Single-player (vs computer opponent)
   - `2` for Multiplayer
4. If playing against the computer, choose your symbol (`X` or `O`).
5. Enter your move by selecting a position (1-9) corresponding to the board layout:
   ```
   1 | 2 | 3
   --|---|--
   4 | 5 | 6
   --|---|--
   7 | 8 | 9
   ```
6. The game continues until a player wins or the board is full.

## Compilation & Execution
### Using g++:
```sh
 g++ -o tic_tac_toe tic_tac_toe.cpp
 ./tic_tac_toe
```

## Minimax Algorithm (Game Strategy)
The computer opponent is implemented using the **Minimax algorithm**, a recursive strategy for decision-making in games. This algorithm evaluates all possible moves and selects the best possible outcome to ensure an optimal strategy.

### Learn More About Minimax:
- [Minimax Algorithm Explained](https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/)

⚠ **Note:** While often referred to as "AI," this implementation does not involve machine learning or neural networks. It is purely a rule-based approach that guarantees the best possible move.

## Example Gameplay
```
Tic-Tac-Toe! Mode:
1. Single (vs Computer)
2. Multi
Choose: 1
Your symbol (X/O): X

X | O | X
--|---|--
  | X | O
--|---|--
O |   |  

Player X, your move (1-9): 8
```

## Future Improvements
- Add a GUI for better user experience.
- Implement an AI difficulty level.
- Add an option to restart the game.

## License
This project is open-source. Feel free to modify and improve it!

