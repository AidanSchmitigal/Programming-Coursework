#ifndef TERMINAL_GRAPHICS_H
#define TERMINAL_GRAPHICS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Color {
    RESET = 0,
    BOLD = 1,
    DIM = 2,
    UNDERLINED = 4,
    BLINK = 5,
    REVERSE = 7,
    HIDDEN = 8,
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    GRAY = 90,
    LIGHT_RED = 91,
    LIGHT_GREEN = 92,
    LIGHT_YELLOW = 93,
    LIGHT_BLUE = 94,
    LIGHT_MAGENTA = 95,
    LIGHT_CYAN = 96,
    LIGHT_WHITE = 97,
};

enum State {
    DEFAULT = WHITE,
    DISABLED = DIM,
    SUCCESS = GREEN,
    ERROR = RED,
};

enum Key {
    ENTER = 13,
    ESCAPE = 27,
    SPACE = 32,
    BACKSPACE = 127
};

enum ArrowKey {
    UP = 65,
    DOWN = 66,
    RIGHT = 67,
    LEFT = 68,
    NONE = -1
};

/**
 * Returns the arrow key pressed by the user
 * @return The arrow key pressed by the user
 */
ArrowKey getArrowKey(int key);

/**
 * Returns the color code of the given color
 * @param color The color for which to get the color code
 * @return The color code of the given color
 */
string getColorCode(int color);

/**
 * Draws text on the console at the given position with the given color
 * @param text The text to be drawn on the console
 * @param x The X coordinate of the position at which to draw the text
 * @param y The Y coordinate of the position at which to draw the text
 * @param color The color of the text to be drawn on the console
 */
void drawText(string text, int x, int y, int color = WHITE);

/**
 * Draws text on the console at the given position with the given color
 * @param text The text to be drawn on the console
 * @param x The X coordinate of the position at which to draw the text
 * @param y The Y coordinate of the position at which to draw the text
 */
void drawRawText(string text, int x, int y);

/**
 * Clears the area of the console at the given position
 * @param x The X coordinate of the position to be cleared
 * @param y The Y coordinate of the position to be cleared
 * @param width The width of the area to be cleared
 * @param height The height of the area to be cleared
 */
void clearArea(int x, int y, int width, int height);

/**
 * Fills the area of the console at the given position with the given color
 * @param x The X coordinate of the position to be filled
 * @param y The Y coordinate of the position to be filled
 * @param width The width of the area to be filled
 * @param height The height of the area to be filled
 * @param color The color of the area to be filled
 */
void fillArea(int x, int y, int width, int height, int color = WHITE);

/**
 * Converts the given string to capital case
 * @param text The string to be converted to capital case
 * @return The given string converted to capital case
 */
string toCapitalCase(string text);

/**
 * Sets the console cursor position to the given position
 * @param x The X coordinate of the console cursor position to be set
 * @param y The Y coordinate of the console cursor position to be set
 */
void setCursorPosition(int x, int y);

/**
 * Shows the console cursor
 */
void showCursor();

/**
 * Hides the console cursor
 */
void hideCursor();

/**
 * Draws a box on the console at the given position with the given width and height
 * @param x The X coordinate of the position at which to draw the box
 * @param y The Y coordinate of the position at which to draw the box
 * @param width The width of the box to be drawn on the console
 * @param height The height of the box to be drawn on the console
 * @param color The color of the box to be drawn on the console
 */
void drawBox(int x, int y, int width, int height, int color = WHITE);

/**
 * Draws a box with a title on the console at the given position with the given width, height and title
 * @param x The X coordinate of the position at which to draw the box
 * @param y The Y coordinate of the position at which to draw the box
 * @param width The width of the box to be drawn on the console
 * @param height The height of the box to be drawn on the console
 * @param title The title of the box to be drawn on the console
 * @param color The color of the box to be drawn on the console
 */
void drawBox(int x, int y, int width, int height, string title, int color = WHITE);

