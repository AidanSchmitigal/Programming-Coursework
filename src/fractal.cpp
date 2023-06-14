/*********************************************************************
** Program Filename: fractal.cpp
** Author: Aidan Schmitigal
** Date: 3/19/2023
** Description: This is the main file for the fractal program.
** Input: What type of fractal to draw
** Output: A fractal
*********************************************************************/

#include <sys/ioctl.h>
#include <unistd.h>

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Canvas Drawing ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Array of color hues
int** canvas;
int** previousFrame;

int width;
int height;

string getColor(int hue, int offset = 0) {
  if (hue == 0) return "\033[38;2;m";
  // Convert color to RGB - color is hue
  hue = (hue + offset) % 360;
  int r = 0, g = 0, b = 0;
  if (hue < 60) {
    r = 255;
    g = hue * 255 / 60;
  } else if (hue < 120) {
    r = (120 - hue) * 255 / 60;
    g = 255;
  } else if (hue < 180) {
    g = 255;
    b = (hue - 120) * 255 / 60;
  } else if (hue < 240) {
    g = (240 - hue) * 255 / 60;
    b = 255;
  } else if (hue < 300) {
    r = (hue - 240) * 255 / 60;
    b = 255;
  } else {
    r = 255;
    b = (360 - hue) * 255 / 60;
  }

  string colorS = "\033[38;2;";
  colorS += to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
  return colorS;
}

void setColor(int x, int y, int hue) {
  if (x < 0 || y < 0 || x >= width || y >= height) return;
  canvas[x][y] = hue;
}

void paint(unsigned long rot = 0) {
  // Clear the screen and reset color
  // cout << "\033[2J\033[1;1H\033[0m";

  /* Creating a new canvas that is rotated by `rotation` pixels. */
  int** newCanvas1 = new int*[width];

  int cx = width / 2;   // calculate the center x coordinate
  int cy = height / 2;  // calculate the center y coordinate
  // Convert rotation to radians
  // long rotrotrot = (cos(rot * 10000) + 1) * rot / 2;
  double rotation = rot * M_PI / 180;

  for (int i = 0; i < width; i++) {
    newCanvas1[i] = new int[height];
    for (int j = 0; j < height; j++) {
      // translate to origin
      int x = i - cx;
      int y = j - cy;

      // perform rotation
      int newX = round(x * cos(rotation) - y * sin(rotation));
      int newY = round(x * sin(rotation) + y * cos(rotation));

      // translate back to original position
      newX += cx;
      newY += cy;

      // handle out-of-bounds indices
      newX = (newX + width) % width;
      newY = (newY + height) % height;

      // assign pixel value to new canvas
      newCanvas1[i][j] = canvas[newX][newY];
    }
  }

  int** newCanvas = new int*[width];

  long rotrot = rot / 2;
  for (int i = 0; i < width; i++) {
    newCanvas[i] = new int[height];
    for (int j = 0; j < height; j++) {
      newCanvas[i][j] = newCanvas1[(i + rotrot) % width][(j + rotrot) % height];
    }
  }

  // Find changed pixels
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (newCanvas[i][j] != previousFrame[i][j]) {
        // Set color
        cout << getColor(newCanvas[i][j], rot);
        // Move cursor
        cout << "\033[" << j << ";" << i << "H";
        // Print pixel
        cout << "█";
      }
    }
  }

  cout << "\033[" << height << ";0H";
  cout << "This will run until you press Ctrl+C.";
  // Flush output
  cout << flush;

  previousFrame = newCanvas;
}

