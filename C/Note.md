# Notes

- [ ] [**C**: _Build Your Own Text Editor_](https://viewsourcecode.org/snaptoken/kilo/)
    - [X] Setup
    - [ ] Entering raw mode
    - [ ] Raw input and output
    - [ ] A text viewer
    - [ ] A text editor
    - [ ] Search
    - [ ] Syntax highlighting
    - [ ] Appendices


## Ch1. Setup

`$(CC)` is a variable that make expands to cc by default.

`-Wall` stands for “all Warnings”, and gets the compiler to warn you when it sees code in your program that might not technically be wrong, but is considered bad or questionable usage of the C language, like using variables before initializing them.

`-Wextra` and -pedantic turn on even more warnings. For each step in this tutorial, if your program compiles, it shouldn’t produce any warnings except for “unused variable” warnings in some cases. If you get any other warnings, check to make sure your code exactly matches the code in that step.

`-std=c99` specifies the exact version of the C language standard we’re using, which is C99. C99 allows us to declare variables anywhere within a function, whereas ANSI C requires all variables to be declared at the top of a function or block.


using `echo $?` in terminal, after run `kilo` is a way to check the `kilo`'s return value. which is defined in `kilo.c`

## Ch2. raw mode