/**
 * Draws an image on the console at the given position with the given width and height
 * @param path The path of the image to be drawn on the console
 * @param x The X coordinate of the position at which to draw the image
 * @param y The Y coordinate of the position at which to draw the image
 * @param width The width of the image to be drawn on the console
 * @param height The height of the image to be drawn on the console
 */
void drawImage(string path, int x, int y, int width, int height);

/**
 * Reads an image from the given file path
 * @param path The path of the image file to be read
 * @return A 2D vector representing the image read from the file
 */
vector<vector<int>> readImage(string path);

/**
 * Scales the given image to the given width and height
 * @param image The image to be scaled as a 2D vector
 * @param width The width to which to scale the image
 * @param height The height to which to scale the image
 * @return The given image scaled to the given width and height as a 2D vector
 */
vector<vector<int>> scaleImage(vector<vector<int>> image, int width, int height);

#include <tuple>

/**
 * Constructs a new window element with a given width and height.
 * @param width the width of the window
 * @param height the height of the window
 */
class WindowElement {
   public:
    /**
     * Constructs a new window element with a given width and height.
     * @param width the width of the window
     * @param height the height of the window
     */
    WindowElement(int width, int height);

    /**
     * Constructs a new window element with a given width percentage and height.
     * @param widthPercent the width percentage of the window
     * @param height the height of the window
     */
    WindowElement(double widthPercent, int height);

    /**
     * Constructs a new window element with a given width and height percentage.
     * @param width the width of the window
     * @param heightPercent the height percentage of the window
     */
    WindowElement(int width, double heightPercent);

    /**
     * Constructs a new window element with a given width percentage and height percentage.
     * @param widthPercent the width percentage of the window
     * @param heightPercent the height percentage of the window
     */
    WindowElement(double widthPercent, double heightPercent);

    /**
     * Destroys the WindowElement object.
     */
    virtual ~WindowElement();

    /*
     * Paints the element at the given coordinates.
     * The width and height are the size that the element should be painted at.
     * The element will fill the entire space given.
     * @param x the x position of the element
     * @param y the y position of the element
     * @param width the width of the element
     * @param height the height of the element
     */
    virtual void paint(int x, int y, int width, int height);

    /**
     * Gets the fixed size of the window element
     * @param parentWidth the parent's width
     * @param parentHeight the parent's height
     * @return a tuple of width and height
     */
    virtual tuple<int, int> getFixedSize(int parentWidth, int parentHeight);

    /**
     * Gets if the element is selectable
     * @return true if the element is selectable, false otherwise
     */
    bool isSelectable();

    /**
     * Selects the window element
     */
    virtual bool select();

    /**
     * Sends a key event to the window element
     * @param key the key code
     */
    virtual void keyEvent(int key);

    /**
     * Sends an arrow key event to the window element
     * @param key the arrow key
     * @param element the element that the arrow key was pressed on
     */
    virtual void arrowKeyEvent(ArrowKey key, WindowElement* element);

    /**
     * Sets the state of the window element
     * @param state the new state
     */
    void setState(State state);

    /**
     * Sets the hidden status of the window element
     * @param hidden the new status
     */
    void setHidden(bool hidden);

    /**
     * Sets the values of the cached position and size of the window element
     * @param x the x position of the window element
     * @param y the y position of the window element
     * @param width the width of the window element
     * @param height the height of the window element
     */
    void setValues(int x, int y, int width, int height);

    static WindowElement* focusedElement;

    double widthPercent = -1, heightPercent = -1;
    int width = -1, height = -1;
    bool selected, selectable;
    bool hidden = false;
    int cachedX = -1, cachedY = -1, cachedWidth = -1, cachedHeight = 1;
    State state = DEFAULT;
    WindowElement* parent;  // Group only for now
};

/**
 * A base class for creating different Layout objects
 */
class Layout {
   public:
    /**
     * Paints the layout on the screen
     * @param x the x position of the layout on the screen
     * @param y the y position of the layout on the screen
     * @param width the width of the layout on the screen
     * @param height the height of the layout on the screen
     * @param elements a vector of WindowElement objects to be included in the layout
     */
    virtual void paint(int x, int y, int width, int height, vector<WindowElement*> elements) = 0;

    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     * @return true if the next element was selected, false if the selected element was not changed
     */
    virtual bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) = 0;
};

