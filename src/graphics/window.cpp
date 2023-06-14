#include <string>
#include <iostream>
#include <unistd.h>
#include "window.h"
#include "element.h"
#include "spacer.h"
#include "util.h"
#include <tuple>
#include <vector>

using namespace std;

struct winsize Window::w;
int Window::minWidth = 100;
int Window::minHeight = 30;
int Window::totalWindows = 0;
vector<Window*> Window::windows;

Window::Window(int width, string title, bool hidden) {
  this->width = width;
  this->index = totalWindows;
  totalWindows++;

  this->title = title;
  this->hidden = hidden;
  
  windows.push_back(this);

  paint();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Window Features~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Window::setWidthFR(int width) {
  this->width = width;
  Window::paint();
}

void Window::setHidden(bool hidden) {
  this->hidden = hidden;
  Window::paint();
}

void Window::addElement(WindowElement* element, int spacer) {
  this->elements.push_back(element);
  if (spacer) {
    this->elements.push_back(new Spacer(spacer));
  }
  Window::paint();
}

WindowElement* Window::getElement(int index) {
  return this->elements[index];
}

void Window::removeElement(WindowElement* element) {
  for (int i = 0; i < this->elements.size(); i++) {
    if (this->elements[i] == element) {
      this->elements.erase(this->elements.begin() + i);
      break;
    }
  }
  Window::paint();
}

void Window::removeAllElements() {
  for (int i = 0; i < this->elements.size(); i++) {
    delete this->elements[i];
  }
  this->elements.clear();
  Window::paint();
}

void Window::setTitle(string title) {
  this->title = title;
  Window::paint();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Window Drawers~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Window::drawBorder() {
  // Rounded corners
  drawText("╭", getX(), 0);
  drawText("╰", getX(), w.ws_row);
  
  drawText("╮", getX() + getWidth() - 1, 0);
  drawText("╯", getX() + getWidth() - 1, w.ws_row);

  // Draw side borders
  for (int i = 1; i < w.ws_row - 1; i++) {
    drawText("│", getX(), i);
    drawText("│", getX() + getWidth() - 1, i);
  }

  // Draw top & bottom border
  for (int i = 1; i < getWidth() - 1; i++) {
    drawText("─", getX() + i, 0);
    drawText("─", getX() + i, w.ws_row);
  }

  // Draw title
  drawText("┤" + title + "├", getX() + 1, 0);
}

void Window::clear() {
  cout << "\033[2J\033[1;1H";
}


void Window::updateWinSize() {
  ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
}

void Window::checkScreenSize() {
  if (w.ws_col < minWidth || w.ws_row < minHeight) {  
    cout << getColor(BRIGHT_CYAN) << "🚨 Screen size is too small." << endl;
    cout << "Please resize your Window to at least" << minWidth << "x" << minHeight << " characters." << endl;
    cout << "Your terminal is currently " << w.ws_col << "x" << w.ws_row << " characters." << endl;
    cout << getColor(RESET);
    std::exit(1);
  }
}

void Window::prepareScreen() {
  hideCursor();
  updateWinSize();
  checkScreenSize();
  for (int i = 0; i < w.ws_row; i++) {
    cout << endl;
    for (int j = 0; j < w.ws_col; j++) {
      cout << "█";
    }
  }
}

void Window::paint() {
  for (int i = 0; i < w.ws_row; i++) {
    setCursorPosition(0, i);
    for (int j = 0; j < w.ws_col; j++) {
      cout << " ";
    }
  }
  for (int i = 0; i < totalWindows; i++) {
    Window* window = windows[i];
    if (!window->hidden) {
      window->drawBorder();

      int totalHeight = 0;
      for (int j = 0; j < window->elements.size(); j++) {
        totalHeight += window->elements[j]->height;
      }
      for (int i = 0; i < window->elements.size(); i++) { 
        WindowElement* element = window->elements[i];
        // Width of the element
        int width = window->getWidth() * element->widthPercent;
        // X position of the element
        int x = window->getX() + window->getWidth() / 2 - width / 2;
        int y = 0;
        for (int j = 0; j < i; j++) {
          y += window->elements[j]->height;
        }
        y = w.ws_row / 2 - totalHeight / 2 + y;

        element->setLocation(x, y, width);
        element->paint();
      }
    }
  }
  cout << flush;
}

void Window::exit() {
  showCursor();
  setCursorPosition(0, 0);
  
  for (int i = 0; i < w.ws_col; i++) {
    for (int i = 0; i < w.ws_row; i++) {
      cout << "\b";
    }
    cout << "\b";
  }
  cout << "\033[2J\033[1;1H" << "Goodbye. 👋" << endl;

  // Delete all windows and elements
  for (int i = 0; i < totalWindows; i++) {
    for (int j = 0; j < windows[i]->elements.size(); j++) {
      delete windows[i]->elements[j];
    }
    delete windows[i];
  }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Window Getters~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int Window::getTotalWidthFR() {
  int totalWidth = 0;
  for (int i = 0; i < totalWindows; i++) {
    if (!windows[i]->hidden) {
      totalWidth += windows[i]->getWidthFR();
    }
  }
  return totalWidth;
}

int Window::getWidth() {
  return ((double) width) / ((double) getTotalWidthFR()) * w.ws_col;
}

int Window::getXFR() {
  int x = 0;
  for (int i = 0; i < index; i++) {
    if (!windows[i]->hidden) {
      x += windows[i]->getWidthFR();
    }
  }
  return x;
}

int Window::getX() {
  return ((double) getXFR() / ((double) getTotalWidthFR())) * w.ws_col;
}

int Window::getWidthFR() {
  return width;
}