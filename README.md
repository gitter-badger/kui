# Kui
Kwiwk + Text User Interface = Kui!

[![Travis](https://img.shields.io/travis/kwiwk/kui.svg?style=flat-square)](https://travis-ci.org/kwiwk/kui)

### Table Of Contents
 - [Features](#features)
 - [Description](#description)
 - [Getting Started](#getting-started)
 - [Using Kui](#using-kui)

### Description

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



