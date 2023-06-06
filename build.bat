@REM Windows
gcc -W -Wextra -pedantic -g -std=c99 -march=native -DDEBUG *.c -o bin/demo -lraylib -lopengl32 -lwinmm -lgdi32

@REM Linux
@REM gcc -W -Wextra -pedantic -g -std=c99 -march=native -DDEBUG *.c -o bin/demo -lraylib
