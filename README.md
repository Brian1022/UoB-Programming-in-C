# UoB-Programming-in-C

This repository contains my C programming projects completed during my MSc in Computer Science at the University of Bristol. It demonstrates my ability to implement complex data structures, optimize memory allocation, and develop algorithmic solutions from scratch.

## 📂 Project Overview

### 1. T27 Dictionary & Auto-complete (27-way Trie)
A high-performance predictive text engine utilizing a recursive 27-way Trie (Prefix Tree) to handle 26 letters and the apostrophe character.
* **Features:** Supports word insertion, spell checking, and frequency-based auto-completion (`dict_autocomplete`). 
* **Extension:** Includes an alternative dictionary implementation using Hash Tables, which resolves collisions via chaining.
* **Analysis:** Provides a detailed architectural comparison showing that hash tables are more memory-efficient for sparse data with an average O(1) complexity, while the 27-way tree excels when frequent prefix operations (like auto-completion) are required.

### 2. Match-Drop State Space Solver (`md`)
An automated puzzle solver that utilizes Breadth-First Search (BFS) to find the shortest path to a goal state. 
* **Mechanics:** Reads initial grid states from a text file or string, checking for column consistency to reach the winning condition.
* **Optimization:** Manages up to 200,000 board states dynamically (`MAXBRDS 200000`), utilizing structured memory tracking and `memcmp` for recursive path deduplication.

### 3. Crush It! (`crushit`)
A physics grid engine that simulates the core mechanics of a match-3 game.
* **Mechanics:** Includes algorithms for initializing the board via file I/O, detecting 3-in-a-row matches (horizontal and vertical), and simulating block drops using gravitational constraints.

### 4. ROT18 Cipher (`rot18.c`)
A fast, character-level transformation tool.
* **Mechanics:** Combines ROT13 for alphabetic characters and ROT5 for digits, enforcing robust string parsing and ASCII boundary management.

## 🛠️ Key Technical Skills Demonstrated
* **Advanced C Programming:** Pointers, strict dynamic memory allocation (`malloc`, `calloc`, `free`), and structs.
* **Data Structures:** Hash Tables, Tries (Prefix Trees), Multidimensional Arrays, and custom Queues for BFS.
* **Software Verification:** Automated assert testing suites to guarantee functional correctness across edge cases.
