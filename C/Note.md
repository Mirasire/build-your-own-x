# Notes

- [ ] [**C**: _Build Your Own Text Editor_](https://viewsourcecode.org/snaptoken/kilo/)
    - [X] Setup
    - [X] Entering raw mode
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

## Ch2. Raw mode

**added feature**

- [X] press `q` to quit
- [X] control **terminal**'s behaviour
- [X] turn off **canonical mode**
- [X] display **keypresses**
- [X] turn off `ctrl-c` and `ctrl-z` (lflag: `ISIG`)
- [X] turn off `ctrl-s` and `ctrl-q` (iflag: `IXON`)
- [X] disable `ctrl-v` (lflag: `IEXTEN`)
- [X] fix `ctrl-M` (iflag: `ICRNL`)
- [X] turn off all output processing (oflag: `OPOST`)
- [X] compatible with old terminal
- [X] added timeout for `read()`
- [X] added error handling
- [X] split code into sections

**canonical mode(cooked mode)**

This mode is `Terminal`'s default mode. In this mode, keyboard's press will send to program(running on terminal) only when user press `Enter`.

using `ICANON` flag in `c_flag` to disable this mode.

**raw mode**

Terminal send to program when each single key pressed.


**miscellaneous flags**

- When `BRKINT` is turned on, a break condition will cause a `SIGINT` signal to be sent to the program, like pressing `Ctrl-C`.
- `INPCK` enables parity checking, which doesn’t seem to apply to modern terminal emulators.
- `ISTRIP` causes the 8th bit of each input byte to be stripped, meaning it will set it to 0. This is probably already turned off.
- `CS8` is not a flag, it is a bit mask with multiple bits, which we set using the bitwise-OR (|) operator unlike all the flags we are turning off. It sets the character size (CS) to 8 bits per byte. On my system, it’s already set that way.


## Ch3. Raw input and output

- [X] press `ctrl-q` to quit
- [X] refactor keyboard input
- [X] clear the screen
- [X] reposition the cursor
- [X] clear screen on exit
- [X] tildes
- [X] global state
- [X] get window's size (easy way)
- [X] get window's size (hard way)
- [ ]
- [ ]


**CTRL_KEY**

```cpp
//'a' is (61)D
#define CTRL_KEY(k) ((k) & 0x1f)
```

**clear the screen**


the reason of why using `"\x1b[2J"` in function `editorRefreshScreen`.

- `x1b` is value of escape key's press value
- `[`, `2`, `J`: see the refrence in ![#Erasing](https://vt100.net/docs/vt100-ug/chapter3.html)
- the `4` at `write(..., 4)` means we are writing 4 bytes out to the terminal.

**reposition the cursor**

`<esc>[H` *escape sequence* to reposition the cursor back up at the **top-left** corner.

**Tildes**

the tildes in left , which like when vim create a new file the `~` in the left. 

Example below:

```
~
~
~
~
~
```
