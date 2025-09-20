#  Maze Solver using Breadth-First Search (BFS) in C

This project is a console-based maze solver written entirely in C. It reads a labyrinth structure from a text file, finds the shortest path from the top-left corner to the bottom-right corner using the Breadth-First Search (BFS) algorithm, and displays the solving process step-by-step in the terminal.

This was developed as a university project to implement and understand graph traversal algorithms and fundamental data structures from scratch.

---

### ✨ What this project showcases

*   **Algorithm Implementation:** A clean, from-scratch implementation of the **Breadth-First Search (BFS)** algorithm to guarantee the shortest path.
*   **Custom Data Structures from Scratch:** The program does not rely on external libraries for its core logic.
    *   A **Queue** (file) was built using a linked list to manage the cells to visit, which is the heart of the BFS algorithm.
    *   A **Stack** (pile) structure is also defined, demonstrating knowledge of different data structures (even if not used in the final BFS implementation).
*   **Dynamic Memory Management:** Proper use of `malloc()` and `free()` to handle the labyrinth grid and queue elements, preventing memory leaks.
*   **File I/O:** The program reads and parses the maze layout from an external `.txt` file.

---

### 🛠️ Technologies & Tools Used

<div>
  <img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=black" alt="C"/>
  <img src="https://img.shields.io/badge/GCC-Compiler-4E8A00?style=for-the-badge&logo=gnu&logoColor=white" alt="GCC"/>
</div>

*   **C** as the programming language.
*   **GCC** for compilation.
*   Standard C libraries (`stdio.h`, `stdlib.h`).

---

### 🚀 How to Use

**1. Prerequisites**
*   You need a C compiler like GCC installed.

**2. Prepare the Labyrinth File**
The program requires a `laby1.txt` file in the same directory. The file must be formatted as follows:
```txt
15
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 1 1 0 1 1 1 1 1 0
... (rest of the maze) ...
