# gameoflife
Game of life written in C++ using wxWidgets GUI library.

## Installation
You would probably need wxWidgets. Do it by writing in cmd-line:
**sudo apt install libwxgtk3.0-dev**

## Compile
**g++ GameOfLife.cc MainFrame.cc GamePanel.cc Grid.cc -std=c++11 `wx-config --cxxflags` `wx-config --libs` -o gameoflife**

## Run
**./gameoflife**

![In-game screenshot](/img/screenshot.png)