#include <vector>

/**
 * Constructor for ColumnLayout object
 * @param widths an array of integers representing the width of each element in the layout
 */
class ColumnLayout : public Layout {
   public:
    /**
     * Constructor for ColumnLayout object
     * @param widths an array of integers representing the width of each element in the layout
     */
    ColumnLayout(int widths[]);

    /**
     * Paints the layout on the screen
     * @param x the x position of the layout on the screen
     * @param y the y position of the layout on the screen
     * @param width the width of the layout on the screen
     * @param height the height of the layout on the screen
     * @param elements a vector of WindowElement objects to be included in the layout
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;

    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;

   private:
    int* widths;
};

#include <vector>

/**
 * A constructor that initializes a GridLayout instance with the provided
 * widths and heights.
 *
 * @param widths the array of the column widths
 * @param heights the array of the row heights
 */
class GridLayout : public Layout {
   public:
    /**
     * A constructor that initializes a GridLayout instance with the provided
     * widths and heights.
     *
     * @param widths the array of the column widths
     * @param heights the array of the row heights
     */
    GridLayout(int widths[], int heights[]);

    /**
     * Paints the grid layout on the screen with the given x and y positions,
     * width, height, and vector of window elements.
     *
     * @param x the x-coordinate of the grid
     * @param y the y-coordinate of the grid
     * @param width the width of the grid
     * @param height the height of the grid
     * @param elements the vector of WindowElement objects to be painted
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;

    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;

   private:
    int* widths;   // an array of the column widths
    int* heights;  // an array of the row heights
};

#include <tuple>

/**
 * A class representing a horizontal layout of elements.
 */
class HorizontalLayout : public Layout {
   public:
    /**
     * Constructor for HorizontalLayout.
     */
    HorizontalLayout();
    /**
     * Paints the elements in the layout from left to right.
     * @param x the x coordinate of the layout
     * @param y the y coordinate of the layout
     * @param width the width of the layout
     * @param height the height of the layout
     * @param elements a vector of WindowElement pointers to be painted
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;
};

/**
 * Constructs a RowLayout with the given array of heights
 * @param heights array of heights of each element
 */
class RowLayout : public Layout {
   public:
    /**
     * Constructs a RowLayout with the given array of heights
     * @param heights array of heights of each element
     */
    RowLayout(int heights[]);

    /**
     * Paints the list of elements in a vertical row
     * @param x the x coordinate of the starting position
     * @param y the y coordinate of the starting position
     * @param width the width of the layout
     * @param height the height of the layout
     * @param elements the list of WindowElements to paint
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;

   private:
    int* heights;
};

#include <cmath>

/**
 * @param widths an array of integers representing the width of each element in the grid
 */
class ScrollingColumnsLayout : public Layout {
   public:
    /**
     * @param numColumns the number of columns in the grid
     */
    ScrollingColumnsLayout(int numColumns);
    /**
     * A grid where the width of each element is the same as the height
     * @param x the x coordinate of the top-left corner of the grid
     * @param y the y coordinate of the top-left corner of the grid
     * @param width the width of the grid
     * @param height the height of the grid
     * @param elements a vector of pointers to the WindowElements in the grid
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;

   private:
    int numColumns;
    int scrollOffset = 0;
};

#include <cmath>

/**
 * @param widths an array of integers representing the width of each element in the grid
 */
class SquareGridLayout : public Layout {
   public:
    /**
     * @param numColumns the number of columns in the grid
     */
    SquareGridLayout(int numColumns);
    /**
     * A grid where the width of each element is the same as the height
     * @param x the x coordinate of the top-left corner of the grid
     * @param y the y coordinate of the top-left corner of the grid
     * @param width the width of the grid
     * @param height the height of the grid
     * @param elements a vector of pointers to the WindowElements in the grid
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;

   private:
    int numColumns;
    int scrollOffset = 0;
};

#include <tuple>

/**
 * A vertical layout class for arranging WindowElements vertically.
 */
class VerticalLayout : public Layout {
   public:
    /**
     * Constructs a new VerticalLayout.
     */
    VerticalLayout();

