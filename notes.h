// notes.h

/*
Game of Life - Object-Oriented Implementation
=============================================

Overview:
---------
This program simulates Conway's Game of Life using a class-based design in C++. 
The grid is 60x60 and displays live and dead cells. The simulation follows the 
standard rules of the Game of Life:

Rules:
------
1. Any live cell with fewer than two live neighbors dies (underpopulation).
2. Any live cell with two or three live neighbors lives on.
3. Any live cell with more than three live neighbors dies (overpopulation).
4. Any dead cell with exactly three live neighbors becomes a live cell (reproduction).

Class Design:
-------------
Class: Grid
- Private:
  - int grid[MAX][MAX]; // Stores cell states (0 = dead, 1 = alive)
- Public Methods:
  - Grid(); // Constructor initializes grid to all dead
  - void SetAlive(int i, int j); // Sets cell to alive
  - void Kill(int i, int j); // Sets cell to dead
  - bool IsAlive(int i, int j); // Returns true if cell is alive
  - int CountNeighbors(int i, int j); // Counts live neighbors
  - void PopulateRandom(int r); // Randomly populates r live cells
  - void Clear(); // Clears the grid
  - void Save(const char fileName[]); // Saves grid to file
  - void Load(const char fileName[]); // Loads grid from file
  - void Step(); // Advances to next generation
  - void Show(); // Displays grid

Math & Logic:
-------------
- Neighbor counting uses a 3x3 window around each cell.
- Edge handling ensures no out-of-bound access.
- Random placement uses rand() with bounds checking.

Additional Features:
--------------------
- Text panel shows live cell count, generation count, and file name.
- Menu-driven interface for user interaction.
- Future enhancements: mouse interaction, speed control, dynamic file naming.

*/
