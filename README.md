# SFML Board Games

## Description

This project is a collection of classic and modern board games developed in C++ using the SFML graphics library. It includes three main games:

- **Classic Checkers**: A traditional implementation of Checkers with standard rules.  
- **Loot**: A captivating variant of Checkers that introduces new rules and strategies.  
- **Safari**: An innovative checker‑based game with unique elements that set it apart.  

Each game has its own graphical interface and rule set.

## Folder Structure

- **main.cpp**  
  Entry point: initializes the game, loads resources, and launches the main menu.

- **Makefile**  
  Build instructions for compiling all source files and linking against SFML.

- **Controller/**  
  Contains controller classes that manage game flow and user input for each game variant.

- **Model/**  
  Implements core game mechanics and data structures

- **View/**  
  Handles rendering and graphical user interface using SFML.
  - **resources/** – Asset files (piece images, fonts) used by the view.


## Prerequisites

- A C++17‑compatible compiler (e.g., `g++`, `clang++`)  
- [SFML](https://www.sfml-dev.org/) (graphics, window, system modules)  
- `make` build tool  

## Compilation & Execution

```bash
# From the project root directory:
make          # Compile the project
./jeu         # Run the game executable
```
