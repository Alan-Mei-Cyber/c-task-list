# c-task-list

A simple command-line task list program written in C/C++ style.

## Features
- Store tasks in a **doubly linked list**
- Keep tasks **sorted by date** (month/day)
- Support basic commands: **insert**, **delete**, **change/update**
- Check for **duplicate tasks**
- Validate input **dates**
- **File I/O**: load tasks from a file and save tasks before exit
- Use **recursion** to print the list backwards and to free all nodes
- Use a **pthread mutex** to protect shared data when updating the list

## How to Build (example)
If you compile with g++:
```bash
g++ -std=gnu++11 -pthread *.c *.cpp -o tasklist
