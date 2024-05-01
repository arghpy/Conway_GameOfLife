# Conway_GameOfLife

This is a personal project I've done in order to practice C and the raylib library.

Please feel free to experiment with the __ROWS__, __COLS__, __width__, __height__ and __POPULATION__ variables as they determine the size of the model.

The project was developed on Linux and thus is suited for UNIX operating systems.


In order to compile, use `gcc` or `clang`.

E.g.: `gcc GameOfLife.c -o GameOfLife -lraylib`


If you experience a segmentation fault, you need to allow an unlimited memory for the stack.
`$: ulimit -s unlimited`

