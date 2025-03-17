# Enhanced Tic-Tac-Toe (C++)

A feature-rich Tic-Tac-Toe implementation in C++ that supports variable board sizes, configurable win conditions, and multiple difficulty levels.

## Features

* **Flexible Game Parameters**:
   * Variable board size (3x3, 4x4, 5x5, etc.)
   * Configurable win condition (3-in-a-row, 4-in-a-row, etc.)
* **Multiple Game Modes**:
   * Single-player against AI with three difficulty levels
   * Multiplayer mode for two human players
* **Advanced AI Opponent**:
   * Easy mode: Random moves
   * Medium mode: Minimax algorithm with limited depth
   * Hard mode: Minimax algorithm with optimized depth
   * Alpha-beta pruning for improved performance
   * Opening book for common positions (3x3 standard board)
* **Game Management**:
   * Save/load game functionality
   * Undo move capability
   * Score tracking across multiple games
* **User-Friendly Interface**:
   * Dynamic board display adapts to board size
   * Clear menu system and instructions
   * Input validation and error handling

## How to Play

1. Compile the code using a C++ compiler:

```sh
g++ -o tictactoe tictactoe.cpp
```

2. Run the executable:

```sh
./tictactoe
```

3. Follow the prompts to set up your game:
   * Choose board size (e.g., 3 for 3x3 board)
   * Set win condition (e.g., 3 for 3-in-a-row)
   * Select game mode (Single player or Multiplayer)
   * If playing against AI, choose difficulty level
4. During gameplay:
   * Enter row and column numbers to make your move (e.g., "1 2")
   * Use special commands as described in the Command Reference section below
5. The game continues until a player wins or the board is full.

## Board Layout

For a standard 3x3 board, positions are numbered as follows:

```
  1 2 3
1 X | O | X
  ---------
2   | X | O
  ---------
3 O |   |  
```

Enter row and column numbers to make your move. For example, "1 2" would place your symbol in the first row, second column.

## Command Reference

During gameplay, you can use the following commands:

| Command | Description |
| ------- | ----------- |
| `row column` | Make a move (e.g., "1 2" for first row, second column) |
| `-1 1` | Undo your last move |
| `-1 2` | Save the current game |
| `-1 3` | Load a previously saved game |

Example usage:
* To place your symbol in the top-right corner: `1 3`
* To undo your last move: `-1 1`
* To save the current game: `-1 2`
* To load a saved game: `-1 3`

## Game Setup Options

When starting the game, you'll be prompted to configure several options:

| Option | Description | Valid Inputs |
| ------ | ----------- | ------------ |
| Board Size | Dimensions of the square board | Any positive integer (e.g., 3 for 3x3) |
| Win Condition | Number of marks in a row needed to win | Integer between 1 and board size |
| Game Mode | Single player or multiplayer | 1 (Single) or 2 (Multi) |
| Difficulty | AI difficulty level (single player only) | 1 (Easy), 2 (Medium), or 3 (Hard) |

## Algorithm Details

The AI opponent uses the Minimax algorithm with alpha-beta pruning:
* **Minimax**: A recursive decision-making algorithm that evaluates all possible moves to determine the optimal play.
* **Alpha-Beta Pruning**: An optimization technique that reduces the number of nodes evaluated in the search tree.
* **Opening Book**: For standard 3x3 games, common optimal moves are pre-programmed for faster play.
* **Difficulty Adjustment**: The algorithm's search depth is limited based on the chosen difficulty level.

## Future Improvements

* Graphical user interface (GUI)
* Network multiplayer support
* Additional AI strategies
* Game statistics and analytics
* Customizable symbols and themes

## License

This project is open-source. Feel free to modify and improve it!