    /**
     * Paints the given vector of elements in a vertical layout.
     * @param x the x-coordinate of the top-left corner of the layout
     * @param y the y-coordinate of the top-left corner of the layout
     * @param width the width of the layout
     * @param height the height of the layout
     * @param elements the vector of WindowElements to paint
     */
    void paint(int x, int y, int width, int height, vector<WindowElement*> elements) override;
    /**
     * Selects the next WindowElement in the layout
     * @param selectedElement the currently selected WindowElement
     * @param elements a vector of WindowElement objects to be included in the layout
     * @param direction the direction to select the next WindowElement in
     */
    bool selectNext(WindowElement* selectedElement, vector<WindowElement*> elements, ArrowKey direction) override;
};

#include <functional>
#include <string>

/**
 * A Button is a WindowElement that can be clicked. It has a setAction method that can be used
 * to specify a function that should be called when the Button is clicked.
 * It also has a paint method that paints the button in the console window.
 * @param title The text that is displayed on the button.
 * @param widthPercent The percentage of the parent width that the Button should take up.
 */
class Button : public WindowElement {
   public:
    /**
     * A Button is a WindowElement that can be clicked. It has a setAction method that can be used
     * to specify a function that should be called when the Button is clicked.
     * It also has a paint method that paints the button in the console window.
     * @param title The text that is displayed on the button.
     * @param action The function that will be executed when the button is clicked.
     * @param widthPercent The percentage of the parent width that the Button should take up.
     */
    Button(
        string title, function<void()> action = []() {});

    /**
     * A Button is a WindowElement that can be clicked. It has a setAction method that can be used
     * to specify a function that should be called when the Button is clicked.
     * It also has a paint method that paints the button in the console window.
     * @param title The text that is displayed on the button.
     * @param widthPercent The percentage of the parent width that the Button should take up.
     * @param action The function that will be executed when the button is clicked.
     */
    Button(
        string title, float widthPercent, function<void()> action = []() {});

    /**
     * Sets the title of the Button.
     * @param title The new title of the button.
     */
    void setTitle(string title);

    /**
     * Sets the action to be performed when the button is clicked.
     * @param action The function that will be executed when the button is clicked.
     */
    void setAction(function<void()> action);

    /**
     * Paints the button in the console window.
     * @param x The x-coordinate of the top left corner of the button.
     * @param y The y-coordinate of the top left corner of the button.
     * @param width The width of the button.
     * @param height The height of the button.
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * Handles key events.
     * @param key The key that was pressed.
     */
    void keyEvent(int key) override;

    /**
     * Simulates a click of the button by executing its action function.
     */
    void click();

   private:
    string title;
    function<void()> action;
};

#include <sstream>
#include <string>
#include <vector>

/**
 * Constructor for Group
 * @param layout A pointer to the layout of the Group
 */
class Group : public WindowElement {
   public:
    /**
     * Constructor for Group
     * @param layout A pointer to the layout of the Group
     */
    Group(Layout* layout);
    /**
     * Constructor for Group
     * @param layout A pointer to the layout of the Group
     * @param title The title of the Group
     */
    Group(Layout* layout, string title);
    /**
     * Destructor for Group
     */
    ~Group();
    /**
     * Adds a WindowElement to the Group
     * @param element A pointer to the WindowElement to add
     * @param spacer An integer representing the size of the Spacer to add after the WindowElement
     */
    void addElement(WindowElement* element, int spacer = 0);
    /**
     * Returns the WindowElement at the specified index
     * @param index The index of the WindowElement to return
     * @return The WindowElement at the specified index
     */
    WindowElement* getElement(int index);
    /**
     * Removes the specified WindowElement from the Group
     * @param element A pointer to the WindowElement to remove
     */
    void removeElement(WindowElement* element, bool remove = true);
    /**
     * Removes all WindowElements from the Group
     */
    void removeAllElements();
    /**
     * Hides all WindowElements in the Group
     */
    void hideAllElements();
    /**
     * Shows all WindowElements in the Group
     */
    void showAllElements();
    /**
     * Paints the Group to the screen
     * @param x The x coordinate to paint the Group at
     * @param y The y coordinate to paint the Group at
     * @param width The width of the Group
     * @param height The height of the Group
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * Handles a key press event
     * @param key The key that was pressed
     */
    void arrowKeyEvent(ArrowKey key, WindowElement* element) override;

