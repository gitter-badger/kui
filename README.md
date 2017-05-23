# Kui
Kool + Text User Interface = Kui!

[![Travis](https://img.shields.io/travis/ruski-engineering/kui.svg?style=flat-square)](https://travis-ci.org/ruski-engineering/kui)

### Table Of Contents
 - [Features](#features)
 - [Showcase](#showcase)
 - [Description](#description)
 - [Getting Started](#getting-started)
 - [Using Kui](#using-kui)


### Description
Kui is a terminal UI solution built as an alternative to ncurses. Sometimes we want a simple UI for people to use, or a basic canvas to draw on to test things out. Implementing a solution in ncurses leaves a lot to be desired with its unpredictable rendering. C Macros make it impossible to implement functions (i.e. _scroll()_) without conflicting with an ncurses macro defined in a global scope.

The goal of Kui is to provide a modern, easy to use, easy to understand terminal user interface framework for people to develop their applications with. Inspiration should be taken from other languages such as JavaScript. A hello world should be as simple as possible while still showcasing some of the more important scaffolding.

### Showcase

### Features

### Getting Started

### Using Kui
Getting the global [screen](https://kwiwk.github.io/kui/classkui_1_1Screen.html)
```cpp
#include <kui/screen.hpp>
#include <kui/input_const.hpp>

int main() {
    using namespace kui;
    
    auto& screen = Screen::get_screen();  // Get our global screen
    
    // On CTRL+Q, exit
    screen.on_input([](auto& s, auto input){
        // Screen's on_input sets the screen's callback, which is called whenever input is recieved
        
        // Input is simply a string alias and can be compared against Input_const
        if(input == Input_const::ctrl_q) {
            s.quit();
            return;
        }
    });
    
    screen.run();  // Run our screen/application
    return 0;
}
```

Adding a simple, static [box](https://kwiwk.github.io/kui/classkui_1_1Box.html)
```cpp
#include <kui/screen.hpp>
#include <kui/input_consts.hpp>

int main() {
    using namespace kui;
    
    auto& screen = Screen::get_screen();  // Get our global screen
    
    auto hw_box = screen.add_box([](auto& b){
        // The add_box function takes a callback to be called which contains steps
        // for initializing the box. The box itself is passed by reference into the function as ap
        
        b.move(0, 0;  // initialize box to position row 0, column 0 (top left)
        b.resize(1, 10);  // initialize box size to 1 row, 10 columns
        
        b.write_str(0, 0, "Hello, World!"); // Write "Hello, World!" to our box
    });
    
    // On CTRL+Q, exit
    screen.on_input([](auto& s, auto input){
        if(input == Input_const::ctrl_q) {
            s.quit();
            return;
        }
    });
    
    screen.run();  // Run our screen/application
    return 0;
}
```