void drawLine(int x1, int y1, int x2, int y2, int hue) {
  int dx = x2 - x1;
  int dy = y2 - y1;
  int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
  float xIncrement = dx / (float)steps;
  float yIncrement = dy / (float)steps;
  float x = x1;
  float y = y1;
  for (int i = 0; i <= steps; i++) {
    int roundX = round(x);
    int roundY = round(y);
    setColor(roundX, roundY, hue);
    x += xIncrement;
    y += yIncrement;
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Fractals ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Sierpinski Triangle
// Parameters: starting x, starting y, size, depth
void drawSierpinski(int x, int y, int size, int depth) {
  if (depth == 0) {
    drawLine(x, y, x + size, y, 10);
    drawLine(x, y, x + size / 2, y + size, 10);
    drawLine(x + size, y, x + size / 2, y + size, 10);
  } else {
    drawSierpinski(x, y, size / 2, depth - 1);
    drawSierpinski(x + size / 2, y, size / 2, depth - 1);
    drawSierpinski(x + size / 4, y + size / 2, size / 2, depth - 1);
  }
}

// Koch Snowflake
void koch(int x1, int y1, int x2, int y2, int depth) {
  if (depth == 0) {
    // Pick color based on location and depth
    int hue = (x1 + y1 + depth * depth) % 360;
    drawLine(x1, y1, x2, y2, hue);
  } else {
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int x3 = x1 + deltaX / 3;
    int y3 = y1 + deltaY / 3;
    int x4 = x2 - deltaX / 3;
    int y4 = y2 - deltaY / 3;
    int x5 = x3 + (int)(deltaX - deltaY * sqrt(3)) / 6;
    int y5 = y3 + (int)(deltaY + deltaX * sqrt(3)) / 6;
    koch(x1, y1, x3, y3, depth - 1);
    koch(x3, y3, x5, y5, depth - 1);
    koch(x5, y5, x4, y4, depth - 1);
    koch(x4, y4, x2, y2, depth - 1);
  }
}

void drawKochSnowflake(int x, int y, int length, int depth) {
  int x1 = x;
  int y1 = y;
  int x2 = x + length;
  int y2 = y;
  int x3 = x + length / 2;
  int y3 = y + length * sqrt(3) / 2;
  koch(x1, y1, x2, y2, depth);
  koch(x2, y2, x3, y3, depth);
  koch(x3, y3, x1, y1, depth);
}

void drawDragonCurve(int x, int y, int length, int depth, int angle = 0) {
  if (depth == 0) {
    // Pick color based on location and depth
    int hue = (x + y + depth * depth) % 360;
    drawLine(x, y, x + length * cos(angle), y + length * sin(angle), hue);
  } else {
    drawDragonCurve(x, y, length, depth - 1, angle);
    drawDragonCurve(x + length * cos(angle), y + length * sin(angle), length, depth - 1, angle + M_PI / 2);
  }
}

void drawTree(int x, int y, int length, int depth, double angle = 0) {
  int hue = (x + y + depth * depth) % 360;
  drawLine(x, y, x + length * cos(angle + 3 * M_PI / 2), y + length * sin(angle + 3 * M_PI / 2), hue);
  if (depth == 0) {
    return;
  } else {
    drawTree(x + length * cos(angle + 3 * M_PI / 2), y + length * sin(angle + 3 * M_PI / 2), length / 2, depth - 1, angle + M_PI / 4);
    drawTree(x + length * cos(angle + 3 * M_PI / 2), y + length * sin(angle + 3 * M_PI / 2), length / 2, depth - 1, angle - M_PI / 4);
  }
}

void fillSpace(int spaces) {
  for (int i = 0; i < spaces; i++) {
    cout << " ";
  }
}

/*********************************************************************
** Function: pattern
** Description: Prints a pattern of stars
** Parameters: lines, inset
** Pre-Conditions: lines and inset are ints
** Post-Conditions: none
*********************************************************************/
void pattern(int lines, int inset) {
  // OG code no colors
  if (lines == 0) {
    fillSpace(inset);
    cout << "*" << endl;
    return;
  }
  fillSpace(inset);
  cout << "*";
  fillSpace(lines * 2 - 1);
  cout << "*" << endl;
  pattern(lines - 1, inset + 1);
  fillSpace(inset);
  cout << "*";
  fillSpace(lines * 2 - 1);
  cout << "*" << endl;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {
  // Get the terminal size
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  width = w.ws_col;
  height = w.ws_row - 1;

  // Create the canvas
  canvas = new int*[width];
  for (int i = 0; i < width; i++) {
    canvas[i] = new int[height];
  }
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      canvas[i][j] = 0;
    }
  }

  int choice;
  cout << "1. Sierpinski Triangle" << endl;
  cout << "2. Koch Snowflake" << endl;
  cout << "3. Dragon Curve" << endl;
  cout << "4. Tree" << endl;
  cout << "5. Weird X shaped thing for the requirement" << endl;
  cout << "Enter your choice: ";

  cin >> choice;
  int param1, param2, param3, param4;

  switch (choice) {
    case 1:
      cout << "Enter the depth (10): ";
      cin >> param1;

      // Draw the fractal
      drawSierpinski(width / 4, height / 4, width / 2, param1);
      break;
    case 2:
      cout << "Enter the length (40): ";
      cin >> param1;
      cout << "Enter the depth (10): ";
      cin >> param2;

      // Draw the fractal
      drawKochSnowflake(width / 4, height / 4, param1, param2);
      break;
    case 3:
      cout << "Enter the length (100): ";
      cin >> param1;
      cout << "Enter the depth (10): ";
      cin >> param2;

      // Draw the fractal
      drawDragonCurve(width / 2, height / 2, param1, param2);
      break;
    case 4:
      cout << "Enter the length (40): ";
      cin >> param1;
      cout << "Enter the depth (10): ";
      cin >> param2;

      // Draw the fractal
      drawTree(width / 2, height + height / 4, param1, param2, 0);
      break;
    case 5:
      cout << "Enter the lines (4): ";
      cin >> param1;
      cout << "Enter the spaces (1): ";
      cin >> param2;

      // Draw the fractal
      pattern(param1, param2);
      break;
    default:
      cout << "Invalid choice" << endl;
      return 0;
  }

  if (choice != 5) {
    // Paint the canvas
    previousFrame = canvas;

    // cout << canvas;
    // Fill screen with black "\033[38;2;m";
    cout << "\033[2J\033[1;1H \033[48;2;m";
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        cout << " ";
      }
      cout << endl;
    }

    unsigned long time = 0;
    // loop until user presses any key

    // Switch so user doesn't have to press enter
    cout << "\033[?1049h";

    while (true) {
      paint(time);
      time++;
      // wait 500 ms
      usleep(50000);
    }

    // Switch back to main screen
    cout << "\033[?1049l";

  }  // Delete the canvas

  for (int i = 0; i < height; i++) {
    delete[] canvas[i];
  }
  delete[] canvas;

  return 0;
}