    /**
     * Selects the Group
     */
    bool select() override;
    /**
     * Sets the title of the Group
     * @param title The title of the Group
     */
    void setTitle(string title);
    /**
     * Sets whether or not the border of the Group should be hidden
     * @param borderHidden A boolean representing whether or not the border should be hidden
     */
    void setBorderHidden(bool borderHidden);
    /**
     * Sets the layout of the Group
     * @param layout A pointer to the layout of the Group
     */
    void setLayout(Layout* layout);
    /**
     * Sets the background color of the Group
     * @param color The color to set the background to
     */
    void setBackgroundColor(Color color);

   private:
    string title;
    bool borderHidden;
    Color backgroundColor;
    vector<WindowElement*> elements;
    Layout* layout;
};

#include <fstream>

/**
 * Constructs an icon object with a given path and size.
 *
 * @param path The path of the icon to be constructed.
 * @param width The width of the icon to be constructed.
 * @param height The height of the icon to be constructed.
 */
class Icon : public WindowElement {
   public:
    /**
     * Constructs an icon object with a given path and size.
     *
     * @param path The path of the icon to be constructed.
     * @param width The width of the icon to be constructed.
     * @param height The height of the icon to be constructed.
     */
    Icon(string path, int width, int height);

    /**
     * Sets the icon of the icon object.
     *
     * @param path The path of the icon to be set.
     */
    void setIcon(string path);

    /**
     * Paints the icon object at the given coordinates.
     *
     * @param x The x coordinate at which the icon should be painted.
     * @param y The y coordinate at which the icon should be painted.
     * @param width The width at which the icon should be painted.
     * @param height The height at which the icon should be painted.
     */
    void paint(int x, int y, int width, int height) override;

   private:
    string path = "";
};

/**
 * Constructor for TextField object
 * @param title the title of the text input
 * @param templateText the template text to be shown if input is empty
 * @param widthPercent the percentage of the screen's width the text input should take up, defaults to 0.6
 */
class TextField : public WindowElement {
   public:
    /**
     * Constructor for TextField object
     * @param title the title of the text input
     * @param templateText the template text to be shown if input is empty
     * @param widthPercent the percentage of the screen's width the text input should take up, defaults to 0.6
     */
    TextField(string title, string templateText, float widthPercent = 0.9);

    /**
     * Sets the title of the text input
     * @param title the new title to be set
     */
    void setTitle(string title);

    /**
     * Sets the text input's current text
     * @param text the new text to be set
     */
    void setText(vector<string> text);

    /**
     * Gets the text input's current text
     * @return the text input's current text
     */
    vector<string> getText();

    /**
     *
     */
    void setLineNumbers(bool lineNumbers);

    /**
     * Paints the text input on the screen
     * @param x the x position of the text input on the screen
     * @param y the y position of the text input on the screen
     * @param width the width of the text input on the screen
     * @param height the height of the text input on the screen
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * When key is pressed, adds the key to the text input's text
     * @param key the key that was pressed
     */
    void keyEvent(int key) override;

    /**
     * When arrow key is pressed, moves the cursor in the text input's text
     * @param key the key that was pressed
     * @return true if the key was handled, false otherwise
     */
    void arrowKeyEvent(ArrowKey key, WindowElement* element) override;

    /**
     * Sets the exit action of the text input
     * @param exitAction the exit action to be set
     */
    void setExitAction(function<void(string)> exitAction);

