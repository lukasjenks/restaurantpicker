## Summary

This project contains a simple program I wrote in 2019 to help my fellow employees and I at Method1
Software choose where to go for lunch on fridays in a random way. It allows the user to add, remove,
and randomly select a restaurant from memory at runtime and also simultaneously saves the list of 
restaurants added to a text file, allowing the data to persist between sessions.

### Author

Lukas Jenks

### System Prerequisites

This project most recently tested with the following:

OS: Arch Linux x86_64
Kernel: 5.10.15-arch1-1
Shell: bash 5.1.4
Thread model: posix
gcc 11.1.0
GNU Make 4.3

but should run on any unix-based OS.

## Running Instructions

To run the program, run:

`make all`

## Explanation of Test

Executing

`make all`

Executes the subcommands

`make picker`

and

`make run`

which compile picker.c using picker.h into the executable picker, then runs
the executable, respectively.

### Output

An interactive shell should launch upon executing the executable. Enter q
to exit the shell.
