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
Getting the main screen
```cpp
#include <kui/screen.hpp>
#include <kui/input_consts.hpp>

int main() {
    using namespace kui;
    
    auto& screen = Screen::get_screen();  // Get our global screen
    
    // On CTRL+Q, exit
    screen.on_input([](auto& s, auto input){
        if(input == Input_consts::ctrl_q) {
            s.quit();
            return;
        }
    });
    
    screen.run();  // Run our screen/application
    return 0;
}
```

Adding a static box
```cpp
#include <kui/screen.hpp>
#include <kui/input_consts.hpp>

int main() {
    using namespace kui;
    
    Screen& screen = Screen::get_screen();  // Get our global screen
    
    auto hw_box = screen.add_box([](auto& b){
        b.move(0, 0;  // initialize box to position row 0, column 0 (top left)
        b.resize(1, 10);  // initialize box size to 1 row, 10 columns
        
        b.write_str(0, 0, "Hello, World!"); // Write "Hello, World!" to our box
    });
    
    // On CTRL+Q, exit
    screen.on_input([](auto& s, auto input){
        if(input == Input_consts::ctrl_q) {
            s.quit();
            return;
        }
    });
    
    screen.run();  // Run our screen/application
    return 0;
}
```



