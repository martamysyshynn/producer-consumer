# Command-line Producer-Consumer program on C/C++

## Description:
The program creates one producer thread and two consumer threads.
- The producer generates a series of integers and places them in a shared buffer.
- The consumer receives the values and displays them on the screen.
- It terminates correctly after processing all values.

## Approaches: 
The program uses atomic operations for synchronization without mutexes, as mutexes are disallowed in this task.

- A fixed-size array (`buffer`) is used instead of `std::queue`, which is not thread-safe without mutexes.
- Synchronization is achieved using atomic indices:
  - `producer_index` tracks how many items have been written.
  - `consumer_index` tracks which item to read next.
- Atomic operations with memory ordering ensure correct visibility between threads.
- This approach avoids race conditions and allows safe communication without locks.


## Requirements:
- C++14 or later
- Linux / macOS (x86_64)
- GCC / G++ compiler 
  
## Build Instructions:

This project includes a Makefile. To compile and run the program, use:
```bash
make
./main
