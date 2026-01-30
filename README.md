# c-task-list

A simple command-line task list program written in C/C++ style.

## What it does
- Doubly linked list (sorted by date: month/day)
- Insert / delete / change tasks
- Date validation and duplicate checks
- File I/O (load and save)
- Recursion (print backwards, delete all)
- Mutex (pthread) for safer updates

## Build & Run
```bash
gcc -o lab9 main.c list.c file.c -lpthread
./lab9 <text_file> <binary_file>
# example:
make
./lab9 x y