    /**
     * Sets the key action of the text input
     * @param keyAction the key action to be set
     */
    void setKeyAction(function<void(string)> keyAction);

    void setHeader(vector<string> header);

    void setFooter(vector<string> footer);

   private:
    string title;
    vector<string> text = vector<string>();
    pair<int, int> selectedText = pair<int, int>(0, 0);
    string templateText;
    function<void(string)> exitAction;
    function<void(string)> keyAction;
};

/**
 * Constructs an Image object with a given path and size.
 *
 * @param path The path of the image to be constructed.
 * @param size The size of the image to be constructed.
 */
class Image : public WindowElement {
   public:
    /**
     * Constructs an Image object with a given path and size.
     *
     * @param path The path of the image to be constructed.
     * @param size The size of the image to be constructed.
     */
    Image(string path, int size);
    /**
     * Constructs an Image object with a given path and size.
     *
     * @param path The path of the image to be constructed.
     * @param size The size of the image to be constructed.
     */
    Image(string path, int width, int height);

    /**
     * Sets the image of the Image object.
     *
     * @param path The path of the image to be set.
     */
    void setImage(string path);

    /**
     * Paints the image object at the given coordinates.
     *
     * @param x The x coordinate at which the image should be painted.
     * @param y The y coordinate at which the image should be painted.
     * @param width The width at which the image should be painted.
     * @param height The height at which the image should be painted.
     */
    void paint(int x, int y, int width, int height) override;

   private:
    string path = "";
};

/*
* A file preview element that displays the contents of a file.

*/
class FilePreview : public WindowElement {
   public:
    /*
     * Creates a new file preview element with the given path.
     *
     * @param path The path of the file to be previewed.
     */
    FilePreview(string path);
    /*
     * Creates a new file preview element with the given path and width.
     *
     * @param path The path of the file to be previewed.
     * @param widthPercent The width of the file preview element.
     */
    FilePreview(string path, float widthPercent);

    /*
     * Sets the path of the file to be previewed.
     *
     * @param path The path of the file to be previewed.
     */
    void setPath(string path);

    /*
     * Paints the file preview element at the given coordinates.
     *
     * @param x The x coordinate at which the file preview element should be painted.
     * @param y The y coordinate at which the file preview element should be painted.
     * @param width The width at which the file preview element should be painted.
     * @param height The height at which the file preview element should be painted.
     */
    void paint(int x, int y, int width, int height);

   private:
    string path = "";
};

class Lock : public WindowElement {
    /**
     * Creates a new lock element with default dimensions
     */
    Lock();

    /**
     * Displays a lock icon
     * @param x - the x coordinate of the top left corner of the element
     * @param y - the y coordinate of the top left corner of the element
     * @param width - the width of the element
     * @param height - the height of the element
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * Sets the message to display when the lock is active
     * @param message - the message to display
     */
    void setLockedMessage(string message);

    /**
     * Sets the locked status of the element
     * @param locked - true if the element is locked, false otherwise
     */
    void setLocked(bool locked);

   private:
    bool locked;                // whether the lock is active or not
    string lockedMessage = "";  // message to display when the lock is active
};

/**
 * This class extends WindowElement class.
 * It creates Spacer objects with given height.
 * @param height The height of Spacer
 */
class Spacer : public WindowElement {
   public:
    /**
     * This class extends WindowElement class.
     * It creates Spacer objects with given height.
     * @param height The height of Spacer
     */
    explicit Spacer(float size) : WindowElement(size, size) {}

    /**
     * This class extends WindowElement class.
     * It creates Spacer objects with given height.
     * @param height The height of Spacer
     */
    explicit Spacer(int size) : WindowElement(size, size) {}

    /**
     * This function is an override to the paint function in the WindowElement class.
     * It does not paint any text or spaces.
     * @param x The x coordinate of the Spacer object
     * @param y The y coordinate of the Spacer object
     * @param width The width of the Spacer object
     * @param height The height of the Spacer object
     */
    void paint(int x, int y, int width, int height) override;
};

#include <algorithm>
#include <string>

/**
 * Creates a new Text object.
 * @param text the string to be displayed
 * @param widthPercent the percentage of the width of the window that the Text should take up.
 */
class Text : public WindowElement {
   public:
    /**
     * Creates a new Text object.
     * @param text the string to be displayed
     */
    Text(string text);

