# miniShell

A minimal Unix shell written in C++17 using POSIX system calls.

## Learning Goal

Learn how a shell works internally by building one from scratch: creating processes with `fork()`, running programs with `execvp()`, and waiting for them with `waitpid()`.

## Features

- Interactive prompt
- Runs external commands (`ls`, `pwd`, `echo Hello`)
- Built-ins: `cd`, `exit`
- Parent waits for each child, so no zombie processes

## Build and Run

```
make
./miniShell
```
