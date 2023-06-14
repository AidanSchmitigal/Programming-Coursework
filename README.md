# Intro Programming Coursework

A collection of my favorite projects from **CS162 - Introduction to Computer Science II** at Oregon State University. For each of theses I built custom terminal interfaces with visual effects.

## Assignments

| Course | Project                                   | What its about                                                                                                                                                                                                                                                                                                       |
| ------ | ----------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| CS162  | [Assignment 2 - Wizards](Wizards/)        | I made a custom custom terminal interface with side-by-side windows, text fields, buttons, colored validation states, and an ASCII-art lock screen. The library updates alongside the action panel and it has the full logged-in wizard, spellbook search, and sorting the assignment asks for.                      |
| CS162  | [Assignment 3 - Coffee Shop](CoffeeShop/) | Another interactive kiosk using TerminalGraphics, with scrolling coffee cards, ASCII-art drinks, search fields that update the menu as you type, best-seller highlights, and separate customer and employee views for ordering, menu editing, and order fulfillment.                                                 |
| CS162  | [Assignment 4 - Maze / Escape 162](Maze/) | Turned the maze into a programming-themed game with, again, a custom terminal UI, arrow-key movement, randomly placed walls and characters, illustrated learning material, and an embedded code editor. Battles compile to run the player's C++ solutions and show compiler or program output when a solution fails. |
| CS162  | [Assignment 5 - Fractal](Fractal/)        | A terminal fractal viewer with a Sierpinski triangle, Koch snowflake, dragon curve, and tree. It uses true-color rendering, animated hue changes, rotation, and movement across the terminal.                                                                                                                        |

## CS162 - Introduction to Computer Science II

### [Assignment 2 - Wizards](Wizards/)

| Login and locked library                                                                    | Spellbook browser and actions                                                        |
| ------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------ |
| ![Wizards login panel beside an ASCII-art lock protecting the library](Assets/Wizards3.png) | ![Wizards action panel beside the searchable spellbook library](Assets/Wizards5.png) |

### [Assignment 3 - Coffee Shop](CoffeeShop/)

![Coffee Shop kiosk with drink cards, best-seller labels, and search controls](Assets/CoffeeShop1.png)

| Search results                                                                   | Place an order                                                                      |
| -------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| ![Coffee Shop menu filtered using the name search field](Assets/CoffeeShop2.png) | ![Coffee Shop order screen with size and quantity controls](Assets/CoffeeShop4.png) |

![Coffee Shop employee view with order cards and fulfillment controls](Assets/CoffeeShop5.png)

### [Assignment 4 - Maze / Escape 162](Maze/)

| Start screen                                                                       | Explore the maze                                                                  |
| ---------------------------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| ![Escape 162 title screen and game options](Assets/Maze1.png)                      | ![Escape 162 maze with the player, TAs, skills, and instructor](Assets/Maze3.png) |
| **Learn a skill**                                                                  | **Write a solution**                                                              |
| ![Programming reference material shown after collecting a skill](Assets/Maze4.png) | ![Embedded C++ editor used to solve a programming challenge](Assets/Maze6.png)    |
| **Compiler feedback**                                                              | **Escape**                                                                        |
| ![Code challenge showing compiler errors beside the editor](Assets/Maze9.png)      | ![Escape 162 victory screen](Assets/Maze11.png)                                   |

### [Assignment 5 - Fractal](Fractal/)

| Sierpinski triangle                                                                   | Animated fractal patterns                                                                |
| ------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------- |
| ![Colorful Sierpinski triangle pattern rendered in the terminal](Assets/Fractal1.png) | ![Blue and cyan recursive fractal pattern rendered in the terminal](Assets/Fractal2.png) |
| ![Cyan fractal outlines rendered in the terminal](Assets/Fractal3.png)                | ![Branching recursive pattern with multicolored segments](Assets/Fractal4.png)           |

## Building and running

Wizards, Coffee Shop, Maze, and Fractal are written in C++. Run them from their own project folders. Use a terminal with ANSI color and Unicode support.

| Project     | Build and run                                                                                                          |
| ----------- | ---------------------------------------------------------------------------------------------------------------------- |
| Wizards     | `make run_wizard_out`, then `./run_wizard_out`. A terminal of at least 100 columns by 30 rows is required.             |
| Coffee Shop | Requires TerminalGraphics under `libs/TerminalGraphics` and libcurl. Then, `make debug`, and `./CoffeeShop`.           |
| Maze        | This also needs TerminalGraphics header, then run `make`. The in-game challenges use `g++` so make sure you have that. |
| Fractal     | `make Fractal`, then `./Fractal`. Use Ctrl+C to quit.                                                                  |