    /**
     * Creates a new Text object.
     * @param text the string to be displayed
     * @param widthPercent the percentage of the width of the window that the Text should take up.
     */
    Text(string text, float widthPercent);

    /**
     * Sets the text of the Text object.
     * @param text the string to be displayed
     */
    void setText(string text);

    /**
     * Displays the text on the window.
     * @param x the x coordinate of the text's position
     * @param y the y coordinate of the text's position
     * @param width the width of the text
     * @param height the height of the text
     */
    void paint(int x, int y, int width, int height);

   private:
    string text = "";
};

#include <functional>
#include <string>

/**
 * Constructor for TextInput object
 * @param title the title of the text input
 * @param templateText the template text to be shown if input is empty
 * @param widthPercent the percentage of the screen's width the text input should take up, defaults to 0.6
 */
class TextInput : public WindowElement {
   public:
    /**
     * Constructor for TextInput object
     * @param title the title of the text input
     * @param templateText the template text to be shown if input is empty
     * @param widthPercent the percentage of the screen's width the text input should take up, defaults to 0.6
     */
    TextInput(string title, string templateText, float widthPercent = 0.6);

    /**
     * Sets the title of the text input
     * @param title the new title to be set
     */
    void setTitle(string title);

    /**
     * Sets the text input's current text
     * @param text the new text to be set
     */
    void setText(string text);

    /**
     * Gets the text input's current text
     * @return the text input's current text
     */
    string getText();

    /**
     * Paints the text input on the screen
     * @param x the x position of the text input on the screen
     * @param y the y position of the text input on the screen
     * @param width the width of the text input on the screen
     * @param height the height of the text input on the screen
     */
    void paint(int x, int y, int width, int height) override;

    /**
     * When key is pressed, adds the key to the text input's text
     * @param key the key that was pressed
     */
    void keyEvent(int key) override;

    /**
     * When arrow key is pressed, moves the cursor in the text input's text
     * @param key the key that was pressed
     * @return true if the key was handled, false otherwise
     */
    void arrowKeyEvent(ArrowKey key, WindowElement* element) override;

    /**
     * Sets the exit action of the text input
     * @param exitAction the exit action to be set
     */
    void setExitAction(function<void(string)> exitAction);

    /**
     * Sets the key action of the text input
     * @param keyAction the key action to be set
     */
    void setKeyAction(function<void(string)> keyAction);

   private:
    string title;
    string text = "";
    string templateText;
    function<void(string)> exitAction;
    function<void(string)> keyAction;
};

#include <math.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

/**
 * Constructor method for Terminal class.
 * Initializes the Terminal.
 * @param layout: A pointer to a layout object.
 */
class Terminal {
   public:
    /**
     * Constructor method for Terminal class.
     * Initializes the Terminal.
     * @param layout: A pointer to a layout object.
     */
    Terminal(Layout* layout);

    /**
     * Destructor method for Terminal class.
     * Exits the terminal.
     */
    ~Terminal();

    /**
     * Checks if the user has pressed any keys.
     * If the user has pressed a key, it is handled.
     */
    static void checkInputs();

    /**
     * Initializes the Terminal window.
     */
    static void initTerminal();

    /**
     * Checks if the size of the Terminal window is big enough to display all content.
     * If the window is too small, prints an error message and exits the program.
     */
    static void checkScreenSize();

    /**
     * Exits the Terminal window with a fancy animation.
     */
    static void exit();

    static void addElement(WindowElement* element);

    static void removeElement(WindowElement* element);

    static void removeAllElements();

    static void select();

    static Group* rootWindow;
    static termios oldTerminalSettings;
    static struct winsize size;
    static struct pollfd fds[1];
    static bool exitFlag;
    const static int minWidth = 100;
    const static int minHeight = 30;
};

#endif